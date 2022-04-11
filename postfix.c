/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	printf("[----- [조은지]  [2021076020] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //top+1 =postfixStack[0] 
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1) //paren이 push 되어있지 않음
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //push 한 후 top-1 
    }
    return x; //x를 반환하기 때문에 stack에 값 남아있음
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //top+1 에 push
}

int evalPop()
{
    if(evalStackTop == -1) //top이 가리키고 있지 않음
        return -1;
    else
        return evalStack[evalStackTop--]; //pop한 후 top-1
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //연산 식 입력
}


precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp[0] == 0) //배열이 비어있을 경우 
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		/* 필요한 로직 완성 */
		if(getPriority(*exp) == operand) //피연산자
		{
			x = *exp; //x에 임시저장 후 
        	charCat(&x); //postfixExp에 저장
		}
        else if(getPriority(*exp) == lparen) {

        	postfixPush(*exp); //stack에 push
        }
        else if(getPriority(*exp) == rparen)
        {
        	while((x = postfixPop()) != '(') { //stack에 top이 '(' 아님
        		charCat(&x); //pop한 연산자 ->postfixExp에 저장
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
			//stack의 top이 exp보다 우선순위 높음 
			
            {
            	x = postfixPop(); // pop 한 후
            	charCat(&x); // postfixExp에 저장
            }
			//(괄호 안의 값)
            postfixPush(*exp); //postfixExp에 저장
        }
        exp++;

	}

	/* 필요한 로직 완성 */
	while(postfixStackTop != -1)
    {
		//top이 가리키고 있는동안
    	x = postfixPop(); //pop -> postfixExp에 저장
    	charCat(&x);
    }

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); //stack에 있는 연산자 

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //배열초기화
	postfixExp[0] = '\0'; //배열초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	int opr1, opr2, i; 

	int length = strlen(postfixExp); 
	char symbol;
	evalStackTop = -1; 

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i]; //postfixExp 문자열 하나씩 가져옴
		if(getToken(symbol) == operand) { 
			//symbol이 피연산자이면 
			evalPush(symbol - '0'); //값 그대로 stack에 push
		}
		else { //연산자 or ()
			opr2 = evalPop(); //피연산자2 pop 
			opr1 = evalPop(); //피연산자1 pop
			switch(getToken(symbol)) {
				//연산 후 push
			case plus: evalPush(opr1 + opr2); break; 
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop(); //연산 값
}

