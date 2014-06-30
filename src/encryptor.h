#include <array>
#include <string>
#include <vector>
using namespace std;
class Encryptor
{
public:
    Encryptor(string& k, string& in);
    string crypt();

private:
    array<unsigned char, 256> state;
    string key;
    void ksa();
    string input;
    string output;
    string prga(const int& length);
};