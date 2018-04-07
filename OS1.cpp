#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<iostream>
#include<stdlib.h>
using namespace std;


void listing(char *path){
	char cmd[100]="ls -l -a ";
	strcat(cmd,path);  // add current path to pass argument to ls command
	system(cmd);       // running ls command 
	struct dirent *dent;
	DIR *dir;
	DIR *dirt;

	dir=opendir(path);
		while((dent=readdir(dir))!=NULL)
		{
		   if(*(dent->d_name)=='.')
			{  
                           continue;
                           // It access current directory 
                        }
		
		   else
                      {

		      char next[50];
                      char temp[100];
		      strcpy(next,dent->d_name);
		      //printf("\nnext:-%s\n",next);//getchar();
			strcpy(temp,path);
			strcat(temp,"/");
			strcat(temp,next);
			

					dirt=opendir(temp);
					if(dirt!=NULL)
                                           {
                                                printf("\npath of next direcory:-%s\n",temp); 
						listing(temp);
                                           }

					closedir(dirt);
		}
		

	}

	closedir(dir);
	
}



int main(){

	
char p[100]="/home/yogesh";
listing(p);

	return 0;
}
