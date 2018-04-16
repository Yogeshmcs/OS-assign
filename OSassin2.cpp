#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
using namespace std;


int array[50], k, pd[2], first, last;

void print(int f,int l){
	int flag=0;
	cout<<"segment(lower,upper):-"<<f<<" "<<l<<endl;
		for(int i=f;i<=l;i++)
			if(array[i]==k)
			{
				cout<<"\nelement found at position "<<i+1<<"\n";
				flag=1;
				kill(0,SIGINT);  // Killing the all process when element found			
			}

	if(flag==0)
	cout<<"\nElement not found in this segment\n";
	
	}


void divide(){
        
	read(pd[0],&first,sizeof(int));   //Reading the start of the segment 
	read(pd[0],&last,sizeof(int));    //Reading end of the segment

	if((last-first+1)<=5)           // Searching Element when segments size below or equll 5
		print(first,last);

	else{
		int pid=fork();int r;   // creating child to give half of data
		if(pid==0){
		int mid=(first+last)/2;  
		write(pd[1],&first,sizeof(int));    //Writing start of the new segment 
		write(pd[1],&mid,sizeof(int));      //Writing End of the new segment
		//cout<<"\nchild1";
		divide();

	    }

	else{ 
               
		pid=fork();        // creating another child to give half of the data
		if(pid==0)
                {   
			int mid=(first+last)/2+1;
			write(pd[1],&mid,sizeof(int));   // Writing the start of the segment
			write(pd[1],&last,sizeof(int));  // Writing The end of the segment

			//cout<<"\nchild2";
			int a=wait(&r);
		
			divide();  
               	} 

	    }


	}	

}

int main(int argc,char *argv[])
{

	FILE* fd=fopen(argv[1],"r"); // opening the file from command line argument
	int n;
	fscanf(fd,"%d\n",&n);        // reading the number of integers present in file

	for(int i=0;i<n;i++)
		fscanf(fd,"%d\n",&array[i]);   // copying file data into array
			
	int o=0;
	printf("Enter the element to be searched:");
	scanf("%d",&k);   
	fclose(fd);
        n--;

pipe(pd);       // creating the pipe for communicating between processes
	write(pd[1],&o,sizeof(int));    // writing the starting of the array
	write(pd[1],&n,sizeof(int));    // writing end of the array

divide();
	return 0;
}
