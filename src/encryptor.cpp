#include "Encryptor.h"

Encryptor::Encryptor(string& k, string& in)
{
    key = k;
    input = in;
    for (int i=0; i < 256; i++)
    {
        state[i] = i; 
    }
}

void Encryptor::ksa()
{
    int len = key.length(), j = 0, temp;
    for(int i = 0; i < 256; i++)
    {
        j = (j + state[i] + (unsigned char) key[i % len]) % 256;
        temp = state[i];
        state[i] = state[j];
        state[j] = temp;
    }
}

string Encryptor::prga(const int& length)
{
    string output;
    int  i = 0, j = 0, temp;
    for(int x = 0; x < length; x++)
    {
        i = (i + 1) % 256;
        j = ( j + state[i]) % 256;
        temp = state[i];
        state[i] = state[j];
        state[j] = temp;
        output.push_back(state[(state[i] + state[j]) % 256]);
    }
    return output;
}

string Encryptor::crypt()
{
    int length = (int) input.size()-1;

    prga(1024);
    ksa();
    string encStream = prga(length);
    for(int i = 0; i < length; i++)
    {
        output.push_back(input[i] ^ encStream[i]);
    }
    return output;
}