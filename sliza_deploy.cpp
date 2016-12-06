#include "sliza_deploy.h"

using namespace std;

int ReplaceTemplates(string usingDir){
	string configFile = "config.php";
	string configTemplatesFile = "config_templates.csv";
	string sTemplate;
	string sReplace;
	
	while(!FileIsExist(configTemplatesFile)){
		cout << "File " << configTemplatesFile << " not found! Specify a file that contains templates." << endl;
		cin >> configTemplatesFile;
	}
	
	while(!FileIsExist(usingDir + "/" + configFile)){
		cout << "File " << configFile << " not found! Specify a configuration file in your repository." << endl;
		cin >> configFile;
	}
	
	string configTextFile;
	ifstream fin(usingDir + "/" + configFile);
	getline (fin, configTextFile, '\0'); // Reads config file into a string
	
	string templateLine;
	ifstream finTemplate(configTemplatesFile);
	while (getline (finTemplate, templateLine)){
		size_t pos = templateLine.find(",");
		sTemplate = templateLine.substr(0, pos);
		sReplace = templateLine.substr(pos+1);
		
		if (sReplace.find("\r") != string::npos){
			sReplace.pop_back();
		}
		
		long pointerPos;
		while((pointerPos = configTextFile.find(sTemplate,0)) != string::npos)
			configTextFile.replace(pointerPos, sTemplate.length(), sReplace);
		
		
	}

	
	cout << configTextFile << endl;
	fin.close();
	
	
	ofstream fout(usingDir + "/" + configFile, ios_base::trunc);
	fout << configTextFile;
	fout.close();
	
	return 0;
}

bool FileIsExist(string filePath)
{
    bool isExist = false;
    ifstream fin(filePath.c_str());
 
    if(fin.is_open())
        isExist = true;
 
    fin.close();
    return isExist;
}