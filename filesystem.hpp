#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include<bits/stdc++.h>
using namespace std;

class File{
public:
    string name;
    int size;
    string type;
    string content;
    time_t createdTime;
    time_t modifiedTime;

    File(string name);
};

class Directory{
public:
    string name;
    vector<Directory*> dirs;
    vector<File*> files;
    Directory* parent;

    Directory(string name, Directory* parent);
};

#endif
