/*Implementation of an mp3finder
Author->Vivek Singh Rathore
Date->23-9-2017*/
#include<iostream>
#include<dirent.h>
#include<string>
#include<string.h>
using namespace std;
void mp3find(string s){

	string temp;

	DIR *dir;
	struct dirent *ent;

	if( (dir=opendir(s.c_str())) !=NULL){

		while((ent=readdir(dir))!=NULL){
			if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0 || ent->d_name[0]=='.')
				continue;                                  				//skips the entities names '.','..' and '.*'
			if(ent->d_type==DT_DIR){                       				//checks if a directory
	            string temp1(ent->d_name);
				temp=s+"/"+temp1;
				mp3find(temp);                            				//recursive call to mp3find
			} 
	        if(ent->d_type==DT_REG){                       				//checks if a regular file
	            if(ent->d_name[strlen(ent->d_name)-1]=='3')             //checks if an mp3 file
	            cout<<ent->d_name<<" "<<s<<endl;                        //prints the filename and file directory
	        }

		}

	    closedir(dir);
    }
}
int main(){

	mp3find(".");           //call with current directory

}
