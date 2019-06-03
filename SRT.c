#include <stdio.h>
#include <stdlib.h>


//순서대로 프로세스번호, 동작시간, 도착시간, 우선순위, 대기시간, 전체 동작시간, 남은 동작시간 
typedef struct _process{
    int pro_num, cpu_time, arr_t, pri, wait_t, ta_t, rem_t;
    } process;


    int process_srt(process *pro, int n);
    /*
    남은 동작시간을 매시간 계산하여 가장짧은 남은 동작시간을 가진 프로세스를 우선 처리하는 알고리즘
    now변수를 이용해 매시간 카운트하여 남은 계산시간을 계산
    선점형으로 동작(처음 min값이 5000인것은 제일 처음 동작하는 프로세스가 
    제일 적은 남은 동작시간을 가져야하기때문
    */ 

    int process_generate(process *pro, int n); //새로운 랜덤프로세스를 생성 
    void at_sort(process *pro, int n); //도착한시간 순으로 프로세스를 정렬 
    void resort(process *pro, int n); //도착시간순으로 정렬된 프로세스를 다시 원래대로 프로세스번호순으로 재정렬 


void at_sort(process *pro, int n){
	process temp;
	int i,j;
	for(i=n-1; i>0;i--){
		for(j=0;j<i;j++){
			if(pro[j].arr_t>pro[j+1].arr_t){
				temp=pro[j+1];
				pro[j+1]=pro[j];
				pro[j]=temp;
				}
			else if(pro[j].arr_t==pro[j+1].arr_t&&pro[j].pro_num>pro[j+1].pro_num){
				temp=pro[j+1];
				pro[j+1]=pro[j];
				pro[j]=temp;
				}
			}
		}
	}
void resort(process *pro, int n){
	process temp;
	int i,j;
	for(i=n-1; i>0;i--){
		for(j=0;j<i;j++){
			if(pro[j].pro_num>pro[j+1].pro_num){
				temp=pro[j+1];
				pro[j+1]=pro[j];
				pro[j]=temp;
				}
			}
																	}
	}

int process_srt(process *pro, int n){
	int remain, min, now_p, i, temp[150];
	int now, wt=0;
	
	remain=n;
	now=pro[0].arr_t;

	while(remain>0){
		min=5000;	
		for(i=0; pro[i].arr_t<=now && i<n; i++){	
			if(pro[i].rem_t<min && pro[i].rem_t>0){	
				now_p=i;
				min=pro[i].rem_t; //가장 적은 남은 동작시간을 선언 
				}
			}
		now++;
	
		if(temp[0] !=pro[0].cpu_time){
			for(i=0; i<n; i++){
				temp[i]=pro[i].rem_t;
			}
		}
	
		pro[now_p].rem_t--;	// 시간이 지날수록 남은 동작시간 카운트를 감소 

		if(pro[now_p].rem_t==0){	//남은 동작시간이 0인경우 연산 
			pro[now_p].wait_t=now-pro[now_p].arr_t-pro[now_p].cpu_time;
			pro[now_p].ta_t=pro[now_p].cpu_time + pro[now_p].wait_t;
			wt=wt+pro[now_p].wait_t;
			remain--;
		}
	}
	for(i=0; i<n; i++){
		pro[i].rem_t=temp[i];
	}
}

int process_generate(process *pro, int n){
	FILE *fp2;
	int j, found;

	fp2=fopen("proc.txt","a+");

	int i=n;

	int bt =(rand()%25)+1;


	pro[i].pro_num=i+1;

	pro[i].cpu_time=bt;



	while(1){

		pro[i].pri=rand()%50;

		found=0;

		for(j=0;j<i;++j){

			if(pro[j].pri==pro[i].pri){

				found=1;

				break;
			}

		}

		if(!found) break;

	}



	while(1){

		pro[i].arr_t=rand()%50;

		found=0;

		for(j=0;j<i;++j){

			if(pro[j].arr_t==pro[i].arr_t){

				found=1;

				break;
			}

		}

		if(!found) break;

	}

	fprintf(fp2,"\r\n%d %d %d %d",pro[i].pro_num, pro[i].cpu_time, pro[i].arr_t, pro[i].pri);

	fclose(fp2);

}

int main(){

	int  i,n, Q;

	int index=0;

	float tat;



	process *ready_queue;



	FILE *fp;

	fp=fopen("proc.txt","r");



	while(!feof(fp)) { 

		fscanf(fp, "%d", &ready_queue[i].pro_num);

		fscanf(fp, "%d", &ready_queue[i].cpu_time);

		fscanf(fp, "%d", &ready_queue[i].arr_t);

		fscanf(fp, "%d", &ready_queue[i].pri);

		ready_queue[i].rem_t=ready_queue[i].cpu_time;

		index=index+1;

		i++;

		if(feof(fp)!=0)

			break;

	}



	fclose(fp);

	n=index;

	system("clear");


	at_sort(ready_queue, n);

	process_srt(ready_queue, n);

	resort(ready_queue, n);



	printf("5. Shortest Remaining time First (SRTF)\n====================SRTF======================\n");

	printf("P#	BT	AT	Pri	WT	TAT\n");

	for(i=0; i<n; i++) {

		tat=tat+ready_queue[i].ta_t;

		printf("%d	%d	%d	%d	%d	%d\n",ready_queue[i].pro_num, ready_queue[i].cpu_time, ready_queue[i].arr_t, ready_queue[i].pri, ready_queue[i].wait_t, ready_queue[i].ta_t);

	}

	printf("average turnaround time: %.2f\n",tat/n);

	printf("==============================================\n");



}
