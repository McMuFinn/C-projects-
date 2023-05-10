#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void* memmem(const void* haystack, size_t haystacklen,
             const void* needle, size_t needlelen)
{
  char* charHaystack = (char*)haystack;
  char* charNeedle = (char*)needle;
  uint8_t setFound = 0;
  
  for(int32_t i = 0; i<haystacklen; i++){
    
  		if(charHaystack[i] == charNeedle[0]){
          
     		 	if((haystacklen-1-i) >= needlelen){ //CHECK IF ENOUGH POSSIBLE CHARACTERS LEFT IN STRING (Minus 1 because maxIndex is len-1)    				
    					
               			for(int32_t j = 1; j<needlelen;j++){
        						setFound = 0;
    									if(charHaystack[i+j]==charNeedle[j]){
             								 setFound = 1;
           								 //Do nothing, keep cylcing through loop,setFound true
            								}else{ //Break out of loop (setFound already at 0)
              								break;
            							    	}	
                	        }//closes for loop checking if rest of string matches 
         	  	  	if(setFound == 1){ // check how many zeroes in front 
          						int32_t k = 0;
            							while((i-1)-k>=0 && charHaystack[(i-1)-k] == 0){ //First cond: checks if at beginning of string Second: checks if char == \0
            								k++;  
              								}
            							return (void*)(charHaystack+(i-k));
            				} //closes setFound if statement
            				//Else do nothing (increment)
    		   
      		 }else{ //IF NOT ENOUGH SPACES LEFT IN STRING RETURN NULL (Belongs to second if statement)
      			return NULL;
        	 }
  		}else{ //belongs to first if statement
    		//(!charHaystack[i] == charNeedle[0])
    		//Check if next index when i is incrememnted is in bounds of original array, if so then increment, otherwise break
    		if(i+1>=haystacklen){
    			break;
    		} //else do nothing == increment i
   		 }
  	} //closes outer for loop
  	//returns NULL if no match found
 
 return NULL;
}

int main(int argc, char* argv[]){
const void* haystack = "Hello world!";
size_t haystacklen = 12;
const void* needle = "world";
size_t needlelen = 6;

void* returnPtr = memmem(haystack, haystacklen, needle, needlelen);
char valueAtPtr = *((char*)returnPtr);
printf("%c",valueAtPtr);
return 0;

}
