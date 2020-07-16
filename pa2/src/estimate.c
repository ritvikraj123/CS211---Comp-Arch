/* PA2 estimate */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//void printMatrix(double**matrix, int rows, int cols);
double** transpose(double**trainmatrix,int tranRows,int tranCols);
double** multiply(double** matrix1, double** matrix2,int row1,int row2,int col1, int col2);

double** inverse(double ** matrix,int row,int col);
double** reduceto1inAug(double** sample, int i, int j,int row,int col);
double** reduceto0inEche(double** sample, int i, int j,int row,int col);
double** findRowEchelon(double** sample, int i, int j,int row,int col);
double** findFinalResult(double** test, double** w,int row,int col);



int main (int argc, char** argv){
	double** trainmatrix;
	double** Y;
	double** testmatrix;
	double** transposeMatrix;
	double** multiplyMatrix;
	double** inverseMatrix; 
	double** xtxinversetran;
	double** finalW;
	double** finalResult;

	

	FILE* train = fopen(argv[1], "r");
	FILE* data = fopen(argv[2], "r");


	if(train == NULL){
		printf("file does not exist\n");
		exit(0);
	}
	if(data == NULL){
		printf("file does not exist\n");
		exit(0);
	}
	
	char word [50];
	fscanf(train, "%s\n", word);

	char word2 [50];
	fscanf(data, "%s\n", word2);

	//double num = 0;
	int rows;
	int cols;
	fscanf(train, "%d\n%d\n", &cols, &rows);

	int numTest;//rows
	int atr;//columns
	fscanf(data, "%d\n%d\n", &atr, &numTest);

	testmatrix=(double**)malloc(numTest*sizeof(double*));
	for(int i=0;i<numTest;i++){
		testmatrix[i]=(double*)malloc((atr)*sizeof(double));
	}

	for(int i=0;i<numTest;i++){
		for(int j=0;j<atr;j++){
			fscanf(data,"%lf",&testmatrix[i][j]);
		}
		fscanf(data,"\n");
	}

	/*if(fscanf(fp, "%d\n%d\n", &cols, &rows)>0){
		//fscanf(fp, "%d", &cols);
		matrix = malloc(rows * sizeof(double*));
		
	}
	*/
/*
	printf("%s\n", word);
	printf("%d\n", rows);
	printf("%d\n", cols);
*/

	int i;
	int j;
	trainmatrix=(double**)malloc(rows*sizeof(double*));
	for(i=0;i<rows;i++){
		trainmatrix[i]=(double*)malloc((cols+1)*sizeof(double));
	}

	Y=(double**)malloc(rows*sizeof(double*));
	for(i=0;i<rows;i++){
		Y[i]=(double*)malloc(1*sizeof(double));
	}

	for(i=0;i<rows;i++){
		for(j=1;j<=cols;j++){
			fscanf(train,"%lf",&trainmatrix[i][j]);

		}
		fscanf(train,"%lf",&Y[i][0]);
		fscanf(train,"\n");
	}
	for(i=0;i<rows;i++){
		trainmatrix[i][0]=1;
	}
	/*
	printf("Train matrix:\n");
	for (int i=0; i<rows; i++){
		for(int j=0; j<cols+1; j++){
			printf("%lf\t", trainmatrix[i][j]);
		}printf("\n");
	}
	printf("Y matrix:\n");
	for (int i=0; i<rows; i++){
		for(int j=0; j<1; j++){
			printf("%lf\t", Y[i][j]);
		}printf("\n");
	}
	*/
	//printf("Train matrix:\n");
	//printMatrix(trainmatrix, rows, (cols+1));
	//printf("\n");

	//printf("Test matrix:\n");
	//printMatrix(testmatrix, numTest, atr);
	//printf("\n");

	//printf("Y matrix:\n");
	//printMatrix(Y, rows, 1);
	//printf("\n");

	//printf("Transpose matrix:\n");
	transposeMatrix = transpose(trainmatrix, (cols+1), rows);	
	//printMatrix(transposeMatrix, (cols+1), rows);
	//printf("\n");

	//printf("Multiplied matrix:\n");
	multiplyMatrix = multiply(transposeMatrix, trainmatrix, (cols+1), rows, rows, (cols+1));
	//printMatrix(multiplyMatrix, (cols+1), (cols+1));
	//printf("\n");

	//printf("Inverse matrix:\n");
	inverseMatrix = inverse(multiplyMatrix, (cols+1), (cols+1));
	//printMatrix(inverseMatrix, (cols+1), (cols+1));
	//printf("\n");

	//printf("xtxinversetran matrix:\n");
	xtxinversetran = multiply(inverseMatrix, transposeMatrix, (cols+1), cols+1, cols+1, rows);
	//printMatrix(xtxinversetran, (cols+1), rows);
	//printf("\n");

	//printf("W matrix:\n");
	finalW = multiply(xtxinversetran, Y, (cols+1), rows, rows, 1);
	//printMatrix(finalW, (cols+1), 1);
	//printf("\n");

	//printf("Final matrix:\n");
	finalResult = findFinalResult(testmatrix,finalW,numTest,atr);

	
	for (int i=0; i<numTest; i++){
		for(int j=0; j<1; j++){
			printf("%.0f\n", finalResult[i][j]);
		}
	}
	

	/*printf("Orignal matrix:\n");
	for(int i = 0; i<rows; i++){
		matrix[i] = malloc((cols+1) * sizeof(double*));
		for(int j=0; j<(cols+1); j++){
			if(fscanf(fp, "%lf\t", &num)>0){
				matrix[i][j] = num;
			}
			printf("%lf\t", matrix[i][j]);
		}printf("\n");
	}printf("\n");
	*/

/*
	printf("Transpose matrix:\n");
	int tranRows = (cols+1);
	int tranCols = rows;
	double** transpose;
	transpose = malloc(tranRows * sizeof(double*));
	for (int i = 0; i<tranRows; i++){
		transpose[i] = malloc(tranCols * sizeof(double*));
		for(int j = 0; j<tranCols; j++){
			transpose[i][j] = trainmatrix[j][i];
		}
	}
	for (int i=0; i<tranRows; i++){
		for(int j=0; j<tranCols; j++){
			printf("%lf\t", transpose[i][j]);
		}printf("\n");
	}
	printf("\n");
*/


/*
	printf("Multiplied Matrix:\n");
	int mulRows = rows;
	int mulCols = tranCols;
	double ** multiply;
	float sum = 0;
	multiply = malloc(mulRows * sizeof(double*));
	for (int i = 0; i<mulRows; i++){
		multiply[i] = malloc((mulCols) * sizeof(double));
	}
	for(int i = 0; i< mulRows; i++){
		for (int j = 0; j < mulCols; j++){
			for (int k = 0; k<tranRows; k++){
				sum = sum + trainmatrix[i][k]*transpose[k][j];
			}
			multiply[i][j] = sum;
			sum = 0;
		}
	}
	for (int i=0; i<mulRows; i++){
		for(int j=0; j<mulCols; j++){
			printf("%lf\t", multiply[i][j]);
		}printf("\n");
	}
	printf("\n");
*/

	




	/*printf("\n");
	//Augmenting Identity matrix
	int order = mulRows;
	for(int i=0; i<order; i++){
		for(int j=0; j<order; j++){
			if(i==j){
				inverse[i][j+order] = 1;
			}
			else{
				inverse[i][j+order] = 0;
			}
		}
	}
	printf("works2");

	//Gauss Jordan
	float ratio;
	for(int i=0; i<order; i++){
		for(int j=0; j<order; j++){
			if(i!=j)
			{
				ratio = inverse[j][i]/inverse[i][i];
				for(int k=0; k<2*order; k++)
				{
					inverse[j][k] = inverse[j][k] - ratio*inverse[i][k];
				}
			}
		}
	}
	//Row Operation to Make Principal Diagonal to 1 
	for(int i=0; i<=order; i++){
		for(int j=order+1; j<=2*order; j++){
			inverse[i][j] = inverse[i][j]/inverse[i][i];
		}
	}
	//print inverse
	for(int i=0;i<=order; i++){
		for(int j=order+1;j<=2*order;j++){
			printf("%lf\t",inverse[i][j]);
		}
	printf("\n");
	}*/

	free(trainmatrix);
	free(Y);
	free(testmatrix);
	free(transposeMatrix);
	free(multiplyMatrix);
	free(inverseMatrix);
	free(xtxinversetran);
	free(finalW);
	free(finalResult);

	return 0;

	fprintf(stderr, "%s: not implemented\n", argv[0]);
	
	return EXIT_FAILURE;
}

