#include "filesystem.hpp"

File::File(string name){
    //  constructor code
         this->name = name;
        this->size = rand() % 1000 +1; // random no from 1-1000

        // 
        int pos = name.find('.');
        if(pos!= string::npos){
            this->type = name.substr(pos+1);
        }
        else {
            this->type = "Unknown" ;
        }
        this->content = ""; // initialise empty

        createdTime = time(0);
        modifiedTime = time(0);
}

Directory::Directory(string name, Directory* parent){
    // constructor code
       this->name = name ;
       this->parent = parent;
    
}