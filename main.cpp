#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
/*
    Made by BAMBOOZLE
*/
using namespace std;

string printV(vector<char> &vect){
    string str = "";
    for(int i = 0; i < vect.size(); i++){
        str += vect[i];
    }
    return str;
}

string makeRandomKey(int randomNumber){
    string key = "";
    for(int i = 0; i < randomNumber; i++){
        key += (char)(rand() % 26 + 97);
    }
    return key;
}

vector<char> getContents(fstream &file, string fileName){
    vector<char> fileContents;
    file.open(fileName);
    if(!file.is_open()) perror("This is some shit bro");
    else {
       while(!file.eof()){
            char *temp;
            file.read(temp, 1);
            fileContents.push_back(*temp);
       }
    }
    file.close();
    return fileContents; // doesn't really matter, because if it fails, it'll be a segmentation fault
}

vector<char> encryptText(vector<char> &fileContents){
    const string key = makeRandomKey(10);
    vector<char> encryptedText;
    for(int i = 0; i < fileContents.size(); i++){
        if(fileContents[i] == ' '){
            encryptedText.push_back(' ');
        }
        else{
            encryptedText.push_back(fileContents[i] + key[i % key.size()]);
        }
    }
    return encryptedText;
}

void writeEncryptedText(vector<char> &encryptedText, string fileName){
    ofstream file;
    file.open(fileName);
    if(!file.is_open()) perror("This is some shit");
    else {
        for(int i = 0; i < encryptedText.size(); i++){
            file << encryptedText[i];
        }
    }
    file.close();
}

std::streampos fileSize( const char* filePath ){

    std::streampos fsize = 0;
    std::ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}

// function to clear contents of file
void clearFile(const char *fileName){
    ofstream file;
    file.open(fileName);
    if(!file.is_open()) perror("This is some shit");
    else {
        // delete all characters in the file
        streampos ptrPosition = 0;
        streampos ONE = 1;
        const streamsize STREAM_SIZE = 1;
        for(streampos i = 0; i < fileSize(fileName); i+ONE){
            file.seekp(fileSize(fileName) - i - 1);
            file.write(" ", STREAM_SIZE);
        }

        file.close();
    }
}

// Prototypes
streampos fileSize(const char*);
vector<char> encryptText(vector<char>&);
string makeRandomKey(int randomNumber);
vector<char> getContents(fstream&, string);
string printV(vector<char>&);
int main(int argc, char *argv[]){

    const string fileName = argv[1];
    const char *filePtr = argv[1];
    // replace the contents of the file with some testing text
    fstream testingFile;
    testingFile.open(fileName);
    if(!testingFile.is_open()) perror("This is some shit");
    else {
        // delete all characters in the file
        clearFile(filePtr);
        // replace the contents of the file with some testing text
        testingFile << "This is some testing text";
    }
    
    cout << "Name the file you'd like to encrypt: " << endl;
    fstream file;
    const string key = makeRandomKey(10);
    vector<char> beforeEncryption = getContents(file, fileName);

    //print the contents of the file before the encryption
    cout << printV(beforeEncryption) << endl;

    //print the encrypted text
    vector<char> encryptedText = encryptText(beforeEncryption);
    cout << printV(encryptedText) << endl;
    return 0;
}
