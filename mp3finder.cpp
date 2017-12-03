/*Implementation of Mp3 finder
Author->Vivek Singh Rathore
*/

#include<iostream>
#include<dirent.h>     
#include<string>
#include<string.h>
#include<vector>    
using namespace std;
class mp3file{
    private:
    string f_name;
    string f_path;
    public:
    string showFile(){
        return f_name;
    }
    string showPath(){
        return f_path;
    } 
    mp3file(string filename,string path){
        f_name=filename;       
        f_path=path;
        
    }   
};
vector<mp3file> list;
class dirfile{
    public:
    DIR *dir;           
    struct dirent *ent;
    dirfile(string s){
        dir=opendir(s.c_str());
    }
    bool isDir(){
        if(ent->d_type==4)
            return true;
        else 
            return false;
    }
    bool isMp3(){
        if(ent->d_type==8){
            string temp;
            for(int i=strlen(ent->d_name)-4;i<strlen(ent->d_name);i++)
                temp.push_back(ent->d_name[i]);
            if(temp==".mp3")
                return true;
            else
                return false;
        }
        else
            return false;                   
        }   
};
void mp3find(string s){
    dirfile d(s);
    if(d.dir!=NULL){
        while((d.ent=readdir(d.dir))!=NULL){
            
            //skips the entities names '.','..' and '.*'
            
            if(strcmp(d.ent->d_name,".")==0 || strcmp(d.ent->d_name,"..")==0 || d.ent->d_name[0]=='.')
                continue;
            
            //checks for directory
            
            if(d.isDir()){
                string temp(d.ent->d_name);
                temp=s+"/"+temp; 
                mp3find(temp);
            }
            
            //checks for mp3 file
            
            if(d.isMp3()){
                mp3file m((string)d.ent->d_name,s);          
                list.push_back(m);                                      
            }    
        }
        closedir(d.dir);
    }
    else
        cout<<"Couldn't open the directory "<<s<<endl;
}
int main(){
    string inputPath;
    cout<<"Enter the path...."<<endl;
    cin>>inputPath;
    mp3find(inputPath);
    for(int i=0;i<list.size();i++)
    cout<<list[i].showFile()<<"\t"<<list[i].showPath()<<endl;   
}
