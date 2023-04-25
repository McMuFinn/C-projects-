#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

int check_isbn10(uint64_t isbn10) {
  //Max valid isbn numbers in decimal format
  uint64_t maxValidISBN = 10999999998;
  if(isbn10 > maxValidISBN||isbn10 < 11){
  return 0;
  }

  uint64_t isbn10Copy = isbn10;

  uint64_t mulArr[10] ={0,11, 110, 1100, 11000, 110000, 1100000, 11000000, 110000000, 1100000000};
  uint64_t numDissected[11]; //will hold all digits of the decimal format of the isbn
  uint64_t isbnConverted[10]; //will hold all digits of the actual isbn
  uint64_t currNum;
  uint64_t ergebniss;
  uint64_t crossSum = 0;

  for(int i = 0; i < 10; i++){
        numDissected[i] = isbn10Copy % 10; //adds current ones to correct place in array
    	isbn10Copy/=10; //shifts subtotal over one decimal place
  }
  numDissected[10] = isbn10Copy;

  isbn10Copy = isbn10;

  if(numDissected[10] == 1){
    currNum = 9;
  } else {
        currNum = numDissected[9];
  }

  for(int i = 9; i > 0; i--){
   ergebniss = currNum * mulArr[i];
    
   while(isbn10Copy-ergebniss > maxValidISBN){
    	currNum--;
    	ergebniss = currNum * mulArr[i];
   }
        isbnConverted[i] = currNum;
        isbn10Copy -= ergebniss;
  }
    
  isbnConverted[0] = isbn10Copy;
  
  for(int i = 9; i>0;i--){
  crossSum += isbnConverted[i] * i+1;
  }

   if(crossSum % 11 == 0){
   return 1;
   }
   return 0;

}

int main(int arc, char *argv[]){
uint64_t result = check_isbn10(8992783381);
printf("%"PRIu64"\n",result); 
}
