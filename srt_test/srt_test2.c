#include <stdio.h>
#include <stdlib.h>


typedef struct process{
	int num_pro, arr_time, ser_time, pro_pid;
	//프로세스 번호,  도착시간, 서비스시간, 프로세스 아이디 
	int turn_time;//프로세스 실행이 종료되는시간 - arr_time
	int wait_time;//큐에 머무는 시간의 합 or not running 시간의 합
	int resp_time;//cpu를 맨처음 점유한시간 - arr_time or 처음 running state가 된시간 - arr_time
	int stop_time;
	int flag;

}process;

void pro_State(process *pro, int num_pro){ //프로세스 상태표시
	char state_0[] = "Not-Running";
	char state_1[] = "Running";
	char state_2[] = "Exit";
	int i = 0;
	


}


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

void pro_choice(process *pro, int num_pro, int time, process *start){//프로세스 선택
	int i;
	process *temp; //프로세스 초기값

	if(start == NULL) //작업이 맨 처음일때 실행중인 프로세스가 없을때
		temp = &pro[0];
	else
		temp = start;

	for(i=0; i<num_pro; i++){
		if(pro[i].arr_time <= time && pro[i].ser_time != 0){
		//i번째 프로세스가 현재시간보다 작거나 같고, 실행시간이 0이 아닌 것 중
			if(temp->ser_time == 0 || temp->ser_time > pro[i].ser_time)
				temp = &pro[i]; //실행시간이 작은것을 선택
		}
	}
	if(temp->arr_time > time) //temp안에 있는  time과 arr_time을 확인
		temp = NULL;
	
//	return temp;
}

void pro_wait(process *pro, int num_pro){//wait 시간
	int i;
	int wait = 0;
	for (i = 0; i < num_pro; i++){
		wait += pro[i].wait_time;
	}
//	return wait;
}

void pro_check(process *pro, int num_pro){
	int i;
	int result;

	for(i=0; i<num_pro; i++){
		if(pro[i].ser_time != 0)
			result = 1;
	}
//	return 0;
}

void pro_average(process *pro, int num_pro){
	int i, j;
	for(i = 0; i<num_pro; i++){
		pro[i+1].turn_time += pro[i].turn_time;
		pro[i+1].wait_time += pro[i].wait_time;
		
		}
	printf("%d %d\n",pro[i].turn_time, pro[i].wait_time);		
	float average_turn_time = pro[i].turn_time/num_pro;

	float average_wait_time = pro[i].wait_time/num_pro;

	printf("\n\nAverage Turnaround Time : %0.2f\nAverage Waiting Time : %0.2f\nAverage Response Time : \n", average_turn_time, average_wait_time);

}

void pro_SRT(process *pro, int num_pro, int time, process *choice){//SRT 수행 코드
	
	int now_time = 0;//현재시간
	int total_time; // = arr_time + ser_time; //전체 동작시간
	int i;
	
		
	printf("\nLog of Process Scheduling\n");

	pro[0].wait_time = 0;//처음들어온 프로세스의 대기시간은 0이다.
	for(i=1; i < num_pro; i++){
		if(pro[i-1].ser_time + pro[i-1].arr_time < pro[i].arr_time)
			pro[i].wait_time = 0;
		else	
			pro[i].wait_time = pro[i-1].arr_time + pro[i-1].ser_time - pro[i].arr_time;
	}

	for(i=0; i<num_pro; i++){
		pro[i].turn_time = pro[i].wait_time + pro[i].ser_time;
		printf("PID(%d)  Turnaround Time : %d  Waiting Time : %d\n", pro[i].pro_pid, pro[i].turn_time, pro[i].wait_time);
		}

}

int main(){
	int select; //실행버튼 
	int n;
	int i = 0;
	int index = 0;
	int num_pro;
	int time = 0;
	int result;

	process *queue;
	process *start = NULL; //작업이 처음인지 판단
	process *temp = NULL; //초기값

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
		
			printf("Process Count : %d\n", num_pro);//프로세스 개수 출력
		
			for(i=0; i < num_pro; i++){
				if (queue[i].pro_pid < 0 || queue[i].pro_pid > 99999){  
					//PID값 범위검사
					printf("\nPID 값은 0과 99,999 사이여야합니다.\n");
					printf("PID(%d) PID값 초과\n", queue[i].pro_pid);
					break;
					
					}
				else{
					printf("PID(%d)   Arrival Time : %d   Service Time : %d  \n", queue[i].pro_pid, queue[i].arr_time, queue[i].ser_time); //프로세스 리스트 출력
					}
			}
					
//			pro_State(queue, num_pro);	//프로세스 상태표시 출력
			
//			pro_choice(queue, num_pro, time, start); //프로세스 선택

//			pro_wait(queue, num_pro);
			

			pro_SRT(queue, num_pro, time, start); //SRT 동작

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