double** transpose(double**trainmatrix,int tranRows,int tranCols){
	double** transposeMatrix;
	transposeMatrix = malloc(tranRows * sizeof(double*));
	for (int i = 0; i<tranRows; i++){
		transposeMatrix[i] = malloc(tranCols * sizeof(double*));
		for(int j = 0; j<tranCols; j++){
			transposeMatrix[i][j] = trainmatrix[j][i];
		}
	}
	return transposeMatrix;
}

double** multiply(double** matrix1, double** matrix2,int row1,int col1,int row2, int col2){

	double** multiplyMatrix=(double**)malloc(row1*sizeof(double*));
	double sum=0;
	for(int a=0; a<row1; a++){
		multiplyMatrix[a]=(double*)malloc((col2)*sizeof(double));
	}
	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			for(int k=0; k<row2; k++){
				sum = sum + matrix1[i][k]*matrix2[k][j];

			}
			multiplyMatrix[i][j]=sum;
			sum=0;
		}
	}
	return multiplyMatrix;
}
/*
void printMatrix(double**matrix, int rows, int cols){
	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			printf("%lf\t", matrix[i][j]);
		}
		printf("\n");
	}
}
*/

double** inverse(double ** matrix,int row,int col){
	double** result=(double**)malloc(row*sizeof(double*));
	for(int i=0; i<row; i++){
		result[i]=(double*)malloc((col*2)*sizeof(double));
	}

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			result[i][j]=matrix[i][j];
		}
	}
	for(int i=0; i<row; i++){
		for(int j=col; j<(col*2); j++){
			if(j-col==i){
				result[i][j]=1;
			}else{
				result[i][j]=0;
			}

		}
	}
	//printf("checkpoint 1");
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			if(i==j){//pivot
				result=reduceto1inAug(result,i,j,row,col*2);
				for(int k=i+1; k<row; k++){
					result=reduceto0inEche(result,k,j,row,col*2);
				}
			}
		}

	}
	//printf("checkpoint 2");

	for(int i=row-1; i>=0; i--){
		for(int j=col-1; j>=0; j--){
			if(i!=j&&result[i][j]!=0){
				result=findRowEchelon(result,i,j,row,col*2);
			}

		}
	}
	//printf("checkpoint 3");

	double** final=(double**)malloc(row*sizeof(double*));
	for(int i=0; i<row; i++){
		final[i]=(double*)malloc((col)*sizeof(double));
	}
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			final[i][j]=result[i][j+col];
		}
	}

	return final;
}

