/* CS 211 PA4
 * Created for: rr1032
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct truthTable {char str[17]; int NumInputs; int MultiplexerCnt; int *inputs; int *outputs; int *sec;};

int indexOf(int size, char **arr, char *var) {
    int i = 0;
	while(i < size){
		if (strcmp(arr[i], var) == 0) {
            return i;
        }
		i++;
	}
    return -1;
}//find correct placment

int increaseInputs(int *values, int inpCnt) {
    int i = inpCnt + 1;
	while(i >=2){
		values[i] = !values[i];
        if (values[i] == 1) {
            return 1;
        }
		i--;
	}
    return 0;
}//traverse though inputs


int main(int argc, char** argv) {
    if (argc - 1 != 1) {
        return 0;
    }
	//define variables
	int arrCnt = 0;
    struct truthTable* arrs = NULL;
    int size = 2;
    int inpCnt = 0;
    int outCnt = 0;
    int tcount = 0;
    char tableArrayData[17];
    char **dataName;
    int *values = malloc(size * sizeof(int));
	int i = 0;

	//open file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        return 0;
    }

	//reading inputs
    fscanf(file, " %s", tableArrayData);
    fscanf(file, "%d", &inpCnt);

    size = size + inpCnt;
    dataName = malloc(size * sizeof(char *));
    dataName[0] = malloc(2 * sizeof(char));
    dataName[0] = "0\0";
    dataName[1] = malloc(2 * sizeof(char));
    dataName[1] = "1\0";
	while(i < inpCnt){
		dataName[i + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", dataName[i + 2]);
		i++;
	}

    //reading outputs
    fscanf(file, " %s", tableArrayData);
    fscanf(file, "%d", &outCnt);
    size = size + outCnt;
    dataName = realloc(dataName, size * sizeof(char *));
	i = 0;
	while (i < outCnt){
		dataName[i + inpCnt + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", dataName[i + inpCnt + 2]);
		i++;
	}

    //solve
    while (!feof(file)) {
        int numInputs = 0;
		int numOutputs = 1;
        struct truthTable arr;
        int inArgs = fscanf(file, " %s", tableArrayData); 
        if (inArgs != 1) {
            break;
        }
        arrCnt = arrCnt + 1;
        arr.NumInputs = 0;
        arr.MultiplexerCnt = 0;//only for mux
        strcpy(arr.str, tableArrayData);//copying string

        if (strcmp(tableArrayData, "NOT") == 0) {
            numInputs = 1;
			numOutputs = 1;
        }
        else if (strcmp(tableArrayData, "PASS") == 0) {
            numInputs = 1;
			numOutputs = 1;
        }
		else if (strcmp(tableArrayData, "AND") == 0) {
            numInputs = 2;
			numOutputs = 1;
        }
		else if (strcmp(tableArrayData, "OR") == 0) {
            numInputs = 2;
			numOutputs = 1;
        }
		else if (strcmp(tableArrayData, "NAND") == 0) {
            numInputs = 2;
			numOutputs = 1;
        }
		else if (strcmp(tableArrayData, "NOR") == 0) {
            numInputs = 2;
			numOutputs = 1;
        }
		else if (strcmp(tableArrayData, "XOR") == 0) {
            numInputs = 2;
			numOutputs = 1;
        }
        else if (strcmp(tableArrayData, "DECODER") == 0) {
            fscanf(file, "%d", &numInputs);
            arr.NumInputs = numInputs;
            numOutputs = pow(2, numInputs);
        }
        else if (strcmp(tableArrayData, "MULTIPLEXER") == 0) {
            fscanf(file, "%d", &numInputs);
            arr.MultiplexerCnt = numInputs;
            numInputs = pow(2, numInputs);
        }

        arr.inputs = malloc(numInputs * sizeof(int));
        arr.outputs = malloc(numOutputs * sizeof(int));
        arr.sec = malloc(arr.MultiplexerCnt * sizeof(int));

        char ans[17];
		//inputs
		i = 0;
		while(i < numInputs){
			fscanf(file, "%*[: ]%16s", ans);
            arr.inputs[i] = indexOf(size, dataName, ans);
			i++;
		}
		//Multiplexer
		i = 0;
		while(i < arr.MultiplexerCnt){
			fscanf(file, "%*[: ]%16s", ans);
            arr.sec[i] = indexOf(size, dataName, ans);
			i++;
		}
		//outputs
		i = 0;
        while(i < numOutputs){
			fscanf(file, "%*[: ]%16s", ans);
            int IndArray = indexOf(size, dataName, ans);
            if (IndArray == -1) {
                size = size + 1;
                tcount = tcount + 1;
                dataName = realloc(dataName, size * sizeof(char *));
                dataName[size - 1] = malloc(17 * sizeof(char));
                strcpy(dataName[size - 1], ans);
                arr.outputs[i] = size - 1;
            }
            else {
                arr.outputs[i] = IndArray;
            }
			i++;
		}
        
        //add array content
        if (!arrs) {
            arrs = malloc(sizeof(struct truthTable));
        } 
		else {
            arrs = realloc(arrs, arrCnt * sizeof(struct truthTable));
        }
        arrs[arrCnt - 1] = arr;
    }

    // initialize values array
    values = malloc(size * sizeof(int));
    i = 0;
	while(i < size){
		values[i] = 0;
		i++;
	}
    values[1] = 1;

    while(1 < 2) {
        //start print table
		i = 0;
		while(i < inpCnt){
			 printf("%d ", values[i + 2]);
			 i++;
		}
		printf("|");
            
        //run through array
        i = 0;
		while(i < arrCnt){
			struct truthTable arr = arrs[i];
            if (strcmp(arr.str, "NOT") == 0) {
				values[arr.outputs[0]] = !values[arr.inputs[0]];
            }//NOT evaluation
			else if (strcmp(arr.str, "PASS") == 0) {
				values[arr.outputs[0]] = values[arr.inputs[0]];
            }//PASS evaluation
            else if (strcmp(arr.str, "AND") == 0) {
				values[arr.outputs[0]] = values[arr.inputs[0]] && values[arr.inputs[1]];
            }//AND evaluation
            else if (strcmp(arr.str, "OR") == 0) {
				values[arr.outputs[0]] = values[arr.inputs[0]] || values[arr.inputs[1]];
            }//OR evaluation
            else if (strcmp(arr.str, "NAND") == 0) {
				values[arr.outputs[0]] = !(values[arr.inputs[0]] && values[arr.inputs[1]]);
            }//NAND evaluation
            else if (strcmp(arr.str, "NOR") == 0) {
				values[arr.outputs[0]] = !(values[arr.inputs[0]] || values[arr.inputs[1]]);
            }//NOR evaluation
            else if (strcmp(arr.str, "XOR") == 0) {
                values[arr.outputs[0]] = values[arr.inputs[0]] ^ values[arr.inputs[1]];

            }//XOR evaluation
			
            else if (strcmp(arr.str, "DECODER") == 0) {
                int temp = 0;
				int i = 0;
				while(i < pow(2, arr.NumInputs)){
					values[arr.outputs[i]] = 0;
					i++;
				}
				i = 0;
				while(i<arr.NumInputs){
					temp = temp + values[arr.inputs[i]] * pow(2, arr.NumInputs - i - 1);
					i++;
				}
				values[arr.outputs[temp]] = 1;
            }//DECODER computation

            else if (strcmp(arr.str, "MULTIPLEXER") == 0) {
                int temp = 0;
    			int i = 0;
				while(i < arr.MultiplexerCnt){
					temp = temp + values[arr.sec[i]] * pow(2, arr.MultiplexerCnt - i - 1);
					i++;
				}
   				values[arr.outputs[0]] = values[arr.inputs[temp]];
            }//MULTIPLEXER computation
			i++;
		}

        //print output table
        for (i = 0; i < outCnt; i++) {
            printf(" %d", values[inpCnt + i + 2]);
        }
        printf("\n");

        if (!increaseInputs(values, inpCnt)) {
            break;
        }
    }

    return 0;
}