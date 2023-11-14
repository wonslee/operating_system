#include <pthread.h> // pthread 라이브러리를 사용하기 위해 필>요한 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void* calcThread(void *param); // 스레드로 작동할 코드
int sum = 0; // __thread : 스레드 공유 변수. main 스레드와 calcThread가 공유하는 전역 변수
pthread_spinlock_t lock;

int main() {
	 pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
	 for(int i=0; i<10; i++){
                pthread_t tid;
                pthread_attr_t attr;
                pthread_create(&tid, &attr, calcThread, "100"); // calcThread 스레드 생성
                 pthread_join(tid, NULL); // tid 번호의 스레드 종
        printf("calcThread 스레드가 종료하였습니다.\n");
        }

        printf("sum = %d\n", sum);

}

void* calcThread(void *param) { // param에 "100" 전달 받음
        printf("calcThread 스레드가 실행을 시작합니다. %lu \n", pthread_self());
        int to = 100;
        int s = 0;


        for(int i=1; i<=to*2000; i++) // 1에서 to까지 합 계산
        {
		pthread_spin_lock(&lock);
                sum += i; // 전역 변수 sum에 저장
	 pthread_spin_unlock(&lock);
                }
        //      sum += s;
        printf("sum = %d\n", sum);
}
