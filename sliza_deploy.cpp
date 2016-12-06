#include "sliza_deploy.h"

using namespace std;

int ReplaceTemplates(string usingDir){
	string configFile = "config.php";
	while(!FileIsExist(usingDir + "/" + configFile) && !(configFile == "0")){
		cout << "File " << configFile << " not found! Specify your configuration file. (Type '0' for cancel)" << endl;
		cin >> configFile;
	}
	if(configFile == "0")
		return 0;
	string textFile;
	ifstream fin(usingDir + "/" + configFile);
	getline ( fin, textFile, '\0' );
	
	
	long sPosition;
	string stringTemplate = "%db_username%";
	string stringReplace = "sliza";
	while((sPos = textFile.find(stringTemplate,0)) != string::npos)
        textFile.replace(sPos,stringTemplate.length(),stringReplace);
	
	cout << textFile << endl;
	fin.close();
	
	
	ofstream fout(usingDir + "/" + configFile, ios_base::trunc);
	fout << textFile;
	fout.close();
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