#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct process{
	int num_pro, arr_time, ser_time, pro_pid;
	//프로세스 번호,  도착시간, 서비스시간, 프로세스 아이디
	int total_time;
	int rem_time; 
	int turn_time;//프로세스 실행이 종료되는시간 - arr_time
	int wait_time;//큐에 머무는 시간의 합 or not running 시간의 합
	int resp_time;//cpu를 맨처음 점유한시간 - arr_time or 처음 running state가 된시간 - arr_time
}process;

/*
void pro_State(process *pro, int num_pro){ //프로세스 상태표시
//	char state_0[] = "Not-Running";
//	char state_1[] = "Running";
//	char state_2[] = "Exit";
	int i = 0;
	int time = 0;


	for(i=0;;){
		if(pro[0].arr_time == 0){
			printf("[%d] PID(%d) : Not Running\n",pro[i].arr_time, pro[i].pro_pid);
			time++;
			i++;
			
		}		
		if(time <= pro[i].arr_time){
			printf("[%d] PID(%d) : Running\n",pro[i].arr_time, pro[i].pro_pid);
			time++;
			i++;
			if(pro[i].arr_time <= pro[i-1].ser_time){
				printf("[%d] PID(%d) : Not Running\n",pro[i].arr_time, pro[i].pro_pid);
				}

		}
		else if(time > pro[i].arr_time){
			printf("[%d] PID(%d) : Exit\n",pro[i].arr_time, pro[i].pro_pid);
			time++;
			i++;
		}
			
		
	}
}
*/

void pro_sort(process *pro, int num_pro){ //프로세스를 오름차순으로 정렬
	process temp;
	int i, j;
	for(i = num_pro - 1; i>0; i--){
		for(j=0; j<i; j++){
			if(pro[j].arr_time > pro[j+1].arr_time){//프로세스 도착시간이 더 빠를때 오름차순으로 정렬
				printf("Arrival Time을 오름차순으로 변경합니다.\n\n");

				temp = pro[j+1];
				pro[j+1] = pro[j];
				pro[j] = temp;
			}
			else if(pro[j].arr_time == pro[j+1].arr_time && pro[j].pro_pid > pro[j+1].pro_pid){
				//프로세스 도착시간이 같을때, PID값을 오름차순으로 정렬
				printf("PID 값을 오름차순으로 변경합니다.\n\n");

				temp = pro[j+1];
				pro[j+1] = pro[j];
				pro[j] = temp;
			}
		}
	}
}

void pro_average(process *pro, int num_pro){
	int i, j;
	for(i = 0; i<num_pro; i++){
		pro[i+1].turn_time += pro[i].turn_time;
		pro[i+1].wait_time += pro[i].wait_time;
		pro[i+1].resp_time += pro[i].resp_time;
		}
	
//	printf("%d %d %d\n",pro[i].turn_time, pro[i].wait_time, pro[i].resp_time);
	float average_turn_time = pro[i].turn_time/num_pro;
	float average_wait_time = pro[i].wait_time/num_pro;
	float average_resp_time = pro[i].resp_time/num_pro;

	printf("\n\nAverage Turnaround Time : %0.2f\nAverage Waiting Time : %0.2f\nAverage Response Time : %0.2f\n", average_turn_time, average_wait_time, average_resp_time);

}

void pro_run(process *pro, int num_pro){
	int i;
	

	for(i=0; i< num_pro; i++){
		pro[i].total_time = pro[i].wait_time + pro[i].ser_time; //전체 동작시간
//		printf("PID (%d) -> Total Time : %d\n",pro[i].pro_pid ,pro[i].total_time);
	}

//	pro_SRT(pro, num_pro);

	printf("\nLog of Process Scheduling\n");

	pro[0].wait_time = 0;//처음들어온 프로세스의 대기시간은 0이다.
	for(i=1; i < num_pro; i++){
		if(pro[i-1].ser_time + pro[i-1].arr_time < pro[i].arr_time)
			pro[i].wait_time = 0;
		else	
			pro[i].wait_time = pro[i-1].arr_time + pro[i-1].ser_time - pro[i].arr_time + pro[i-1].wait_time;
	}

	for(i=0; i<num_pro; i++){
		pro[i].turn_time = pro[i].wait_time + pro[i].ser_time;
		}
	pro[0].resp_time = pro[0].wait_time;
	for(i=0; i<num_pro; i++){
		pro[i+1].resp_time = pro[i+1].wait_time;
	}


}


