#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

int ReplaceTemplates(std::string tempDir, bool usingCron);
bool FileIsExist(std::string filePath);
std::string CutString(std::string OriginalString);