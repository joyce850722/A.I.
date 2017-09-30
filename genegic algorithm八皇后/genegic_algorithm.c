#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

static int size = 8, individuals = 8, pm = 8, genernation = 0;		/*�K�ӦZ, �C�N����ƶq, ���ܾ��v, �N*/
static int *current_status, *father, *mother;							/*��e�ѽL, �˥N*/

int Adaptability(int *status){											/*�p��A����*/
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

void Mutation(int *status){												/*����*/
	int position = rand() % size;
	int location = rand() % size;
	
	status[position] = location;
}

void Crossover(){														/*����*/
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

void Parental(){														/*�˥N*/
	int i, j, adaptable = 0, random, stop;
	int individual[individuals][size], adaptation[individuals];			/*����, �A���פ��*/
	
	for(i = 0; i < size; i ++){											/*��l�ƭ���*/
		for(j = 0; j < size; j ++){
			individual[i][j] = current_status[j];
		}
		
		Mutation(individual[i]);
	}
	
	for(i = 0; i < individuals; i ++){									/*�̾A���פ�ҿ�ܿ˥N*/
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

void Queens(){															/*�D�ѤK�ӦZ*/
	int i;
	
	for(i = 0; i < size; i ++){											/*��l�ƴѽL*/
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
	unsigned seed;														/*�üƺؤl*/
	seed = (unsigned)time(NULL);
	srand(seed);
	FILE *fw;															/*�ɮ׿�X*/
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
		fprintf(fw, "�b%d�N����\n", genernation);
	}
	
	fclose(fw);
	return 0;
}