#include<stdio.h>
#include<stdlib.h>
struct node{
	int item1;
	struct node* nextNode;
};
void printAns(struct node* headNode);
int lengthOfList(struct node* headNode);
struct node* insertNode(struct node* headNode, int inputN);
struct node* deleteNode(struct node* headNode, int inputN);



struct node* deleteNode(struct node* headNode, int inputN){
	struct node* currentNode = headNode;
	struct node* previousNode = NULL;
	while(currentNode != NULL){
		if(inputN < currentNode->item1){
			return headNode;
		}
		else if(inputN == currentNode->item1)
			break;
		previousNode = currentNode;
		currentNode = currentNode->nextNode;
	}
	if(currentNode == NULL){
		return headNode;
	}
	if(previousNode == NULL){
		headNode = currentNode->nextNode;
	}
	else
		previousNode->nextNode = currentNode->nextNode;
		free(currentNode);
			return headNode;
}

struct node* insertNode(struct node* headNode, int inputN){
	struct node* currentNode = headNode;
	struct node* previousNode = NULL;
	struct node* holder1 = (struct node*) malloc(sizeof(struct node));
	holder1->item1 = inputN;
	holder1->nextNode = NULL;
	while(currentNode != NULL){
		if(inputN < currentNode->item1){
		break;
		}
		else if(inputN == currentNode->item1)
			return headNode;
			previousNode = currentNode;
			currentNode = currentNode->nextNode;
	}
	holder1->nextNode = currentNode;
	if(previousNode != NULL){
		previousNode->nextNode = holder1;
	}
	else
		headNode = holder1;
			return headNode;
}




int lenList(struct node* headNode){
	struct node* currentNode = headNode;
	int length1 = 0;
	while(currentNode != NULL){
		length1++;
		currentNode = currentNode->nextNode;
	}
	return length1;
}



/*int main(int argc, char* argv[]){
	FILE *inputf;
	inputf=fopen(argv[1],"r");
	char func;     //input command and data
	int data;
	struct node *head=NULL ;//head of the linked list
	struct node *curr=NULL;
	
	//get input command
	fscanf(stdin,"%c %d",&func, &data); //write at memory location since the variables will be passed to different functions
	while (func=='i' || func=='d') {

        printf("enters loop");
		if (func=='i') {    //insert
			head=insertNode(head,data);
		}
		else {            //delete
			head=deleteNode(head,data);
		}
		printf("%d : ", lengthOfList(head));
		curr=head;
		while (curr!=NULL) {
			printf("%d ",curr -> item1);
			curr = curr-> nextNode;
		}
		printf("\n");
        printf("error here");
		fscanf(stdin,"%c %d",&func, &data);	

        printf("got here");
        
        printf("%c %d", func, data);
        printf("\n");
	}
	return 0;
}*/




int main(int argc, char* argv[]){
	FILE *inputf;
	inputf=fopen(argv[1],"r");
	char func;     //input command and data
	int data;
	struct node *head=NULL ;//head of the linked list
	struct node *curr=NULL;
	
	//get input command
	while (fscanf(stdin,"%c %d",&func, &data)!=EOF) {
        //fscanf(stdin,"%c %d",&func, &data);
        
		if (func=='i') {    //insert
			head=insertNode(head,data);
		}
		else {            //delete
			head=deleteNode(head,data);
		}
		printf("%d : ", lenList(head));
		curr=head;
		while (curr!=NULL) {
			printf("%d ",curr -> item1);
			curr = curr-> nextNode;
		}
		//printf("\n");
       
        
        //printf("%c %d", func, data);
        //printf("\n");
		fscanf(stdin,"%c %d",&func, &data);
        
	}
	return 0;
}