#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int size = 8;
static int *current_status, *next_status;

int Collision(int *status){												/*計算衝突數*/
	int i, j, num_collision = 0;
	
	for(i = 0; i < size; i ++){
		for(j = (i + 1); j < size; j ++){
			if(status[i] == status[j]){									/*判斷直行是否衝突*/
				num_collision ++;
			}
			
			if(abs(status[i] - status[j]) == (j - i)){					/*判斷斜行是否衝突*/
				num_collision ++;				
			}
		}
	}
	
	return num_collision;
}

int HillClimbing(){														/*爬山演算法*/
	int i, j, k, temp_status[size], now_collision, min_collision;
	
	min_collision = Collision(next_status);								/*紀錄最小衝突數*/	
	for(i = 0; i < size; i ++){
		temp_status[i] = next_status[i];
	}
	
	for(i = 0; i < size; i ++){		
		for(j = 0; j < size; j ++){
			if(current_status[i] == j){
				continue;
			}
			
			for(k = 0; k < size; k ++){
				next_status[k] = current_status[k];
			} 
			next_status[i] = j;
			now_collision = Collision(next_status);
			if(min_collision > now_collision){
				min_collision = now_collision;
				for(k = 0; k < size; k ++){
					temp_status[k] = next_status[k];
				}
			}
		}
	}
	
	for(i = 0; i < size; i ++){
		next_status[i] = temp_status[i];
	}	
}

void Queens(){															/*求解八皇后*/
	int i, j, same;
	for(i = 0; i < size; i ++){											/*初始化棋盤位置*/
		next_status[i] = rand() % size;
	}
	
	do{
		for(i = 0; i < size; i ++){
			current_status[i] = next_status[i];
		}
		HillClimbing();
		
		same = 0;
		for(i = 0; i < size; i ++){			
			if(current_status[i] == next_status[i]){
				same ++;
			}
		}
	}while(same != size);
}

int main(){
	int i, j, success = 0;
	unsigned seed;
	seed = (unsigned)time(NULL);										/*亂數取值*/
	srand(seed);	
	FILE *fw;															/*檔案輸出*/
	fw = fopen("output.txt", "w + t");
	
	current_status = (int *)malloc(sizeof(int) * size);
	next_status = (int *)malloc(sizeof(int) * size);
	
	while(success < 3){
		Queens();
		
		if(Collision(current_status) == 0){								/*若衝突數 = 0，即印出棋盤*/
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
			fprintf(fw, "\n");
		}
	}
	
	fclose(fw);
	return 0;
}