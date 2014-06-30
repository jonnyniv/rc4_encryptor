#include "FileHandler.h"

FileHandler::FileHandler(bool b)
{
    fileStream = 0;
    fileString = 0;
    readOnly = b;
    setUp = false;
}

FileHandler::~FileHandler()
{
    fileStream->close();
    delete fileStream;
    delete fileString;
}

bool FileHandler::setFileName(const char* name)
{
    if(readOnly)
    {

        fileStream = new fstream(name, ios::in | ios::binary);
        if(!*fileStream)
        {
            cerr << "File \"" << name << "\" not found!" << endl;

            return false;
        }
        setUp = true;
        return true;
    }
    else
    {
        fileStream = new fstream(name, ios::out | ios::binary);
        setUp = true;
        return true;
    }

}

string* FileHandler::get()
{
    if(!setUp)
    {
        cerr << "FileHandler not set up properly!";
        throw false;
        return 0;
    }

    if(readOnly)
    {   
        fileStream->seekg(0, fileStream->end);
        fSize = fileStream->tellg();
        fileStream->seekg(0, fileStream->beg);
        cerr << "File size: " << fSize << endl;
        char* buffer = new char[fSize];
        fileStream->read(buffer, fSize);
        cerr << "File buffer: " << buffer << endl;

        fileString = new string(buffer);
        delete[] buffer;
        return fileString;
    }
    else
    {
        cerr << "Trying to read from an output file" << endl;
        return 0;
    }
}

bool FileHandler::write(string& s)
{
    if(!setUp)
    {
        cerr << "FileHandler not set up properly!";
        throw false;
        return false;
    }

    if(readOnly)
    {
        cerr << "Trying to write to an input file" << endl;
        return false;
    }
    else
    {
        fileStream->write(s.c_str(), s.size());
        cerr << s.size();
        return true;
    }

}