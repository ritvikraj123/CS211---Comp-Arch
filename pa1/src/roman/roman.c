#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int num = atoi(argv[1]);
    int remain;
    int fin;

    if (num == 0){
        return 0;
    }

    while(num != 0){
        if(num>=1000){
            remain = num % 1000;
            fin = num / 1000;
            for (int i = 0; fin>i; fin--){
                printf("M");
            }
            num = remain;    
        }
        if(num>=900){
            remain = num % 900;
            fin = num / 900;
            for (int i = 0; fin>i; fin--){
                printf("CM"); 
            }
            num = remain;
        }
        if(num>=500){
            remain = num % 500;
            fin = num / 500;
            for (int i = 0; fin>i; fin--){
                printf("D");
            }
            num = remain;
        }
        if(num>=400){
            remain = num % 400;
            fin = num / 400;
            for (int i = 0; fin>i; fin--){
                printf("CD");
            }
            num = remain;
        }
        if(num>=100){
            remain = num % 100;
            fin = num / 100;
            for (int i = 0; fin>i; fin--){
                printf("C");
            }
            num = remain;
        }
        if(num>=90){
            remain = num % 90;
            fin = num / 90;
            for (int i = 0; fin>i; fin--){
                printf("XC");
            }
            num = remain;
        }
        if(num>=50){
            remain = num % 50;
            fin = num / 50;
            for (int i = 0; fin>i; fin--){
                printf("L");
            }
            num = remain;
        }
        if(num>=40){
            remain = num % 40;
            fin = num / 40;
            for (int i = 0; fin>i; fin--){
                printf("XL");
            }
            num = remain;
        }
        if(num>=10){
            remain = num % 10;
            fin = num / 10;
            for (int i = 0; fin>i; fin--){
                printf("X");
            }
            num = remain;
        }
        if(num>=9){
            remain = num % 9;
            fin = num / 9;
            for (int i = 0; fin>i; fin--){
                printf("IX");
            }
            num = remain;
        }
        if(num>=5){
            remain = num % 5;
            fin = num / 5;
            for (int i = 0; fin>i; fin--){
                printf("V");
            }
            num = remain;
        }
        if(num>=4){
            remain = num % 4;
            fin = num / 4;
            for (int i = 0; fin>i; fin--){
                printf("IV");
            } 
            num = remain;
        }
        if(num>=1){
            for (int i = 0; num>i; fin--){
                printf("I");
                num--;
            }
        }
    }
    return 0;
}


