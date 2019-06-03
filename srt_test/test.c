#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
	int i=0;

	while(1){
	//	printf("%d\n",i);
		
		if(i==0){
			printf("1 : %d\n", i);
		}
		if(i>=0){
			printf("2 : %d\n",i);
			if(i % 2 ==0){
				printf("4 : %d\n",i);
			}
		}
		if(i == 100){
			printf("3 : %d\n",i);
			break;
		}
		i++;
		sleep(1);
	}
		
	
}

