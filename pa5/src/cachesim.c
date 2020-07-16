#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "first.h"

/* Global variables representing hits and misses
 * * for cacheA and cacheB. 
 *  */
int hitA = 0;
int missA = 0;
int readA = 0;
int writeA = 0;

int hitB = 0;
int missB = 0;
int readB = 0;
int writeB = 0;

int main(int argc, char **argv){
	if(argc != 5){
		printf("Incorrect number of parameters\n");
		exit(0);
	}
	FILE *trace_file = fopen(argv[4], "r");
	int assoc, cache_size, block_size, num_sets, block_offset, set_index, tag;
	if(strcmp(argv[2], "direct") == 0){
		assoc = 1;
		cache_size = atoi(argv[1]);
		block_size = atoi(argv[3]);
		num_sets = cache_size / block_size;
	}else if(strcmp(argv[2], "assoc") == 0){
		cache_size = atoi(argv[1]);
		block_size = atoi(argv[3]);
		assoc = cache_size / block_size;
		num_sets = 1;
	}else{
		assoc = argv[2][6] - '0';
		cache_size = atoi(argv[1]);
                block_size = atoi(argv[3]);
                num_sets = cache_size / (block_size * assoc);
	}
	block_offset = log2(block_size);
        set_index = log2(num_sets);
	tag = 48 - (block_offset + set_index);
	readFile(trace_file, num_sets, tag, set_index, block_offset, assoc);
	fclose(trace_file);
	print();
	return 0;
}

/* Takes a pointer to a text file to read from. Creates cacheA and cacheB using the number of sets,
 * * associativity and tag size. Reads the 3 columns in each line of the file, discarding the program
 *  * counter, and calls necessary functions to get the index bits, tag bits, and calculate the set index
 *   * of each memeory address. Then updates each cache using these variables.
 *    */
void readFile(FILE *trace_file, int num_sets, int tag, int set_index, int block_offset, int assoc){
	struct cache **A = createCache(num_sets, assoc, tag);
	struct cache **B = createCache(num_sets, assoc, tag);
	
	char oper;
	char counter[100];
	char address[20];
	char *temp, *f_bin;
	char *tag_bitsA, *index_bitsA;
	char *tag_bitsB, *index_bitsB;
	int i, j, count, decA, decB;
	while((fscanf(trace_file, "%s %c %s\n", counter, &oper, address) != EOF) && (strcmp(counter, "#eof") != 0)){
		count = 0;
		char *binary = (char *) malloc(sizeof(char) * strlen(address) * 4);
		for(i = 2; i < strlen(address); i++){
			temp = convertHex(address[i]);
			for(j = 0; j < 4; j++){
				binary[count] = temp[j];
				count++;
			}
		}
		
		f_bin = fixBinary(binary);
		
		tag_bitsA = getTagA(f_bin, tag);
		index_bitsA = getIndexA(f_bin, tag, set_index);
		decA = convertBin(index_bitsA, set_index);
		
                index_bitsB = getIndexB(f_bin, set_index);
                tag_bitsB = getTagB(f_bin, tag, set_index);
		decB = convertBin(index_bitsB, set_index);		
		
		updateCache(assoc, A, tag_bitsA, index_bitsA, decA, oper, 0);
		updateCache(assoc, B, tag_bitsB, index_bitsB, decB, oper, 1);
	}
	
	dealloc(A, num_sets, assoc);
	dealloc(B, num_sets, assoc);
}

/* Takes number of sets, associativity, and tag size to create and return a 
 * * cache.
 *  */
struct cache **createCache(int num_sets, int assoc, int tag){
	int r, c, x;
	struct cache **temp = (struct cache **) malloc(sizeof(struct cache*) * num_sets);
	for(r = 0; r < num_sets; r++){
		temp[r] = (struct cache *) malloc(sizeof(struct cache) * assoc);
	}
	for(r = 0; r < num_sets; r++){
		for(c = 0; c < assoc; c++){
			temp[r][c].tag = (char *) malloc(sizeof(char) * (tag + 1));
			temp[r][c].valid = 0;
			temp[r][c].rank = 0;
			for(x = 0; x < tag; x++){
				temp[r][c].tag[x] = '0';
			}
			temp[r][c].tag[tag] = '\0';
		}
	} 
	return temp;
}

