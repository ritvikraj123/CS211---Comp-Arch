
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// segmentation fault for last example
int main(int argc, char *argv[]) {
  char input[100];
  char output[100];
  strcpy(input,argv[1]);
  int len=strlen(input);
  int counter=1;
  char current;
  char prevNode=input[0];
  int position=0;

  for (int i=1; i<len; i++) {
    current=input[i];
    if(current>='0' && current<='9') {
      printf("error");
      return 0;
    }//check for error

    else if (current==prevNode) {
      counter++;
      if (i==len-1) {
        output[position]=prevNode;
        sprintf(&output[position+1],"%d",counter);
      }     
    }

    else {
      output[position]=prevNode;
      sprintf(&output[position+1],"%d",counter);
      position=strlen(output);

      if (i+1==len) {
        output[position]=current;
        output[position+1]='1';
      }
      counter=1;
    }
    prevNode=current;
  }
  int outputlen=strlen(output);
  if (outputlen>len) {
    printf("%s",input);
  }
  else {
    printf("%s",output);
  }
  return 0;
}