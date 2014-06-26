#include "encryptor.h"

encryptor::encryptor(string& k, vector<unsigned char>& in)
{
    key = k;
    input = in;
    for (int i=0; i < 256; i++)
    {
        state[i] = i; 
    }
}

void encryptor::ksa()
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

vector<unsigned char> encryptor::prga()
{
    vector<unsigned char> output;
    int  i = 0, j = 0, temp;
    for(int x = 0; x < (int) input.size()-1; x++)
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

vector<unsigned char> encryptor::crypt()
{
    ksa();
    vector<unsigned char> encStream = prga();
    for(int i = 0; i < (int) input.size()-1; i++)
    {
        output.push_back(input[i] ^ encStream[i]);
    }
    return output;
}