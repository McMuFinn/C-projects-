#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
struct BFState{
size_t array_len;
uint8_t* array;
uint8_t* cur;
};

int brainfuck(struct BFState* state, const char* program){
size_t progLength = 0;
uint8_t closed = 0;

while(program[progLength]!= '\0'){
        char c = program[progLength];
        if(c=='['){
        closed++;
        }
        if(c==']'){
        closed--;
        }
    progLength++;
    }

if(closed != 0){
        return -1;
}

char programIns[8192]= {0};
char* programInsPtr = &programIns[0];
  
for(uint8_t i = 0; i<progLength; i++){
        char c = program[i];
        if(c=='+'||c=='-'||c=='<'||c=='>'||c=='['||c==']'||c=='.'||c==','){
                *programInsPtr = c;
                 programInsPtr++;
        }else if(c == '\0'){
	break;
	}
    }

size_t index = 0;

while(index < progLength){
char currIns = programIns[index];

switch(currIns){
        case '[':
                if(*state->cur==0){
                int nestingLayer = 1;
                        while(nestingLayer>0){
                        ++index;
                        currIns = programIns[index];
                                if(currIns=='['){
                                ++nestingLayer;
                                }else if(currIns==']'){
                                --nestingLayer;
                                }
                        }
                }
                ++index;
                break;

        case ']':
                if(*state->cur!=0){
                int nestingLayer = 1;
                        while(nestingLayer > 0){
                        index--;
                        currIns = programIns[index];
                                if(currIns == '['){
                                --nestingLayer;
                                }else if(currIns == ']'){
                                ++nestingLayer;
                                }
                        }
                }else{
                ++index;
                }
                break;

        case '.':
                //putchar(*state->cur);
                ++index;
                break;

        case ',':
                //(*state->cur)=getchar();
                ++index;
                break;

        case '-':
                (*state->cur)++;
                ++index;
                break;

        case '+':
                (*state->cur)++;
                ++index;
                break;

        case '>':
                ++(state->cur);
                if((state->cur - state->array) >= state->array_len){
                return -1;
                }
                ++index;
                break;

        case '<':
                --(state->cur);
                if(state->cur < state->array){
                return -1;
                }
                ++index;
                break;

        case '\0':
                break;

        } //Switch statement
 } //While loop
return 0;
}

int main(int argc, char* argv[]){
struct BFState testState;
testState.array=(uint8_t[]){1,2,3,4,5,6};
testState.array_len=6;
testState.cur=(uint8_t*) testState.array;
uint8_t output = brainfuck(&testState, "just comments no commands");
printf("%d",output);
}
