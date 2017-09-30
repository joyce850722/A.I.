#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

static int size = 8, individuals = 8, pm = 8, genernation = 0;		/*八皇后, 每代個體數量, 突變機率, 代*/
static int *current_status, *father, *mother;							/*當前棋盤, 親代*/

int Adaptability(int *status){											/*計算適應度*/
	int i, j, adaptability = 0;
	
	for(i = 0; i < size; i ++){
		for(j = (i + 1); j < size; j ++){
			if(status[i] != status[j]){
				adaptability ++;
			}
			
			if(abs(status[i] - status[j]) != (j - i)){
				adaptability ++;
			}
		}
	}
	
	return adaptability;
}

void Mutation(int *status){												/*突變*/
	int position = rand() % size;
	int location = rand() % size;
	
	status[position] = location;
}

void Crossover(){														/*雜交*/
	int i;
	
	for(i = 0; i < size; i ++){
		if(father[i] != mother[i]){
			if(father[i] != current_status[i]){
				current_status[i] = father[i];
			}else{
				current_status[i] = mother[i];
			}
		}
	}
}

void Parental(){														/*親代*/
	int i, j, adaptable = 0, random, stop;
	int individual[individuals][size], adaptation[individuals];			/*個體, 適應度比例*/
	
	for(i = 0; i < size; i ++){											/*初始化個體*/
		for(j = 0; j < size; j ++){
			individual[i][j] = current_status[j];
		}
		
		Mutation(individual[i]);
	}
	
	for(i = 0; i < individuals; i ++){									/*依適應度比例選擇親代*/
		adaptable += Adaptability(individual[i]);
		adaptation[i] = adaptable;
	}
	
	random = rand() % adaptable;
	for(i = 0; i < individuals; i ++){
		if(random < adaptation[i]){
			for(j = 0; j < size; j ++){
				father[j] = individual[i][j];
			}
			stop = i;
			break;
		}
	}
	
	do{
		random = rand() % adaptable;
		
		for(i = 0; i < individuals; i ++){	
			if(random < adaptation[i]){
				for(j = 0; j < size; j ++){
					mother[j] = individual[i][j];
				}
				break;
			}
		}
	}while(i == stop);
}

void Queens(){															/*求解八皇后*/
	int i;
	
	for(i = 0; i < size; i ++){											/*初始化棋盤*/
		current_status[i] = rand() % size;
	}
	
	do{		
		Parental();
		
		Crossover();
		
		if(rand() % pm == 0){
			Mutation(current_status);
		}
		
		genernation ++;
	}while(Adaptability(current_status) != (size * (size - 1)));
}

int main(){	
	int i, j, success = 0;
	unsigned seed;														/*亂數種子*/
	seed = (unsigned)time(NULL);
	srand(seed);
	FILE *fw;															/*檔案輸出*/
	fw = fopen("output.txt", "w + t");
	
	current_status = (int *)malloc(sizeof(int) * size);
	father = (int *)malloc(sizeof(int) * size);
	mother = (int *)malloc(sizeof(int) * size);
	
	while(success < 3){
		Queens();
		
		success ++;
			
		for(i = 0; i < size; i ++){
			for(j = 0; j < size; j ++){
				if(current_status[i] == j){					
					fprintf(fw, "1");
					continue;
				}				
				fprintf(fw, "0");
			}			
			fprintf(fw, "\n");
		}		
		fprintf(fw, "在%d代找到解\n", genernation);
	}
	
	fclose(fw);
	return 0;
}