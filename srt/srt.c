#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
	int Process_num;
	int Arrive_time;
	int CPU_time;
	int Stop_time;
	int Waiting_time;
	int flag;
}Process;

void Process_Sort(Process *Pro, int n) {
	Process temp;
	int i, j;
	for(i = n-1; i > 0; i--) {
		for(j = 0; j < i; j++) {
			if(Pro[j].Arrive_time > Pro[j+1].Arrive_time) {
				temp = Pro[j+1];
				Pro[j+1] = Pro[j];
				Pro[j] = temp;
				}
			else if(Pro[j].Arrive_time == Pro[j+1].Arrive_time && Pro[j].Process_num > Pro[j+1].Process_num) {
				temp = Pro[j+1];
				Pro[j+1] = Pro[j];
				Pro[j] = temp;
			}
		}
	}
}

Process *Select_Pro(Process *Pro, int n, int time, Process *start) {

	int i;
	Process *temp; //초기값 설정
	if(start == NULL) //실행프로세스가 없다면...
		temp = &Pro[0];

	else
		temp = start;

	for(i = 0; i < n ; i++) {
		if(Pro[i].Arrive_time <= time && Pro[i].CPU_time !=0) { //현재 시간보다 도착시간이 작거나 같고, CPU사용량이 0이 아닌 것 중
			if(temp->CPU_time == 0  || temp->CPU_time > Pro[i].CPU_time) //CPU시간이 작은것
				temp = &Pro[i];
		}
	}

	if(temp->Arrive_time > time) //선택이 된 상태에서 time과 선택된것의 Arrive타임확인
		temp = NULL;
	printf("%d ", temp->Process_num);
	return temp;
}

int Pro_Check(Process *Pro, int n) {
	int i;
	int result;
	for(i = 0; i < n ; i++) {
		if(Pro[i].CPU_time !=0)
		return 1;
		}
	return 0;
}

int Waiting_sum(Process *Pro, int n) {
	int i, Waiting = 0;
	for(i = 0; i < n ; i++) {
		Waiting += Pro[i].Waiting_time;
		}
	return Waiting;
}

int main() {
	int n, i, time = 0;
	int result;

	Process *Ready_Queue;
	Process *Start = NULL;
	Process *temp = NULL;

	FILE *file = fopen("process_list.txt","rt");

	FILE *outfile = fopen("srtf.out", "wt");

	fscanf(file, "%d\n", &n); //첫 줄 먹기

	Ready_Queue = (Process*)malloc(sizeof(Process)*n); //동적할당

	for(i = 0; i<n ; i++) { 
		fscanf(file, "%d %d %d\n", &Ready_Queue[i].Process_num, &Ready_Queue[i].Arrive_time, &Ready_Queue[i].CPU_time);
		Ready_Queue[i].flag = -1;
		Ready_Queue[i].Stop_time = 0;
		Ready_Queue[i].Waiting_time = 0;

		if(feof(file)!=0)
			break;
	}
	
	Process_Sort(Ready_Queue, n);
	/*Start = Select_Pro(Ready_Queue, n, 0);
	Start->CPU_time -=3;*/

	for(;;time++) {
		Start = Select_Pro(Ready_Queue, n, time, Start);

		if(Start == temp) //바뀌지 않았을 경우
		temp = Start;
	
		else { //바뀌었을 경우
			if(temp != NULL) { //temp가 NULL이 아닐 경우
				temp->Stop_time = time; //현 시간 대입
			}		


			if(Start->flag == -1) { //처음 실행하는 프로세스라면
	Start->flag = 1;

	Start->Waiting_time = time - Start->Arrive_time;

	temp = Start;

			}

			else { //한번 이상 실행하였던 프로세스라면
				Start->Waiting_time += (time - Start->Stop_time);

				temp = Start;
	
			}
	
		}

		if(Start == NULL) //실행프로세스가 없다면 time증가
	
			continue;

		Start->CPU_time--; //있다면 감소

		if(Start->CPU_time < 0) //0에서 더 이상 감소하면 안됨요.

			Start->CPU_time = 0;

		if(Pro_Check(Ready_Queue, n) == 0)

			break;

	}

	printf("결과1 \n");

	for(int i=0; i<n; i++) { //우왕국 잘받음

		printf("PID(%d) Arr Time : %d Ser Time : %d flag : %d Wait time : %d \n", Ready_Queue[i].Process_num, Ready_Queue[i].Arrive_time, Ready_Queue[i].CPU_time, Ready_Queue[i].flag, Ready_Queue[i].Waiting_time);
	

	}

	printf("결과2 \n");

	result = Waiting_sum(Ready_Queue, n);

	printf("Total wait time : %d \n", result);

	fprintf(outfile, "%d", result);

	fclose(file);

	fclose(outfile);

	return 0;

}
