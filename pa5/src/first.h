#ifndef _first_h
#define _first_h

/* Cache data structure.
 * */
struct cache{
	int valid;
	int rank; /* Used for FIFO replacement */
	char *tag;
};

void readFile(FILE *trace_file, int num_sets, int tag, int set_index, int block_offset, int assoc);
struct cache **createCache(int num_sets, int assoc,  int tag);
char *convertHex(char slot);
char *fixBinary(char *binary);
char *getTagA(char* f_bin, int tag);
char *getTagB(char* f_bin, int tag, int set_index);
char *getIndexA(char* f_bin, int tag, int set_index);
char *getIndexB(char* f_bin, int set_index);
int convertBin(char* index_bits, int set_index);
void updateCache(int assoc, struct cache **temp, char* tag_bits, char* index_bits, int dec, char oper, int check);
void print();
void dealloc(struct cache **temp, int num_sets, int assoc);

#endif