/* Takes a character from the the hexadecimal memory address and converts it to binary
 * * and returns it.
 *  */
char *convertHex(char slot){
	char *binary = (char *) malloc(sizeof(char) * 5);
	switch(slot){
		case '0':
			strcat(binary, "0000\0"); break;
		case '1':
                        strcat(binary, "0001\0"); break;
		case '2':
                        strcat(binary, "0010\0"); break;
		case '3':
                        strcat(binary, "0011\0"); break;
		case '4':
                        strcat(binary, "0100\0"); break;
		case '5':
                        strcat(binary, "0101\0"); break;
		case '6':
                        strcat(binary, "0110\0"); break;
		case '7':
                        strcat(binary, "0111\0"); break;
		case '8':
                        strcat(binary, "1000\0"); break;
		case '9':
                        strcat(binary, "1001\0"); break;
		case 'a':
                        strcat(binary, "1010\0"); break;
		case 'b':
                        strcat(binary, "1011\0"); break;
		case 'c':
                        strcat(binary, "1100\0"); break;
		case 'd':
                        strcat(binary, "1101\0"); break;
		case 'e':
                        strcat(binary, "1110\0"); break;
		case 'f':
                        strcat(binary, "1111\0"); break;
		default:
			break;
	}
	return (char *) binary;
}

/* Zero extends the resultant binary from converting the hexadecimal memory address to ensure there
 * * are a total of 48 bits. Sets any of the missing bits to 0.
 *  */
char *fixBinary(char *binary){
	int missing_bits = 48 - strlen(binary);
	char *f_bin = (char *) malloc(sizeof(char) * (strlen(binary) + missing_bits + 1));
	int i;
	for(i = 0; i < missing_bits; i++){
		f_bin[i] = '0';
	}
	f_bin[missing_bits] = '\0';
	strcat(f_bin, binary);
	return (char *) f_bin;
}

/* Gets necessary tag bits from beginning of the zero extended binary.
 * */
char *getTagA(char *f_bin, int tag){
	char *tag_bitsA = (char *) malloc(sizeof(char) * (tag + 1));
	int i;

	for(i = 0; i < tag; i++){
		tag_bitsA[i] = f_bin[i];
	}
	tag_bitsA[tag] = '\0';
	return (char *) tag_bitsA;
}

/* Gets necessary tag bits, starting off where the index bits ended, from
 * * the zero extended binary. Main difference from cacheA is that cacheB
 *  * uses tag bits from the middle and NOT the beginning.
 *   */
char *getTagB(char *f_bin, int tag, int set_index){
	char *tag_bitsB = (char *) malloc(sizeof(char) * (tag + 1));
	int i;
	int index = set_index;
	for(i = 0; i < tag; i++){
		tag_bitsB[i] = f_bin[index];
		index++;
	}
	tag_bitsB[tag] = '\0';
	return (char *) tag_bitsB;
}

/* Gets necessary index bits, starting off where the tag bits ended, from
 * * the zero extended binary. If there are no index bits needed, returns
 *  * NULL.
 *   */
char *getIndexA(char *f_bin, int tag, int set_index){
	if(set_index == 0){
		return "NULL";
	}
	char *set_bitsA = (char *) malloc(sizeof(char) * (set_index + 1));
	int i;
	int index = tag;
	for(i = 0; i < set_index; i++){
		set_bitsA[i] = f_bin[index];
		index++;
	}
	set_bitsA[set_index] = '\0';
	return (char *) set_bitsA;
}

/* Gets necessary tag bits from beginning of zero extended binary. This is the
 * * MAIN difference between cacheA and cacheB. If there are no index bits needed,
 *  * returns NULL.
 *   */
