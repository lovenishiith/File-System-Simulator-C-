#include <bits/stdc++.h>
#include "utils.hpp"


void handleWrite(Directory* current , string filename){
    File* file = getfile(current,filename);

    if(!file){
        cout  << "Error : File not found\n";
        return;
    }
    cout << "Enter content: " ;
    string text;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,text);
    file->content = text;
    file->modifiedTime = time(0);
    cout << "Content written successfully\n";
}
void handleRead(Directory* current,string filename){
    File* file =getfile(current,filename);
    if(!file){
        cout << "Error : File not found\n";
        return;
    }
    cout << "Content: " << file->content << endl;

}
void deletedirectory(Directory* current) {
    for(auto d : current->dirs){
        deletedirectory(d);
    }
    for(auto f : current->files){
        delete f;
    }
    delete current;
}

// adding path 
string getpath(Directory* current){
    vector<string> path;
    while(current!= nullptr){
        path.push_back(current->name);
        current = current->parent;
    }
    reverse(path.begin(),path.end());
   string result = "";

   // skip "Root"
   for(int i = 1; i < path.size(); i++){
    result += "/" + path[i];
    }

    // if nothing → root
    if(result.empty()) result = "/";

    return result;
}
// checking if directory exists or not
bool isDirectory(Directory* current , string name){
    for(auto dir : current->dirs){
        if(dir->name == name){
            return true;
        }
    }
    return false;
}

// checking if file exists or not 
bool isFile(Directory* current , string name){
    for(auto file : current->files){
        if(file->name == name) return true;
    }
    return false;
}


void handleRmdir(Directory* current , string name){
    if(isFile(current,name)){
        cout << "Error : " << name << " is a file , Not Directory , use rm\n";
        return;
    }
    for(int i=0;i<current->dirs.size();i++){
        if(current->dirs[i]->name == name){
            deletedirectory(current->dirs[i]);
            current->dirs.erase(current->dirs.begin()+i);
            cout << "Directory Deleted\n";
            return;
        }
    }
    cout << "Error : Directory not found\n";
}
void handleRm(Directory* current ,string filename){
   
     if(isDirectory(current,filename)){
            cout << "Error : " << filename << " is a Directory ,Not a file , use rmdir\n";
            return;
        }
    bool found = false;
    for(int i =0 ;i<current->files.size();i++){
        if(current->files[i]->name == filename){
            // free memory
            delete current->files[i];
            // remove from vector
            current->files.erase(current->files.begin()+i);
            found = true;
            break;
        }
    }      
       if(!found){ 
        cout << "Error : File Not found " << endl;
       }
}
void handleMkdir(Directory* current , string name){
    bool found = false;

    for(auto dir : current->dirs){
        if(dir->name == name){
            found = true;
            break;
        }
    }
   if(found) {
    cout << "Error : Directory exists" << endl;
   }
   else{ Directory* newdir = new Directory(name,current);
    current->dirs.push_back(newdir);
    }
}

void handleCd(Directory*& current , string name){

    if(name == ".."){
        if(current->parent != nullptr) {
            current = current->parent;
        }
    }
    else{
        if(isFile(current,name)){
            cout << "Error : " << name << " is a file , Not a Directory\n";
            return;
        }
        // this will replace 
        bool found = false;
        for(auto dir : current->dirs ){
            if(dir->name == name){
                current = dir;
                found = true;
                break;
            }
        }
        if(!found){
            cout << "Error : Directory Not found " << endl;
        }
    }
}

void handlels(Directory* current){
     // for directories
        for(auto dir : current->dirs){
            cout << "[DIR] " << dir->name << endl;
        }
        
        // now for files
        for(auto file : current->files){
        string c = ctime(&file->createdTime);
        c.pop_back();
        string m = ctime(&file->modifiedTime);
        m.pop_back();
        cout << "[FILE] " << file->name 
        << " | Size: " << file->size 
        << " | Type: " << file->type
        << " | Created: " << c
        << " | Modified: " << m << endl;            
        }
}

void handleTouch(Directory* current , string filename ) {
        bool found =false;
       
        for(auto file: current->files){
        if(file->name == filename){
            found = true;
            break;
        }
    }
        if(found) {
                cout << "Error : File already exists" << endl;
        }
        else {
           File* newfile = new File(filename);   
            current->files.push_back(newfile);
        }
}

vector<string> tokenize(string path){
    vector<string> tokens;
    stringstream ss(path);
    string temp ;

    while(getline(ss,temp,'/')){
        if(!temp.empty()) tokens.push_back(temp);
    }
    return tokens;
}

