#ifndef __FUTIL_HPP
#define __FUTIL_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <dirent.h>
#include <errno.h>

using namespace std;

/**
 * This function is useful to know if a given path is either a folder, directory or none (?)
 * return 1 if it's a folder, -1 if it's a file, 0 if none or -2 on error
 **/
int folder_or_file(string path) {
    struct stat s;
    const char *c_path = path.c_str();
    if (stat(c_path, &s) == 0)
        if (s.st_mode & S_IFDIR) return 1; // It's folder
        else if (s.st_mode & S_IFREG) return -1; // It's file
        else return 0;
    else return -2;    
}

/**
 * Scan a given directory and save all the files and folders on each argument 
 **/
int getdir(string dir, vector<string> &files, vector<string> &folders){
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(dir.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        string fdname = dir + "/" + string(dirp->d_name);
        string dname = string(dirp->d_name);
        if (dname != "." && dname != "..") {            
            int r = folder_or_file(fdname);
            if (r == 1) folders.push_back(fdname);
            else if (r == -1) files.push_back(fdname);
        }
    }

    closedir(dp);
    return 0;
}

#endif // __FUTIL_HPP