#ifndef UTILS_HPP
#define UTILS_HPP

#include "filesystem.hpp"

// path + helpers
string getpath(Directory*);
vector<string> tokenize(string);
Directory* resolvePath(Directory*, Directory*, string);

// checks
bool isDirectory(Directory*, string);
bool isFile(Directory*, string);

// file + dir access
File* getfile(Directory*, string);
Directory* getdirectory(Directory*, string);
Directory* traversepath(Directory*, string);

// operations
void deletedirectory(Directory*);
void handleWrite(Directory*, string);
void handleRead(Directory*, string);
void handleMkdir(Directory*, string);
void handleCd(Directory*&, string);
void handlels(Directory*);
void handleTouch(Directory*, string);
void handleRm(Directory*, string);
void handleRmdir(Directory*, string);

void handleMkdirpath(Directory*, string);
void handleTouchpath(Directory*, string);

void handleMv(Directory*, string, string);
void handleCp(Directory*, string, string);
void handleCopyDir(Directory*, string, string);

void handleRenameFile(Directory*, string, string);
void handleRenameDir(Directory*, string, string);

void searchByContent(Directory*, string);
bool findfile(Directory*, string);

void printTree(Directory*, int);

File* copyFile(File*);
Directory* copyDirectory(Directory*, Directory*);

bool validatecommand(string, vector<string>&);


#endif