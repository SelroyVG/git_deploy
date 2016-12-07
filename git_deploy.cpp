#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "sliza_deploy.h"

using namespace std;

int main(int argc, char ** argv) {
	
	string usingLink = "false";
	string usingBranch = "master";
	string usingDir = "false";
	bool usingPatterns = false;
	bool usingCron = true;
	string tempDir = ".temp_deploy_dir";
	
	system("rm -rf .temp_deploy_dir");
	system("mkdir .temp_deploy_dir");
	
	string query;
	for (int argCounter = 1; argCounter < argc; argCounter++) 
	{
		string currentAgrument = argv[argCounter];
		
		if (currentAgrument == "-l"){ //Link search
			usingLink = argv[argCounter + 1];
			continue;
		}
		if (currentAgrument == "-b"){ //Branch search
			usingBranch = argv[argCounter + 1];
			continue;
		}
		if (currentAgrument == "-d"){ //Directory search	
			usingDir = argv[argCounter + 1];
			continue;
		}
		if (currentAgrument == "--include-patterns"){
			usingPatterns = true;
			continue;
		}
		if (currentAgrument == "--disable-input"){
			usingCron = false;
			continue;
		}
		if ((currentAgrument == "-h") || (currentAgrument == "--help")){ //Help
			cout << "Usage: ./git_deploy -l <Repository link> -d <Output directory> [-b <Branch name>]" << endl;
			return 0;
		}
		
		
	}
	if (usingLink == "false")
	{
		cout << "Error: repository link not specified!" << endl;
		return 1;
	}
	if (usingDir == "false")
	{
		cout << "Error: destination directory not specified!" << endl;
		return 2;
	}
	
/*	query = "mkdir " + usingDir;
	int error_code = system (query.c_str());	
	if (error_code == 0){*/
		cout << "Creating a new copy of the repository" << endl;
		query = "git clone -b " + usingBranch + " " + usingLink + " " + tempDir;
		system (query.c_str());
/*	} else if (error_code == 256){
		cout << "The directory already exists, trying to update the repository" << endl;
		query = "git -C " + usingDir + " reset --hard"; 
		system (query.c_str());
		query = "git -C " + usingDir + " pull " + usingLink;
		system (query.c_str());
	}*/
	
	if(usingPatterns){
		if (usingCron){
			cout << "Do you want to replace templates? (Y/N)" << endl;
			string user_input;
			cin >> user_input;
			if ((user_input == "Y") || (user_input == "y"))
				ReplaceTemplates(tempDir, usingCron);
		} 
		else{
			cout << "Trying to replace templates." << endl;
			ReplaceTemplates(tempDir, usingCron);
		}
	}
	
	query = "cp -R " + tempDir + "/* " + usingDir + "/";
	system(query.c_str());
	cout << "Repository copied into " << usingDir << endl;
	return 0;
}