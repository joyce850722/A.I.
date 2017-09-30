#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct tree{
	int data;
	int visit;
	struct tree **child;
}tree;
static int height, branch, *data, number = 0;	/*高度, 分支, leaves值*/

tree *createTree(tree *current, int level){		/*建樹*/
	int i, j;
	
	if(level <= height){	
		for(i = 0; i < branch; i ++){
			current -> child[i] = (tree *)malloc(sizeof(tree));
			current -> child[i] -> child = (tree **)malloc(branch * sizeof(tree*));
			current -> child[i] -> data = 0;
			current -> child[i] -> visit = 0;
			
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

tree *minmaxTree(tree *current, int level){		/*minmax填值*/
	int i;
	
	if(level < height){
		if(level % 2 == 0){
			for(i = 0; i < branch; i ++){
				minmaxTree(current -> child[i], level + 1);
				
				if(current -> data < current -> child[i] -> data){
					current -> data = current -> child[i] -> data;
				}
			}
		}else{
			for(i = 0; i < branch; i ++){
				minmaxTree(current -> child[i], level + 1);
				
				if(current -> data > current -> child[i] -> data){
					current -> data = current -> child[i] -> data;
				}
			}
		}
	}
}

tree *preorder(tree *current, int level){		/*前序走訪*/
	int i;
	
	if(level <= height){
		for(i = 0; i < branch; i ++){
			if(current -> visit == 0){
				current -> visit = 1;
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
	
	fr = fopen(str, "r");						/*讀檔*/
	if(fr == NULL){
		printf("開檔失敗！\n");
		
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
	
	root = (tree *)malloc(sizeof(tree));		
	root -> data = 0;
	root -> visit = 0;
	root -> child = (tree **)malloc(branch * sizeof(tree));
	createTree(root, 1);						
	
	minmaxTree(root, 0);						
	
	printf("print all the nodes：\n");
	preorder(root, 0);
	
	system("PAUSE");	
	return 0;
}