void pro_SRT(process *pro, int num_pro){//SRT 수행 코드
	int i = 0;
	int time = 0;
	pro_run(pro,num_pro);
	while(1){

		if(time == 0 && pro[i].arr_time == 0){
			printf("[%d] PID(%d) : Not-Running\n", time, pro[i].pro_pid);
		}
			
		if(time <= pro[i].arr_time){
			for(;time >= pro[i].arr_time+pro[i].ser_time;time++){
				printf("[%d] PID(%d) : Running\n", time, pro[i].pro_pid);
				if(pro[i+1].arr_time == time && pro[i].ser_time > pro[i+1].arr_time){
					printf("[%d] PID(%d) : Not-Running\n", time, pro[i+1].pro_pid);
				}
				if(time == pro[i].arr_time + pro[i].ser_time){
					printf("[%d] PID(%d) : Exit\n",time, pro[i].pro_pid);
					break;
				}
			}
		if(time > pro[i].arr_time){
			break;
		}
		}
		i++;
		
		
	}
		



//	for(i=0; i< num_pro; i++){
//		pro[i].total_time = pro[i].wait_time + pro[i].ser_time; //전체 동작시간
//		printf("PID (%d) -> Total Time : %d\n",pro[i].pro_pid ,pro[i].total_time);
//	}


}

int main(){
	int select; //실행버튼 
	int n;
	int i = 0;
	int index = 0;
	int num_pro;
	
	process *queue;

	while(1){
		printf("프로세스를 시작하려면 1을, 종료하려면 0을 눌러주세요.\n");
		scanf("%d",&select);

		if(select == 1){
			printf("====\n");
			printf("SRT\n");
			printf("====\n");
			
			FILE *fp;
			fp=fopen("process_list.txt","r");
			fscanf(fp, "%d", &num_pro);//첫줄 프로세스 갯수

			queue = (process*)malloc(sizeof(process)*n); //동적할당

			while(!feof(fp)){
				fscanf(fp, "%d", &queue[i].pro_pid);
				fscanf(fp, "%d", &queue[i].arr_time);
				fscanf(fp, "%d", &queue[i].ser_time);
				
				index = index + 1;
				i++;
				
				queue[i].turn_time = 0;
				queue[i].wait_time = 0;
				queue[i].resp_time = 0;
					
				if(feof(fp) != 0)
					break;
		
			}
			pro_sort(queue, num_pro); //오름차순 검사
		
//			printf("Process Count : %d\n", num_pro);//프로세스 개수 출력
		
			for(i=0; i < num_pro; i++){
				if (queue[i].pro_pid < 0 || queue[i].pro_pid > 99999){  
					//PID값 범위검사
					printf("\nPID 값은 0과 99,999 사이여야합니다.\n");
					printf("PID(%d) PID값 초과\n", queue[i].pro_pid);
					break;
					
					}
				else{
				//	printf("PID(%d)   Arrival Time : %d   Service Time : %d  \n", queue[i].pro_pid, queue[i].arr_time, queue[i].ser_time); //프로세스 리스트 출력
					}
			}
					
			pro_SRT(queue, num_pro);//SRT수행하여 동작시간 순서 변경			
//			pro_run(queue, num_pro); //SRT  동작 수행시간 계산 출력
	
			for(i=0; i<num_pro; i++){
				printf("PID(%d)  Turnaround Time : %d  Waiting Time : %d  Response Time : %d\n", queue[i].pro_pid, queue[i].turn_time, queue[i].wait_time, queue[i].resp_time);
		}


			pro_average(queue, num_pro);
	
						
			break;	

		}
		

		else if(select == 0){
			printf("종료합니다\n");
			break;
		}
		else{
			printf("0또는 1을 눌러주세요\n");
			printf("프로세스를 시작하려면 1을, 종료하려면 0을 눌러주세요.\n");
			scanf("%d",&select);
			}
		
	}
}			
