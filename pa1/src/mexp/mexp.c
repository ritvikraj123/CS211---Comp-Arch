#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    
    FILE *inputFile;
    inputFile = fopen(argv[1], "r");

    if (inputFile == NULL){
        printf("Unable to open file\n");
        return 0;
    }
    int i, j, k, m, n, count;
    fscanf(inputFile, "%d", &n);
    int **Matrix = (int **)malloc(n * sizeof(int *));
    int **Matrix2 = (int **)malloc(n * sizeof(int *));
    int **result = (int **)malloc(n*sizeof(int *));
    for (i = 0; i < n; i++){
        Matrix[i] = (int *)malloc(n * sizeof(int));
        Matrix2[i] = (int *)malloc(n * sizeof(int));
        result[i] = (int *)malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            fscanf(inputFile, "%d", &Matrix[i][j]);
            Matrix2[i][j] = Matrix[i][j];
        }
    }
    fscanf(inputFile, "%d", &count);
    for (m = 0; m < count-1; m++){
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                result[i][j] = 0;
                for (k = 0; k < n; k++){
                    result[i][j] += Matrix[i][k] * Matrix2[k][j];
                }

            }
        }
        for(i=0;i<n; i++){
            for(j=0;j<n; j++){
                Matrix[i][j] = result[i][j];
            }
        }
    }

    for(i=0;i<n; i++){
        for(j=0;j<n; j++){
            printf("%d", result[i][j]);
            if(j!=n-1){ printf(" ");}
        }
        printf("\n");
    }

    fclose(inputFile);

    return 0;

}