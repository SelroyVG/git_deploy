#include "sliza_deploy.h"

using namespace std;

int ReplaceTemplates(std::string tempDir, bool usingCron){
	string currentFile;
	string configTemplates = "config/sliza_templates.csv";
	string configExtensions = "config/extensions";
	string sTemplate;
	string sReplace;
	int filesCounter = 0;
	
	if (usingCron){
		while(!FileIsExist(configTemplates)){
			cout << "File " << configTemplates << " not found! Specify a file that contains templates." << endl;
			cin >> configTemplates;
		}
		
		while(!FileIsExist(configExtensions)){
			cout << "File " << configExtensions << " not found! Specify a file that contains templates." << endl;
			cin >> configExtensions;
		}
		
	} else 
		if(!FileIsExist(configTemplates) || !FileIsExist(configExtensions)){
			cout << "A necessary config file not found! Replacing templates operation aborted." << endl;
			return 2;
		}
	
	system ("rm -f .temp/fileslist");
	
	string extension;
	ifstream finExtensions(configExtensions);
	while (getline (finExtensions, extension)){
		extension = CutString(extension);
		string query = "find " + tempDir + " -name *" + extension + " > .temp/fileslist";
		system(query.c_str());
		
		ifstream finFileList(".temp/fileslist");
		while (getline (finFileList, currentFile)){
			currentFile = CutString(currentFile);
			filesCounter++;
			
			string textFile;
			ifstream fin(currentFile);
			getline (fin, textFile, '\0'); // Reads a file into a string
			
			string templateLine;
			ifstream finTemplate(configTemplates);
			while (getline (finTemplate, templateLine)){
				size_t pos = templateLine.find(",");
				sTemplate = templateLine.substr(0, pos);
				sReplace = templateLine.substr(pos+1);
				
				if (sReplace.find("\r") != string::npos){
					sReplace.pop_back();
				}
				
				long pointerPos;
				while((pointerPos = textFile.find(sTemplate,0)) != string::npos)
					textFile.replace(pointerPos, sTemplate.length(), sReplace);
				
				
			}
			finTemplate.close();
			fin.close();
			
			ofstream fout(currentFile, ios_base::trunc);
			fout << textFile;
			fout.close();
		}
	}
	finExtensions.close();
	cout << "Templates replased, " << filesCounter << " files parsed." << endl;
	
	return 0;
}

string CutString(string OriginalString){
	if (OriginalString.find("\r") != string::npos){
		OriginalString.pop_back();
	}
	return OriginalString;
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