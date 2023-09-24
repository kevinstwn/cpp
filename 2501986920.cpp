#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  char drinks[100];
  int A;
} root[1000];

int size = 0;

void heap(int i){
    if ((i > size/2 && i<=size)==NULL){
        Node left = root[i * 2];
        Node right = root[i * 2 + 1];
        if (root[i].A < left.A || root[i].A < right.A){
            Node temp = root[i];
            if (left.A > right.A) {
                root[i] = root[i*2];
                root[i*2] = temp;
                heap(i*2);
            }else{
                root[i] = root[i * 2 + 1];
                root[i * 2 + 1] = temp;
                heap(i * 2 + 1);
            }
        }
    }
}

void insert(Node node){
    size++;
    root[size] = node;
    
    int i = size;
    while (root[i].A>root[i/2].A && i/2>0) {
        Node temp = root[i];
        root[i] = root[i/2];
        root[i/2] = temp;
        i /= 2;
    }
}

Node del(){
    Node temp = root[1];
    root[1] = root[size];
    size--;
    heap(1);
    return temp;
}

void getName(char code[100],char** result){
    if (strcmp(code, "BC") == 0) {
        strcpy(*result, "Boba Coffee");
    }else if (strcmp(code, "MC") == 0){
        strcpy(*result, "Moccapucino");
    }else if (strcmp(code, "PC") == 0){
        strcpy(*result, "Pandan Coffee");
    }else if (strcmp(code, "BT") == 0){
        strcpy(*result, "Boba Thai");
    }else if (strcmp(code, "CP") == 0){
        strcpy(*result, "Choco Pandan");
    }else if (strcmp(code, "CC") == 0){
        strcpy(*result, "Cheese Choco");
    }
}

void print(){
    char drink1[100], drink2[100];
    
    Node temp1 = del();
    Node temp2 = del();
    char*minum1 = drink1;
    char*minum2 = drink2;
    getName(temp1.drinks,&minum1);
    getName(temp2.drinks,&minum2); 
    printf("Top Sales:\n");
    printf("1. %s %d\n",drink1,temp1.A);
    printf("2. %s %d\n",drink2,temp2.A);
}

int main(){
    int x, y, z;
    scanf("%d", &x);
    getchar();
    Node nodes[x];
    
    for(int i=0; i<x; i++){
    	z=0;
        Node node;
        scanf("%d %s",&node.A,node.drinks);
        getchar();
        for(int j=0; j<=y; j++){
            if(j!=y && strcmp(nodes[j].drinks,node.drinks)==0){
                nodes[j].A+=node.A;
                z=1;
                break;
            }
        }
        if (z==1) {
            continue;
        }
        nodes[y]=node;
        y++;
    }
    
    for(int k=0; k<y; k++){
        insert(nodes[k]);
    }
    
    print();
    return 0;
}
