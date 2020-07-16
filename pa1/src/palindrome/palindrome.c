#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
   
   char *givenString = argv[1];
   
   int stringLength = strlen(givenString);
   int beg = 0;
   int end = stringLength-1;  
   int checkFinal = 0;
   while(beg<=end){
      char lowChar = toupper(givenString[beg]);//uppercase of begining value
      char highChar = toupper(givenString[end]);//uppercase of ending value
      if(!(lowChar>='A' && lowChar<='Z')){
         beg++;
      }
      
      else if(!(highChar>='A' && highChar<='Z' )){
         end--;   
      }
      else if(lowChar == highChar){
         beg++;
         end--;
      }
      else{
         checkFinal = 1;
         break;
      }
   }
   if(checkFinal == 0){
      printf("yes");
   }
   else{
      printf("no");
   }
   
   return 0;
}