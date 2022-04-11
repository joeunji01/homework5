/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //큐 최대 크기

typedef char element;  
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //char형 element가 배열 queue의 원소로
	int front, rear; 
}QueueType; 


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	printf("[----- [조은지]  [2021076020] -----]");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ; //구조체 포인터 
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ =구조체 크기만큼 동적 메모리 할당
	cQ->front = 0; 
	cQ->rear = 0;
	return cQ; //포인터 반환
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{
	element item; //char형 item 
	printf("Input element = "); 
	scanf(" %c", &item); //item 입력
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ->front==cQ->rear) { 
		//front와 rear이 값은 값을 가리킴 (초기값 0)-> 배열에 원소가 들어있지 않음
		printf("queue is empty");
		return 1; }

    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if(((cQ->rear+1)%MAX_QUEUE_SIZE)==cQ->front){ 
		//큐 배열의 rear+1의 값과 front가 같음. rear 위치의 다음이 (삽입할 곳) 채워져있음 
		printf("queue is full");
		return 1;
	}
   return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item) //구조체와 item이 매개변수
{
	if(isFull(cQ)) //큐가 꽉 찼으면 삽입X
		return ;
	else {
	cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE; 
	//현재 rear의 값을 +1 (값이 MAX를 넘어갈 경우 queue[0] 위치)
	cQ->queue[cQ->rear]=item; //queue[rear]=item 삽입
	return ;
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return ;
	else {
		cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE;
		//front가 가리키는 값+1
		*item=cQ->queue[cQ->front];
		//item을 front로 
		return ;
	}
} 


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;  //first : front 다음 값 =삽입된 위치
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last : rear 다음 값

	printf("Circular Queue : [");

	i = first;
	while(i != last){ 
		printf("%3c", cQ->queue[i]); //삽입된 위치부터 출력
		i = (i+1)%MAX_QUEUE_SIZE; //i 증가

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) { 
			//front가 가리키는 위치 출력
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //큐의 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


