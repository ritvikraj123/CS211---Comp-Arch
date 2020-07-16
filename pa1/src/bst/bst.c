#include<stdio.h>
#include<stdlib.h>
//-----------------------------------------------------------------------------
typedef struct node {
  int data;
  int height;
  struct node* right;
  struct node* left;
}node;
//-----------------------------------------------------------------------------
node * insert (node* head, int num);
node * delete (node* head, int num); 
int checkDup (node* head, int num);
int bringMeHeight (node* head, int num);
int search (node* head, int num);
int bringMeSmallest (node* head);
//void print(node*head);
void fixHeight(node * p);
void freeMe (node * p);
//-----------------------------------------------------------------------------
int main ( int argc , char** argv ) {
 
  FILE* fefe;
  fefe = fopen(argv[1], "r");

  char op;
  int num,tempHeight,s,dupCheck;

  if ( fefe == NULL ) {
    printf("error\n");
    return 0;
  }
  
  node * head = NULL;

  //gushead = delete(head,5);

  
  
  while ( fscanf(fefe, "%c\t%d\n", &op, &num) != EOF ) {
    if ( op == 'i' ) { //inserting into the binary tree
      dupCheck = checkDup(head,num); //will return 1. if it IS FOUND
      if ( dupCheck == 1 ) { 
        printf("duplicate\n");
      } else {
        head = insert(head,num);
	tempHeight = bringMeHeight(head,num);
	printf("inserted ");
        printf("%d\n", tempHeight);
      }
    } else if ( op == 's' ) { //search the binary tree
	s = search(head,num);
	if ( s == 0 ) { //0 means not found
	  printf("absent\n");
	} else {
	  printf("present ");
	  head->height = 1;
          fixHeight(head);
	  tempHeight = bringMeHeight(head,num);
	  printf("%d\n", tempHeight);
        }
    } else { //must be a delete
	/* delete code */
	s = search(head,num);
	if ( s == 0 ) { // 0 means it wasn't found, so print fail
          printf("fail\n");
        } else { // must be there, so lets delete it.
          printf("success\n");
          head = delete(head,num);
        }
    }
  }
  freeMe(head);
 // print(head);

  return 0;
}
//-----------------------------------------------------------------------------
node* insert ( node* head, int num ) {
  node * po = (node*) malloc(sizeof(node));
  po->data = num;
  po->height = -1;
  po->left = NULL;
  po->right = NULL;
  if ( head == NULL ) {
    head = po;
    head->height = 1;
    return head;
  }
  node* p = head;
  int temp;

  while ( p != NULL ) {
    temp = p->data;
    if ( num < temp ) {
      if ( p->left == NULL ) {
        p->left = po;
        po->height = p->height + 1;
        return head;
      }
      p = p->left;
    } else {
      if ( p->right == NULL ) {
        p->right = po;
        po->height = p->height + 1;
        return head;
      }
      p = p->right;
    }
 }
 return head;
}
//-----------------------------------------------------------------------------
int checkDup(node* head, int num) {
  node* p = head;
  int temp;
  while ( p != NULL ) {
    temp = p->data;
    if ( temp == num ) { //it was found!
      return 1;
    }
    if ( num < temp ) {
      p = p->left;
    } else {
      p = p->right;
    }
 }
 return 0;
}
//-----------------------------------------------------------------------------
int bringMeHeight(node* head, int num) {
  node* p = head;
  int temp;
  while ( p != NULL) {
    temp = p->data;
    if ( temp == num ) { //dup is found!!
      return p->height;
    }
    if ( num < temp ) {
      p = p->left;
    } else {
      p = p->right;
    }
 }
 return -1;
}
//-----------------------------------------------------------------------------
int search ( node* head, int num ) { // 0 = Not found 1 = Found
  node* p = head;
  int temp;
  while ( p != NULL ) {
    temp = p->data;
    if ( temp == num ) {
      return 1;
    }
    if ( num < temp ) {
      p = p->left;
    } else {
      p = p->right;
    }
 }
 return 0;
}
//-----------------------------------------------------------------------------
node * delete (node* p, int num) {
  //node* prev = NULL;
  int temp,s;
  //while ( p != NULL ) {
    temp = p->data;
    if ( temp == num ) { //we have to delete this!
      if ( p->left == NULL && p->right == NULL ) {
        p = NULL;
      } else if ( p->right == NULL ) {
        p = p->left;
      } else if ( p->left == NULL ) {
        p = p->right;
      } else {
        s = bringMeSmallest(p->right);
        p->data = s;
        p->right = delete(p->right, s);
      }
      //printf("I FIRED\n");
      /* SCRAP CODE DOESNT WORK
      printf("Found! : %d\n",num);
      if ( p->right == NULL ) { //easy delete, just return p->left; 1) Handles single node and handles nodes with ONLY left children
        if ( temp == head->data ) {
          //printf("OOPS I fired\n");
	  printf("Just deleted %d\n",head->data);
          return p->left;
        }
        if ( prev->left->data == num ) {
          printf("Just deleted %d\n" , num);
          prev->left = p->left;
	  printf("I exececuted\n");
        }
        if ( prev->right->data == num ) {
          printf("Just deleted %d\n", num);
	  prev->right = p->left;
        }
     */
    }
    if ( num < temp ) {
      //prev = p;
      p->left = delete(p->left , num );
      //printf("Going left, Current node : %d\n",prev->data);
    }
    if ( num > temp ) {
      //prev = p;
      p->right = delete(p->right, num);;
      //printf("Going right, Current node: %d\n",prev->data);
    }
 // }
  //printf("I fired\n");
  return p;
}
//-----------------------------------------------------------------------------
int bringMeSmallest (node* head) {
  int smallest = head->data;
  node* p = head;
  while ( p != NULL) {
    smallest = p->data;
    p = p->left;
  }
  return smallest;
}
//-----------------------------------------------------------------------------
/*node * adjustHeight (node* head) {
    
  head->left->height = head->height + 1;
  head->right->height = head->height + 1;
  
  
}
*/
//-----------------------------------------------------------------------------
void fixHeight(node * p) {
  if ( p == NULL ) {
    return;
  }
  if ( p->left != NULL ) {
     p->left->height = p->height + 1;
  }
  
  if ( p->right != NULL ) {
    p->right->height = p->height + 1;
  }
  fixHeight(p->left);
  fixHeight(p->right);
}
//-----------------------------------------------------------------------------
/*
void print (node* head) {
  if ( head == NULL ) {
    return;
  }
  printf("%d\n", head->data);
  print(head->left);
  print(head->right);
}
*/
//-----------------------------------------------------------------------------
void freeMe (node* p) {
  if ( p == NULL ) {
    return;
  }

  freeMe(p->left);
  freeMe(p->right);
  free(p);
}
//-----------------------------------------------------------------------------