/*
ascii of valid instructions
+ : 43 : *mem++
- : 45 : *mem--
> : 62 : mem++
< : 60 : mem--
[ : 91 : if(!*mem) while(*exec!=93) exec++
] : 93 : if(*mem) while(*exec!=91) exec--
. : 46 : putchar(*mem)
, : 44 : getchar(*mem)
*/

int Brfk(volatile char *exec, volatile unsigned int *mem){
    #ifdef DEBUG
    int start = exec;
    unsigned int m=0;
    #endif
	char** loopStack=(char**)calloc(256,sizeof(char*));
	char** stackTop=loopStack;
	unsigned short int bridge=0;
    while(*exec!=0){
        #ifdef DEBUG
        printf("%u, %u, %u, ",exec-start, *mem, m);
        #endif
        switch(*exec){
            case 43:
                ++*mem;
                #ifdef DEBUG
                printf("%u, %c",*exec,*exec);
                #endif
                break;
            case 45:
                --*mem;
                #ifdef DEBUG
                printf("%u, %c",*exec,*exec);
                #endif
                break;
            case 62:
                ++mem;
                #ifdef DEBUG
                ++m;
                printf("%u, %c",*exec,*exec);
                #endif
                break;
            case 60:
                --mem;
                #ifdef DEBUG
                ++m;
                printf("%u, %c",*exec,*exec);
                #endif
                break;
            case 91:
                #ifdef DEBUG
                printf("%u, %c",*exec,*exec);
                #endif
				*stackTop=exec;
				++stackTop;
				if(!*mem){
					++bridge;
					while(bridge){
						++exec;
						bridge=bridge+(*exec==91)-(*exec==93);
					}
				}
                break;
            case 93:
                #ifdef DEBUG
                printf("%u, %c",*exec,*exec);
                #endif
				if(stackTop==loopStack){
					printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!\nUnballanced brackets\n!!!!!!!!!!!!!!!!!!!!!!!\n");
					return 1;
				}
				--stackTop;
				if(*mem)exec=*stackTop-1;
                break;
            case 46:
                #ifdef DEBUG
                printf("%u, %c : ",*exec,*exec);
                #endif
                putchar(*mem);
                break;
            case 44:
                #ifdef DEBUG
                printf("%u, %c : ",*exec,*exec);
                #endif
                *mem = getchar();
                break;
        }
        #ifdef DEBUG
        putchar('\n');
        #endif
        exec++;
    }
	putchar('\n');
	return 0;
}
