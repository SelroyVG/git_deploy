#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include "sliza_deploy.h"

using namespace std;

int main(int argc, char ** argv) {
	
	string usingLink;
	string usingDir;
	string usingBranch = "master";
	bool usingPatterns = false;
	bool usingCron = true;
	string tempDir = ".temp/temp_rep";
	
	system("rm -rf .temp/temp_rep");
	system("mkdir .temp/temp_rep");
	
	string query;
	for (int argCounter = 1; argCounter < argc; argCounter++) 
	{
		string currentAgrument = argv[argCounter];
		
		if ((currentAgrument == "-l") || (currentAgrument == "--link")){ //Link search
			usingLink = argv[argCounter + 1];
			continue;
		}
		if ((currentAgrument == "-b") || (currentAgrument == "--branch")){ //Branch search
			usingBranch = argv[argCounter + 1];
			continue;
		}
		if ((currentAgrument == "-d") || (currentAgrument == "--directory")){ //Directory search	
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
			cout << "Usage: ./git_deploy -l <Repository link> -d <Output directory> [-b <Branch name> --include-patterns --disable-input]" << endl;
			return 0;
		}
		
		
	}
	if (usingLink.length() == 0)
	{
		cout << "Error: repository link not specified!" << endl;
		return 1;
	}
	if (usingDir.length() == 0)
	{
		cout << "Error: destination directory not specified!" << endl;
		return 2;
	}
	
	cout << "Creating a new copy of the repository." << endl;
	query = "git clone -b " + usingBranch + " " + usingLink + " " + tempDir;
	system (query.c_str());
	
	if(usingPatterns){
		if (usingCron){
			cout << "Do you want to replace templates? (Y/N)" << endl;
			string user_input;
			cin >> user_input;
			if ((user_input == "Y") || (user_input == "y"))
				ReplaceTemplates(tempDir, usingCron);
		} 
		else{
			cout << "Trying to replace templates..." << endl;
			ReplaceTemplates(tempDir, usingCron);
		}
	}
	query = "mkdir " + usingDir + " 2>> .temp/bash_log";
	int error_code = system (query.c_str());	
	if (error_code == 0)
		cout << "Directory " << usingDir << " not found! Creating an empty directory " << usingDir << endl;
	
	query = "cp -R " + tempDir + "/* " + usingDir + "/";
	system(query.c_str());
	query = "cp -R " + tempDir + "/.[a-zA-Z0-9]* " + usingDir + "/ 2>> .temp/bash_log";
	system(query.c_str());
	cout << "Repository copied into " << usingDir << endl;
	return 0;
}