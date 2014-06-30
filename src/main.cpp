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
    else if(!fexists(argv[1]))
    {
        cout << "Input file does not exist!" << endl << "Terminating..." << endl;
        return 0;
    }

    
    //Text hiding method by guestgulkan on cplusplus forum
    

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    string key;
    vector<unsigned char> input;
    vector<unsigned char> output;
    
    ifstream inputFile(argv[1], ios::in | ios::binary);
    ofstream outputFile(argv[2], ios::out | ios::binary);

    cout << "Please enter your session key:" << endl;
    getline(cin, key);

    while(!inputFile.eof())
    {
        input.push_back(inputFile.get());
    }

    inputFile.close();

    Encryptor enc(key, input);
    output = enc.crypt();

    for(int i = 0; i < (int) output.size(); i++)
    {
        outputFile.put(output[i]);
    }

    
    outputFile.close();
    return 0;
}

//Credit to ropez on cplusplus forum
bool fexists(const char* filename)
{
    ifstream ifile(filename);
    return ifile;
}