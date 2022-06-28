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

//https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers

static inline void inc(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	++*mem;
	#ifdef DEBUG
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void dec(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	--*mem;
        #ifdef DEBUG
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void right(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	++mem;
        #ifdef DEBUG
        ++m;
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void left(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	--mem;
        #ifdef DEBUG
        ++m;
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void open(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
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
}
static inline void close(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	#ifdef DEBUG
	printf("%u, %c",*exec,*exec);
	#endif
	if(stackTop==loopStack){
		printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!\nUnballanced brackets\n!!!!!!!!!!!!!!!!!!!!!!!\n");
		return 1;
	}
	--stackTop;
	f(*mem)exec=*stackTop-1;
}
static inline void put(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	#ifdef DEBUG
	printf("%u, %c : ",*exec,*exec);
	#endif
	putchar(*mem);
}
static inline void read(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	#ifdef DEBUG
	printf("%u, %c : ",*exec,*exec);
	#endif
	*mem = getchar();
}
static inline (*op[8])(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop)
	
#ifdef DEBUG
unsigned int m;
#endif
	
int Brfk(volatile char *exec, volatile unsigned int *mem){
	
    op[0] = inc;
    op[1] = dec;
    op[2] = right;
    op[3] = left;
    op[4] = open;
    op[5] = close;
    op[6] = put;
    op[7] = read;
    #ifdef DEBUG
    m=0;
    int start = exec;
    #endif
	char** loopStack=(char**)calloc(256,sizeof(char*));
	char** stackTop=loopStack;
	unsigned short int bridge=0;
    while(*exec!=0){
        #ifdef DEBUG
        printf("%u, %u, %u, ",exec-start, *mem, m);
        #endif
	/*
        determin index
	call op[index]
	*/
        #ifdef DEBUG
        putchar('\n');
        #endif
        exec++;
    }
	putchar('\n');
	return 0;
}
