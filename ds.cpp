#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
	char title[5];
	char name[30];
	char desti[30];
	char airline[30];
	char id[5];
	Node *left;
	Node *right;
	int height;
} *root;

Node *newNode(char title[], char name[], char desti[], char airline[], char id[]){
	Node *node=(Node*)malloc(sizeof(Node*));
	strcpy(node->title, title);
	strcpy(node->name, name);
	strcpy(node->desti, desti);
	strcpy(node->airline, airline);
	strcpy(node->id, id);
	node->height=0;
	node->left=NULL;
	node->right=NULL;
	return node;
}

int max(int a, int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}

int height(struct Node *node){
	if(!node){
		return 0;
	}else{
		return node->height;
	}
}

int getBalance(Node *node){
	if(!node){
		return 0;
	}else{
		return height(node->left)-height(node->right);
	}
}

Node *rightRotate(Node *node){
	Node *x=node->left;
	Node *t2=x->right;
	x->right=node;
	node->left=t2;
	node->height=height(node);
	x->height=height(x);
	return x;
}
	
Node *leftRotate(Node *node){
	Node *x=node->right;
	Node *t2=x->left;
	x->left=node;
	node->right=t2;
	node->height=height(node);
	x->height=height(x);
	return x;
}

Node *insert(Node* node, char title[], char name[], char desti[], char airline[], char id[]){
	if(node==NULL){
		return newNode(title, name, desti, airline, id);
	}
	if(strcmp(id, node->id)<0){
		node->left=insert(node->left, title, name, desti, airline, id);
	}else if(strcmp(id, node->id)>0){
		node->right=insert(node->right, title, name, desti, airline, id);
	}else{
		return node;
	}
	
	node->height = 1+max(height(node->left), height(node->right));
	int balance= getBalance(node);
	if(balance>1 && strcmp(id, node->left->id)<0){
		return rightRotate(node);
	}
	if(balance<-1 && strcmp(id, node->right->id)>0){
		return leftRotate(node);
	}
	if(balance>1 && strcmp(id, node->left->id)>0){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if(balance<-1 && strcmp(id, node->right->id)<0){
		node->right = rightRotate(node);
		return leftRotate(node);
	}
	return node;
}

Node *suc(Node* node){
	Node* curr = node;
	while(curr->left!=NULL){
		curr= curr->left;
	}
	return curr;
}

Node* deleteNode(Node* root, char id[]){
	if(!root){
		return root;
	}
	if(strcmp(id, root->id)<0){
		root->left = deleteNode(root->left, id);
	}else if(strcmp(id, root->id)>0){
		root->right = deleteNode(root->right, id);
	}else{
		if(!root->left||!root->right){
			Node *temp=(root->left);
			root->left, root->right;
			
			if(!temp){
				temp=root;
				root=NULL;
			}else{
				*root = *temp;
			}
			free(temp);
		}else{
			Node* temp= suc(root->right);
			strcpy(root->id, temp->id);
			strcpy(root->title, temp->title);
			strcpy(root->name, temp->name);
			strcpy(root->desti, temp->desti);
			strcpy(root->airline, temp->airline);
			root->right=deleteNode(root->right, temp->id);
		}
	}
	if(root==NULL){
		return root;
	}
	root->height= 1+max(height(root->left), height(root->right));
	int balance= getBalance(root);
	if(balance>1 && getBalance(root->left)>=0){
		return rightRotate(root);
	}
	if(balance>1 && getBalance(root->left)<0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance<-1 && getBalance(root->right)<=0){
		return leftRotate(root);
	}
	if(balance<-1 && getBalance(root->right)>0){
		root->right= rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

Node *find(Node* root, char id[]){
	if(!root){
		return root;
	}
	if(strcmp(id, root->id)<0){
		root->left = deleteNode(root->left, id);
	}else if(strcmp(id, root->id)>0){
		root->right = deleteNode(root->right, id);
	}
	return root;
}

void choose1(){
	char title[5], name[30], desti[30], airline[30], id[5];
	while(true){
		printf("Passenger Title = ");
		scanf("%[^\n]",title);
		getchar();
		if(strcmp(title,"Mr.")==0||strcmp(title,"Ms.")==0||strcmp(title,"Mrs.")==0){
			break;
		}
	}
	while(true){
		printf("Passenger Name = ");
		scanf("%[^\n]",name);
		getchar();
		
		if(strlen(name)>3&&strlen(name)<=25){
			break;
		}
	}
	while(true){
		printf("Travel Destination = ");
		scanf("%[^\n]",desti);
		getchar();
		if(strcmp(desti,"Citilink")==0||strcmp(desti,"Garuda Indonesia")==0){
			break;
		}
	}
	int random1=rand()%10;
	int random2=rand()%10;
	int random3=rand()%10;
	sprintf(id,"%c%c%d%d%d", desti[0],desti[1],random1,random2,random3);
	printf("Insert %s success!\n\n", id);
	printf("Press Enter to continue...");
	getchar();
	}
	
void choose2(){
		if(!root){
			printf("There is no upcoming travel...\n");
		}else{
			char id[5];
			printf("Input Ticket ID: ");
			scanf("%s", id);
			getchar();
			if(find(root, id)){
				printf("Are you sure?\n");
				printf("Confirm %s [y / n] : ");
				char cs;
				scanf("%c",&cs);
				getchar();
				if(cs=='y'){
					printf("|%s|", id);
					root=deleteNode(root, id);
				}
			} else{
				printf("TickedID doesn't exist!");
			}
		}
	}	
	
void inOrder(Node *node){
		if(node){
			printf("|%-5s|%-25s|-25s|%-20s| %\n", node->id, node->name,node->desti, node->airline);
			inOrder(node->right);
		}
	}
	
void preOrder(Node* node){
	if(node){
		printf("|%-5s|%-25s|-25s|%-20s| %\n", node->id, node->name,node->desti, node->airline);
		preOrder(node->left);
		preOrder(node->right);
	}
}

void postOrder(Node *node){
	printf("|%-5s|%-25s|-25s|%-20s| %\n", node->id, node->name,node->desti, node->airline);
	postOrder(node->left);
	postOrder(node->right);
}

int main(){
	while(true){
		int i1;
		printf("1. Plan Travel\n");
		printf("2. Boarding\n");
		printf("3. Cancel All Travel\n");
		printf("4. View Available Travel\n");
		printf("5. Exit\n");
		printf(">>");
		scanf("%d", &i1);
		if(i1==1){
			choose1();
		}else if(i1==2){
			choose2();
		}else if(i1==3){
			printf("Cancel All Travel :");
			char c;
			scanf("%c", &c);
			getchar();
			if(c=='y'){
				if(root){
					while(root){
						root = deleteNode(root, root->id);
					}
				}
				printf("Cancel All Travel Success!");
			}
			printf("Press Enter to continue...");
			getchar();
		}else if(i1==4){
			inOrder(root);
			preOrder(root);
			postOrder(root);
		}else if(i1==5){
			break;
		}
		
	}
	
	return 0;
}
