#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct tree{
	int data;
	int visit;
	struct tree **child;
}tree;
static int height, branch, *data, search = 0, number = 0;		/*����, ����, leaves��, �j�M����*/

tree *createTree(tree *current, int level){						/*�ؾ�*/
	int i, j;
	
	if(level <= height){	
		for(i = 0; i < branch; i ++){
			current -> child[i] = (tree *)malloc(sizeof(tree));
			current -> child[i] -> child = (tree **)malloc(branch * sizeof(tree*));			
			current -> child[i] -> visit = 0;
			
			if(level % 2 == 0){	
				current -> child[i] -> data = INT_MIN;
			}else{
				current -> child[i] -> data = INT_MAX;
			}
			
			if(level == height){
				current -> child[i] -> data = data[number ++];
				for(j = 0; j < branch; j ++){
					current -> child[i] -> child[j] = NULL;
				}
			}
			
			createTree(current -> child[i], level + 1);
		}
	}
}

tree *AlphaBeta(tree *current, int level, int alpha, int beta){	/*alpha-beta�ŪK*/
	int i;
	
	if(level < height){
		if(level % 2 == 0){
			for(i = 0; i < branch; i ++){
				search ++;
				current -> child[i] -> visit = 1;
				
				AlphaBeta(current -> child[i], level + 1, alpha, beta);
				
				if(current -> data < current -> child[i] -> data){
					current -> data = current -> child[i] -> data;
					alpha = current -> data;
				}

				if(alpha >= beta){
					printf("�w���X�L������� : %d\talpha : %d\tbeta : %d\t�Ӹ`�I��%d\n",search, alpha, beta, current -> child[i] -> data);
					break;
				}
			}			
		}else{
			for(i = 0; i < branch; i ++){
				search ++;
				current -> child[i] -> visit = 1;
				
				AlphaBeta(current -> child[i], level + 1, alpha, beta);
				
				if(current -> data > current -> child[i] -> data){
					current -> data = current -> child[i] -> data;
					beta = current -> data;
				}
				
				if(alpha >= beta){
					printf("�w���X�L������� : %d\talpha : %d\tbeta : %d\t�Ӹ`�I��%d\n",search, alpha, beta, current -> child[i] -> data);
					break;
				}
			}						
		}
	}
}		

tree *preorder(tree *current, int level){						/*�e�Ǩ��X*/
	int i;	
	
	if(level <= height){
		for(i = 0; i < branch; i ++){
			if(current -> visit == 1){
				current -> visit = 0;
				printf("%d\t", current -> data);
			}			
			preorder(current -> child[i], level + 1);
		}
	}
}

int main(){
	FILE *fr;
	char c , str[10];
	int i = 0, j = 0, row = 0, size;
	
	printf("Please input data...\n");
	scanf("%s", &str);
	
	fr = fopen(str, "r");										/*Ū��*/
	if(fr == NULL){
		printf("�}�ɥ��ѡI\n");
		
		system("PAUSE");	
		return 0;
	}
	
	memset(str, '\0', sizeof(str));
	while((c = fgetc(fr)) != EOF){
		if(c == '\n'){
			j = 0;
			switch(row ++){
				case 0:
					branch = atoi(str);
					break;
				case 1:
					height = atoi(str);
					
					size = pow(branch, height);
					data = (int *)malloc(size * sizeof(int));
					break;
				case 2:
					data[i ++] = atoi(str);
					break;
			}			
		}else if(c == ','){
				j = 0;
				data[i ++] = atoi(str);
				memset(str, '\0', sizeof(str));				
		}else if(c == '-'){
				str[j ++] = c;
		}else if(isdigit(c)){
				str[j ++] = c;
		}
	}
	
	struct tree *root;
	
	root = (tree *)malloc(sizeof(tree));						/*��l�Ʈڸ`�I*/
	root -> data = INT_MIN;
	root -> visit = 1;
	root -> child = (tree **)malloc(branch * sizeof(tree));
	createTree(root, 1);										/*�ؾ�*/
	
	AlphaBeta(root, 0, INT_MIN, INT_MAX);						/*alpha-beta�ŪK*/
	
	printf("Nunber of nodes visited�G\n");
	printf("%d\n", search);
	
	printf("print all the nodes�G\n");
	preorder(root, 0);											/*�e�Ǩ��X*/
	
	system("PAUSE");	
	return 0;
}