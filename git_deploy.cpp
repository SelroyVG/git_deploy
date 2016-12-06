#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char ** argv) {
	
	string usingBranch = "master";
	string usingLink = "false";
	string usingDir = "false";
	string query;
	for (int argCounter = 1; argCounter < argc; argCounter++) 
	{
		string currentAgrument = argv[argCounter];
		
		if (currentAgrument == "-l") //Link search
		{	
			usingLink = argv[argCounter + 1];
			continue;
		}

		if (currentAgrument == "-b") //Branch search
		{	
			usingLink = argv[argCounter + 1];
			continue;
		}
		if (currentAgrument == "-d") //Directory search
		{	
			usingLink = argv[argCounter + 1];
			continue;
		}

		if ((currentAgrument == "-h") || (currentAgrument == "--help")) //Help
		{
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
	
	query = "mkdir " + usingDir;
	system (query.c_str());	
	
	query = "git clone -b " + usingBranch + " " + usingLink + " " + usingDir;
	system (query.c_str());
	
	query = "git -C " + usingDir + " reset --hard"; 
	system (query.c_str());
	query = "git -C " + usingDir + " pull " + usingLink;
	cout << query << endl;
	system (query.c_str());

	return 0;
}