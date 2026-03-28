#include "filesystem.hpp"
#include "utils.hpp"
#include "persistence.hpp"

int main(){
    srand(time(0)); // different size everytime instead of same 
    Directory* Root = loadstate();
    if(Root == nullptr){
       Root = new Directory("Root",nullptr); 
    }

    Directory* current = Root ;
    while(true){
    cout << getpath(current) << " > " ;
    // now command
    
    vector<string> args;
    string commandline ;
    getline(cin,commandline);
    if(commandline.empty()) continue;
    stringstream ss(commandline);
    string command ;
    ss >> command;
    string temp;
    while(ss >> temp){
        args.push_back(temp);
    }
    if(!validatecommand(command,args)){
        continue;
    }
    string arg = args.empty() ? "" : args[0];
   // mkdir
    if(command  == "mkdir"){
       if(arg.find('/') != string::npos){
        handleMkdirpath(current,arg);
       }
       else {
        handleMkdir(current,arg);
       }
    }

   // cd
else if(command == "cd"){
    Directory* newDir = resolvePath(current, Root, arg);

    if(newDir){
        current = newDir;
    } else {
        cout << "Error: Invalid path\n";
    }
}
    // now ls
    else if(command == "ls"){
       handlels(current);
    }
    else if(command == "touch"){
       if(arg.find('/')!=string::npos){
        handleTouchpath(current,arg);
       }
       else{
        handleTouch(current,arg);
       }
    }
    else if(command == "pwd"){
        cout << getpath(current) << endl;
    }
    else if(command == "rm"){
        handleRm(current,arg);
    }
    else if(command == "rmdir"){
        handleRmdir(current,arg);
    }
    else if(command == "write"){
        handleWrite(current,arg);
    }
    else if(command == "read"){
        handleRead(current,arg);
    }
    else if(command == "search"){
        searchByContent(Root,arg);
    }
    else if(command == "rename"){
        if(args.size()!=2){
            cout << "Error : rename needs 2 arguments\n";
            continue;
        }
        string oldname = args[0];
        string newname = args[1];

        if(isFile(current,oldname)){
        handleRenameFile(current,oldname,newname);
        }
        else if(isDirectory(current,oldname)){
            handleRenameDir(current,oldname,newname);
        }
        else{
            cout << "Error : File/Directory not found\n";
        }
    }
    else if(command == "find"){
       if(!findfile(Root,arg)){
        // root because we dont only want to check in the current folder , we want it to be in all folders 
        cout << "Error : file does not exist" << endl;
      }
    }
    else if(command == "tree"){
        printTree(current,0);
    }
    else if(command == "mv"){
        handleMv(current,args[0],args[1]);
    }
    else if(command == "cp"){
        if(isFile(current,args[0])){
            handleCp(current,args[0],args[1]);
        }
        else if(isDirectory(current,args[0])){
            handleCopyDir(current,args[0],args[1]);
        }
        else{
            cout << "Error : Source not found\n";
        }
    }
    else if(command == "exit"){
        ofstream out("filesystem.txt");
        if(!out){
        cout << "Error: cannot open file\n";
        return 0;
        }
        saveState(Root,out);
        out.close();
        break;
    }
    else {
        cout << "Error : Unknown command  " << command  << endl;
    }

   }
  return 0 ;
}

