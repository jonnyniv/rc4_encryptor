#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class FileHandler
{
public:
    FileHandler(bool b);
    ~FileHandler();
    
    bool setFileName(const char* name);

    string* get();
    bool write(string& s);

private:
    bool setUp;
    bool readOnly;
    fstream* fileStream;
    string* fileString;
    int fSize;
};