bool findfile(Directory* current , string filename){
    // checking in directories 
    bool found = false;
    for(auto file : current->files){
        if(file->name == filename){
             found = true;
            cout << getpath(current)<< "/"<<  filename << endl;
        }
    }
    // in subdirectories 
    for(auto dir : current->dirs){
        if(findfile(dir,filename)){
            found = true ;
        }
    }
    
    return found;
}

void handleMkdirpath(Directory* current , string name){
    vector<string> tokens = tokenize(name);
    
    for(int i=0;i<tokens.size();i++){
        string folder = tokens[i]; 
        bool found = false;
        for(auto dir : current->dirs){
            if(dir->name == folder ){
            current = dir ;
            found = true;
            break;
        }
        }
    

    // if not found 
    if(!found){
        // checking if its last 
        if(i == tokens.size()-1){
            Directory* newdir = new Directory(folder,current);
            current->dirs.push_back(newdir);
            cout << " Directory Created\n";
        }
        else{
            cout << " Error : Path doesn't exist\n";
            return;
    }
    }
    else if(i == tokens.size()-1){
        cout << "Error :Directory alredys exists\n";
        return;
    }
}
}

void handleTouchpath(Directory* current , string path){
    vector<string> tokens = tokenize(path);
    for(int i=0;i<tokens.size();i++){
        string name = tokens[i];
        bool found = false;
        for(auto dir : current->dirs){
            if(dir->name == name){
                current = dir ;
                found = true;
                break;
            }
        }

        if(!found){
            // if its last directory -> create 
            
                if(i == tokens.size()-1){
                    if(isFile(current,name)){
                        cout << "File already exists\n";
                        return;
                    }
                File* newfile = new File(name);
                current->files.push_back(newfile);
                cout << "file Created\n";
            
            }
            else{
                cout << "Error : Path doesn't exist\n" ;
                return;
            }
        }
    }
}

bool validatecommand(string command , vector<string>& args){
    // Command with No argument 
    if(command == "ls" || command == "pwd" || command == "exit" || command == "tree" ){
        // if arg is not empty 
        if(!args.empty()){
            cout << "Error : " << command << " takes no arguments\n ";
            return false;
        }

    }

    // Command with 1 argument 
    else if(command == "mkdir" || command == "cd" || command == "touch" || command == "rm" || command == "rmdir" || command == "find"){
        // 0 arguments 
        if(args.size()==0){
            cout << "Error : Missing argument for " << command << endl;
            return false;
        }
        // more than 1 argument 
        if (args.size()>1){
            cout << "Error : Too many arguments for " << command << endl;
            return false;
        }
    }
    else if(command == "cp" || command == "mv"){
        if(args.size()!=2){
            cout << "Error : " << command << " needs 2 Arguments\n";
            return false;
        }
    }
    else if(command == "search"){
        if(args.size()!=1){
            cout << "Error : search needs  1 argument\n";
            return false;
        }
    }
    else{
        cout << "Error : Unknown Command " << command << endl;
        return false;
    }
    return true;
}


// printing tree 
void printTree(Directory* current , int depth){
    // printing spaces
    for(int i=0;i<depth;i++){
        cout << " " ; 
    }
    if(depth == 0){
        // print current directory
    cout << current->name << endl;
    }

    // 
    for(int i=0;i<current->dirs.size();i++){
        for(int j=0;j<depth+1;j++){
            cout << " " ;
        }
        if(i == current->dirs.size()-1 && current->files.empty()){
              cout << "└── ";
        }
        else {
              cout << "├── ";
        }
        cout << current->dirs[i]->name << endl;
        // going deeper inside this
        printTree(current->dirs[i],depth+1);
    }

    // printing files 
    for(int i=0;i<current->files.size();i++){
        for(int j=0;j<depth+1;j++){
            cout << " " ;
        }
        if(i == current->files.size()-1 ){
            cout << "└── ";
        }
        else{
              cout << "├── ";
        }
        cout << current->files[i]->name << endl;
    }
}
File* getfile(Directory* current , string name){
    for(auto file : current->files){
        if(file->name == name){
            return file;
        }
    }
    return nullptr;
}
Directory* getdirectory(Directory* current , string name){
    for(auto dir : current->dirs){
        if(dir->name == name){
            return dir;
        }
    }
    return nullptr;
}
Directory* traversepath(Directory* current , string path){
    vector<string> tokens = tokenize(path);
    for(string t : tokens){
            bool found = false;
        for(auto dir : current->dirs){
            
            if(dir->name == t){
                current = dir;
                found = true;
                break;
            }
        }
        if(!found){
            return nullptr;
        }
    }
    return current;
}

