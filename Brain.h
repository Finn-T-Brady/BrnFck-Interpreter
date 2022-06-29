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

in order of ascii value
43 inc
44 read
45 dec
46 put
60 left
62 right
91 open
93 close  --  irrelevant during index calculation

index = (*mem>43) + (*mem>44) + (*mem>45) + (*mem>46) + (*mem>60) + (*mem>62) + (*mem>91)
*/

//https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers

static inline void br_inc(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	++*mem;
	#ifdef DEBUG
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void br_dec(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	--*mem;
        #ifdef DEBUG
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void br_right(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	++mem;
        #ifdef DEBUG
        ++m;
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void br_left(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	--mem;
        #ifdef DEBUG
        ++m;
        printf("%u, %c",*exec,*exec);
        #endif
}
static inline void br_open(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
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
static inline void br_close(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
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
static inline void br_put(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
	#ifdef DEBUG
	printf("%u, %c : ",*exec,*exec);
	#endif
	putchar(*mem);
}
static inline void br_read(volatile unsigned int *mem, volatile char *exec,unsigned short int bridge, char** loopStack, char** stackTop){
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
	
    op[0] = br_inc;
    op[1] = br_dec;
    op[2] = br_right;
    op[3] = br_left;
    op[4] = br_open;
    op[5] = br_close;
    op[6] = br_put;
    op[7] = br_read;
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
