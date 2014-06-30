/*
    Designed by Jonathan Niven
    To run enter input filename and output filename to command line
*/

#include "main.h"
int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        cout << "Usage: encryptor InputFileName OutputFileName" << endl << "Terminating..." << endl;
        return 0;
    }
    
    //Text hiding method by guestgulkan on cplusplus forum
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    string key;
    string input;
    string output;
    
    FileHandler inputFile(true);
    if(!inputFile.setFileName(argv[1]))
    {
        return 0;
    }
    
    FileHandler outputFile(false);
    outputFile.setFileName(argv[2]);

    cout << "Please enter your session key:" << endl;
    getline(cin, key);

    input = *inputFile.get();

    Encryptor enc(key, input);

    output = enc.crypt();

    outputFile.write(output);
    return 0;
}

