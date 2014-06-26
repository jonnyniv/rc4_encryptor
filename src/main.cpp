/*
    Designed by Jonathan Niven
    To run enter input filename and output filename to command line
*/

#include "main.h"
int main(int argc, char const *argv[])
{

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    string key;
    ifstream inputFile;
    ofstream outputFile;
    vector<unsigned char> input;
    vector<unsigned char> output;
    
    inputFile.open(argv[1]);
    outputFile.open(argv[2]);
    cout << "Please enter your session key:" << endl;
    getline(cin, key);

    while(!inputFile.eof())
    {
        input.push_back(inputFile.get());
    }
    encryptor enc(key, input);

    output = enc.crypt();

    for(int i = 0; i < (int) output.size(); i++)
    {
        outputFile.put(output[i]);
    }

    inputFile.close();
    outputFile.close();
    return 0;
}