char *getIndexB(char *f_bin, int set_index){
	if(set_index == 0){
		return "NULL";
	}
	char *set_bitsB = (char *) malloc(sizeof(char) * (set_index + 1));
	int i;
	for(i = 0; i < set_index; i++){
		set_bitsB[i] = f_bin[i];
	}
	set_bitsB[set_index] = '\0';
	return (char *) set_bitsB;
}

/* Takes the index bits and converts it decimal form in order to determine which set
 * * it will be indexed to. If there are no index bits, returns 0 because there is only
 *  * one set. 
 *   */
int convertBin(char *index_bits, int set_index){
	if(set_index == 0){
		return 0;
	}
	int sum = 0;
	int base = 1;
	int val = 0, i;
	for(i = set_index - 1; i >= 0; i--){
		if(index_bits[i] == '0'){
			val = 0;
		}else{
			val = 1;
		}
		sum = sum + val * base;
		base = base * 2;
	}
	return sum;
}

/* Updates cache and increments appropriate global variable, depending if it hits or misses. Replacement strategy is 
 * * FIFO, therefore rank maintains the order the tag bits were inserted into the cache. When rank is equal to the
 *  * associativity, the tag_bits at that location are replaced with the tag bits being inserted.  
 *   */
void updateCache(int assoc, struct cache **temp, char *tag_bits, char *index_bits, int dec, char oper, int check){
	int i, j, found = 0;
	struct cache **ptr = temp;
	for(i = 0; i < assoc; i++){
		if((ptr[dec][i].valid == 1) && (strcmp(ptr[dec][i].tag, tag_bits) == 0)){
			found = 1;
			if(oper == 'W'){
				if(check == 0){
					hitA++;
					writeA++;
				}else{
					hitB++;
					writeB++;
				}
			}else if(oper == 'R'){
				if(check == 0){
					hitA++;
				}else{
					hitB++;
				}
			}
			break;
		}
	}
	if(found == 0){
		for(i = 0; i < assoc; i++){
			if(ptr[dec][i].rank == assoc){
				strcpy(ptr[dec][i].tag, tag_bits);
                                ptr[dec][i].rank = 1;
				for(j = 0; j < i; j++){
                                        ptr[dec][j].rank++;
                        	}
				for(j = i + 1; j < assoc; j++){
					ptr[dec][j].rank++;
				}
				break;
			}else if(ptr[dec][i].valid == 0){
				ptr[dec][i].valid = 1;
                                ptr[dec][i].rank = 1;
                                strcpy(ptr[dec][i].tag, tag_bits);
                                for(j = 0; j < i; j++){
                                        ptr[dec][j].rank++;
                                }
                                break;
			}
		}
		if(oper == 'W'){
			if(check == 0){
				missA++;
				readA++;
				writeA++;
			}else{
				missB++;
				readB++;
				writeB++;
			}
		}else if (oper == 'R'){
			if(check == 0){
				missA++;
				readA++;
			}else{
				missB++;
				readB++;
			}
		}
	}
	return;
}

/* Prints out global variables.
 * */
void print(){
	printf("cache A\n");
	printf("Memory reads: %d\n", readA);
	printf("Memory writes: %d\n", writeA);
	printf("Cache hits: %d\n", hitA);
	printf("Cache misses: %d\n", missA);

	printf("cache B\n");
        printf("Memory reads: %d\n", readB);
        printf("Memory writes: %d\n", writeB);
        printf("Cache hits: %d\n", hitB);
        printf("Cache misses: %d\n", missB);
	return;
}

/* Deallocates cache at each lines and then at each set.
 * */
void dealloc(struct cache **temp, int num_sets, int assoc){
	int i, j;
	struct cache **ptr = temp;
	for(i = 0; i < num_sets; i++){
		for(j = 0; j < assoc; j++){
			free(ptr[i][j].tag);
			ptr[i][j].rank = 0;
			ptr[i][j].valid = 0;
		}
		free(ptr[i]);
	}
	return;
}