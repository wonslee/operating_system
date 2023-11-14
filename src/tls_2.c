#include <pthread.h> // pthread 라이브러리를 사용하기 위해 필요한 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void* calcThread(void *param); // 스레드로 작동할 코드
static __thread int sum = 0; // __thread : 스레드 공유 변수. main 스레드와 calcThread가 공유하는 전역 변수

int main() {
        pthread_t tid; //  스레드의 id를 저장할 정수형 변
        pthread_t tid_second;
        pthread_attr_t attr; // 스레드 정보를 담을 구조체

        pthread_attr_init(&attr); // 디폴트 값으로 attr 초기화
        pthread_create(&tid, &attr, calcThread, "100"); // calcThread 스레드 생성
        pthread_create(&tid_second, &attr, calcThread, "100");
        // 스레드가 생성된 수 커널에 의해 언젠가 스케줄되어 실행

        printf("main pid = %d \n", getpid());
        printf("sum = %d\n", sum);


        pthread_join(tid, NULL); // tid 번호의 스레드 종료를 기다림
        printf("calcThread 스레드가 종료하였습니다.\n");

        pthread_join(tid_second, NULL); // tid 번호의 스레드 종료를 기다림
        printf("calcThread 스레드가 종료하였습니다.\n");
}

void* calcThread(void *param) { // param에 "100" 전달 받음
        printf("calcThread 스레드가 실행을 시작합니다. %lu \n", pthread_self());
        int to = 100;
        int s = 0;

        for(int i=1; i<=to*200; i++) // 1에서 to까지 합 계산
                s += i; // 전역 변수 sum에 저장

        sum += s;
        printf("sum = %d\n", sum);
}
