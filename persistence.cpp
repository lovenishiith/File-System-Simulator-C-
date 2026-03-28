#include "persistence.hpp"
#include "utils.hpp"

void saveState(Directory* current , ofstream& out){
    if(current == nullptr) return;
    // printing current directory
    out << "D " << current->name << endl;

    // going into files
    for(auto file : current->files){
        out << "F|" << file->name<<  "|" << file->size << "|" << file->type  << "|" << file->createdTime << "|" << file->modifiedTime << "|" << file->content << endl;
    }
    // Recursively saving  subdirectories 
    for(auto dir : current->dirs){
        saveState(dir,out);
    }
    // END means Mark end of this directory
    out << "END" << endl;
}

Directory* loadstate(){
    ifstream in("filesystem.txt");
    if(!in) {
        return nullptr;
    }
    stack<Directory*> st;
    Directory* root = nullptr;
    string line;
    while(getline(in,line)){
        if(line.empty()) continue;

        if(line[0] == 'D'){
            string name = line.substr(2);
            Directory* newdir;

            if(st.empty()){
                newdir = new Directory(name,nullptr);
                root = newdir;
            }
            else{
                newdir = new Directory(name,st.top());
                    st.top()->dirs.push_back(newdir);
                
                
            }
            st.push(newdir);
        }
        else if(line[0] == 'F'){
            stringstream ss(line);
            vector<string> parts;
            string temp;
           while(getline(ss,temp,'|')){
            parts.push_back(temp);
           }
           if(parts.size()<7 || st.empty()) {continue;}
           string name = parts[1];
           int size = stoi(parts[2]);
           string filetype = parts[3];
           time_t created = stoll(parts[4]);
           time_t modified = stoll(parts[5]);
           string content = parts[6];
           for(int i = 7; i < parts.size(); i++){
            content += "|" + parts[i];
            }
            File* newfile = new File(name);
            newfile->size = size;
            newfile->type = filetype;
            newfile->createdTime = created;
            newfile->modifiedTime = modified;
            newfile->content = content;
           
             st.top()->files.push_back(newfile);
           

        }
        else if(line == "END"){
            if(!st.empty()){
                st.pop();
            }
            else return nullptr;
        }
    }
    return root;

}