double** reduceto1inAug(double** input, int i, int j, int row, int col){

	double** output=(double**)malloc(row*sizeof(double*));
	for(int a=0; a<row; a++){
		output[a]=(double*)malloc((col)*sizeof(double));
	}

	for(int a=0;a<row;a++){
		for(int b=0;b<col;b++){
			output[a][b] = input[a][b];
		}
	}

	double temp;
		if(output[i][j]==1){
			return output;
		}
		else if(output[i][j]==0){
			for(int c=1; c<row; c++){
				if(output[c][j]!=0){
					for(int d=0; d<col; d++){
						output[i][d] = output[i][d] + output[c][d];
					}
				return output;
				}


			}
			//printf("error");
			return output;

		}
		else{
			temp=output[i][j];
			for(int c=0; c<col; c++){
				output[i][c] = output[i][c] / temp;
			}
			return output;
		}
	//printf("error");
	return output;
}

double** reduceto0inEche(double** input, int i, int j,int row,int col){
	if(input[i][j]==0){
		return input;
	}
	double** output=(double**)malloc(row*sizeof(double*));
	for(int a=0; a<row; a++){
		output[a]=(double*)malloc((col)*sizeof(double));
	}

	for(int a=0; a<row; a++){
		for(int b=0; b<col; b++){
			output[a][b]=input[a][b];
		}
	}

	double temp=output[i][j];

	for(int b=0; b<col; b++){
		output[i][b]=output[i][b]/temp;

	}

	for(int c=0; c<col; c++){
		output[i][c]=output[i][c]-output[j][c];
	}

	return output;

}

double** findRowEchelon(double** input, int i, int j,int row,int col){
	if(input[i][j]==0){
		return input;
	}
	double** output=(double**)malloc(row*sizeof(double*));
	for(int a=0; a<row; a++){
		output[a]=(double*)malloc((col)*sizeof(double));
	}

	for(int a=0; a<row; a++){
		for(int b=0; b<col; b++){
			output[a][b]=input[a][b];
		}
	}

	double temp=output[i][j];

	for(int c=0; c<col; c++){
		output[i][c]=output[i][c]-(output[j][c]*temp);
	}


	return output;

}

double** findFinalResult(double** data, double** finalW,int row,int col){
	double temp=0;

	double** finalResult=(double**)malloc(row*sizeof(double*));
	for(int a=0; a<row; a++){
		finalResult[a]=(double*)malloc(1*sizeof(double));
	}

	for(int a=0; a<row; a++){
		temp=finalW[0][0];
		for(int b=0; b<col; b++){
			temp = temp + (data[a][b]*finalW[b+1][0]);
		}
		finalResult[a][0] = temp;
	}
	return finalResult;
}