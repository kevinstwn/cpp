#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10 

struct Node{
	char name[50];
	int room;
	Node* next; 
};
Node* table[SIZE];

Node* createNode(char name[],int room){
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->room = room;
	newNode->next = NULL;
	return newNode;
}

int hash(char name[]){
	int hashkey = 0;
	for(int i=0; i<strlen(name); i++){
		hashkey = hashkey + name[i];
	}
	return hashkey%SIZE;
}


void inserts(char name[], int room){
	
	Node* toInsert = createNode(name, room);
	int idx = hash(name);
	if(table[idx]==NULL) table[idx] = toInsert;
	else{
		Node* curr = table[idx];
		while(curr->next!=NULL){
			curr = curr->next;
		}
		curr->next = toInsert;
	}
}

void deletes(char name[]){

	int idx = hash(name);
	Node* curr = table[idx];
	Node* prev = NULL;
	while(curr!=NULL && strcmp(curr->name, name)!=0){
		prev = curr;
		curr = curr->next;
	}
	if(table[idx]!=NULL && strcmp(table[idx]->name, name)==0){
		table[idx] = table[idx]->next;
		free(curr);
		curr = NULL;
	}
	else if(curr!=NULL && strcmp(curr->name, name)==0){
		prev->next = curr->next;
		free(curr);
		curr = NULL;
	}
}

void view(){
	for (int i=1; i<=SIZE; i++){
		if(table[i]==NULL) printf("%d. - ", i);
		else{
			printf("%d. ", i);
			Node* curr = table[i];
			while(curr!=NULL){
				printf("[%s Kamar no.%d]", curr->name, curr->room);
				if(curr->next!=NULL) printf("-> ");
				curr = curr->next;
			}
		}
		puts("");
	}
	puts("");	
}

int main(){
	awal:
	system ("cls");
	int ts;
	printf("========== INFO KAMAR HOTEL ==========\n");
	printf("1. Masukkan data tamu\n");
	printf("2. Hapus data tamu\n");
	printf("3. Tampilkan data tamu\n");
	printf("4. Exit\n");
	printf("Pilih nomor yang tertera: ");
	scanf("%d",&ts);
	
	switch(ts)
	{
		case(1):
			int room;
			char name[50];
			printf("\n");
			printf("Masukkan nama tamu:\n");
			getchar();
			scanf("%[^\n]", &name);
			printf("Masukkan nomor kamar:\n");
			scanf("%d",&room);
			
			
			inserts(name, room);
			getchar();
			goto awal;
			
		case(2):
			char tamu[50];
			printf ("Masukkan nama yang reservasinya ingin dihapus\n");
			getchar();
			scanf("%[^\n]",tamu);
			
			deletes(tamu);
			printf("\n Tekan enter untuk lanjutkan");getchar();
			getchar();
			goto awal;
			
		case (3):
			view();
			printf("\n Tekan enter untuk lanjutkan");getchar();
			getchar();
			goto awal;
		
		case(4):
			system ("cls");
			break;
	}
	printf ("Terima Kasih!");
	return 0;
	return 0;
}