void handleMv(Directory* current ,string src ,string dest){
    File* file = getfile(current,src);
    if(!file){
        cout << "Error : File doesn't exist\n" ;
        return;
    }

    Directory* target = traversepath(current,dest);

    if(!target){
        cout << "Error : Destination Path not found\n" ;
        return;
    }
    if(isFile(target,src)){
        cout << "Error : File already exists in destination\n";
        return;
    }
    // now erase 
    for(int i=0;i<current->files.size();i++){
        if(current->files[i]->name == src){
            current->files.erase(current->files.begin()+i);
            break;
        }
    }
    target->files.push_back(file);
    cout << "Moved successfully\n";
}

void handleCp(Directory* current , string src , string dest){
    File* file = getfile(current,src);
    if(!file){
        cout << "Error : File not found \n" ;
         return;
    }

    Directory* target = traversepath(current,dest);
    if(!target){
        cout << "Error :Destination Path not found \n" ;
        return;
    }

    if(isFile(target,src)){
        cout << "Error : File already exists in destination \n";
        return;
    }
    
    // now copy by creating new file 
    File* newfile = copyFile(file);
    target->files.push_back(newfile);
    cout << "Copied successfully\n";
}


void handleRenameFile(Directory* current , string oldname, string newname){
    File* file = getfile(current,oldname);
    if(!file){
        cout << "Error : File not found\n";
        return;
    }
    if(isFile(current,newname)){
        cout << "Error : File with new name already exists\n";
        return;
    }
    if(oldname == newname){
        cout << "Error : same name\n";
        return;
    }
    file->name = newname;
    cout << "File renamed Successfully\n";
}
void handleRenameDir(Directory* current , string oldname, string newname){
    Directory* dir = getdirectory(current,oldname);
    if(!dir){
        cout << "Error : Directory not found\n";
        return;
    }
    if(isDirectory(current,newname)){
        cout << "Error : Directory with new name already exists\n";
        return;
    }
    if(oldname == newname){
        cout << "Error : same name\n";
        return;
    }
    dir->name = newname;
    cout << "Directory renamed Successfully\n";
}
void searchByContent(Directory* current , string keyword){
    for(auto file : current->files){
        if(file->content.find(keyword)!= string::npos){
            cout << "MATCH " <<getpath(current) << "/" << file->name << endl;
        }
    }

    // in subdirecotries
    for(auto dir : current->dirs){
        searchByContent(dir,keyword);
    }
}

File* copyFile(File* original){
    File* newfile = new File(original->name);
    newfile->size = original->size;
    newfile->type = original->type;
    newfile->content = original->content;
    newfile->createdTime = original->createdTime;
    newfile->modifiedTime = original->modifiedTime;
    return newfile; 
}

Directory* copyDirectory(Directory* original , Directory* parent){
    Directory* newdir = new Directory(original->name,parent);

    // copy files
    for(auto file : original->files){
        newdir->files.push_back(copyFile(file));
    }
    // recursively copy subdirectory

    for(auto dir : original->dirs){
        Directory* childCopy = copyDirectory(dir,newdir);
        newdir->dirs.push_back(childCopy);
    }

    return newdir;
}

void handleCopyDir(Directory* current , string src , string dest){
    if(src == dest){
        cout << "Error : Cannot copy into itself\n";
        return;
    }

    Directory* source = getdirectory(current,src);

    if(!source){
        cout << "Error : Source directory not found\n";
        return;
    }
    Directory* target = traversepath(current,dest);
    if(!target){
        cout << "Error : Destination path not found\n";
        return;
    }

    if(isDirectory(target,src)){
        cout << "Error : Directory already exists in destination\n";
        return;
    }

    Directory* newcopy = copyDirectory(source,target);
    target->dirs.push_back(newcopy);
    cout << "Directory copied successfully\n";
}
Directory* resolvePath(Directory* current, Directory* root, string path){
    if(path.empty()) return current;

    // If absolute path → start from root
    if(!path.empty() && path[0] == '/'){
         current = root;
    }

    vector<string> tokens = tokenize(path);

    for(string t : tokens){
        if(t == "."){
            continue; // stay in same directory
        }
        else if(t == ".."){
            if(current->parent != nullptr){
                current = current->parent;
            }
        }
        else{
            Directory* next = getdirectory(current, t);
            if(!next){
                return nullptr; // invalid path
            }
            current = next;
        }
    }

    return current;
}