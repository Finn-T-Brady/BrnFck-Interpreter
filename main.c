#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Brain.h"

int main(int argc, char *argv[]) {

    //input validation
    
    //checking if there are more arguments than the program name
    if(argc==1) {
        printf("No File Specified\n");
        return 1;
    }
    
    char fname[256];//declaring a space for the file name
    char file[131072];//declaring a space for the file

    int flag=1;//flag position
    int _flag=0;//flag found
    int _file=0;//filename present

    //checking for an argument that starts with a "-" to declare a flag
    while(flag<argc && !_flag) {
        if(argv[flag][0]==45){//comparing to ascii value of "-"
            _flag=1;
        }else{
            flag++;
        }
    }

    //concatenating all arguments between program name and flags to form complete file name
    if(flag>1){
        _file=1;//file name is present
        strcpy(fname,argv[1]);
        for(int i=2;i<flag;i++) {
            strcat(fname," ");
            strcat(fname,argv[i]);
        }
    }

    
    //checking file exists and can be read
    #ifdef DEBUG
    int EXIST=0,READ=0;//debug variables
    #endif
    if(_file){
        if(access(fname,F_OK) != -1){
            #ifdef DEBUG
            EXIST=1;
            #endif
            if(access(fname,R_OK) !=-1){ 
                #ifdef DEBUG
                READ=1;
                #endif

                //loading file contents
                FILE *fp;
                fp=fopen(fname,"r");
                fscanf(fp,"%s",file);
                fclose(fp);
            }else{
                printf("File specified cannot be read\n");
                #ifndef DEBUG
                return 1;
                #endif
            }
        }else{
            printf("File specified does not exist\n");
            #ifndef DEBUG
            return 1;
            #endif
        }
    }

    //debug info
    #ifdef DEBUG
    printf("argc: %i\n",argc);
    printf("\nfile name given: %s\n",_file ? "true" : "false");
    if(_file){
        printf("-filename: %s\n",fname);
        printf("-file exists: %s\n",EXIST ? "true" : "false");
        printf("-file readable: %s\n", READ ? "true" : "false");
    }
    printf("\nflag found: %s\n",_flag ? "true" : "false");
    if(_flag){
        printf("-flag position: %i\n",flag);
        printf("-flags:\n");
        for(int i=0;i<(argc-flag)/2;i++){
            printf(" -%i: %s %s\n",i,argv[flag+2*i],argv[flag+2*i+1]);
        }
    }
    fflush(stdout);
    fgetc(stdin);
    #endif

    //flag variables
    int S=1024;//array length

    //processing flags
    //i : 105 : append code
    //S : 83 : array length 
    for(int i=0;i<(argc-flag)/2;i++){
        switch (argv[flag+2*i][1]){
        case 105:
            strcat(file,argv[flag+i*2+1]);
            break;

        case 83:
            S=atoi(argv[flag+i*2+1]);
            break;
        }
    }

    unsigned int *mem = calloc(S, sizeof(unsigned int));//declaring variable array for use in execution
    strcat(file,"\0");

    return Brfk(file, mem);
}
