#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {//stack에 저장될 요소, int형 배열과 그 크기
	int size;
	int* arr;
}element;

typedef struct stack* stackPtr;
typedef struct stack{//stack, 동적 크기
	element set;
	stackPtr link;
}stack;
stackPtr top = NULL;

void push(element item);
element pop();

int sort_gen(int* data,int size);

int* get_int_array(char* data);

int length = 0;//data가 몇개의 값을 가지고 있는지 저장

int main()
{
	char data_str[] = "[3, 1, -5, 7, -4, 2, 6, 200, 9, -2, 4, 3, 0, -2] + [100] * 100000";//이러한 표현방법을 찾지 못해 string으로 표현
	int a;//sort_gen시행 결과를 담아두는 변수
	int sum = 0;
	int* data;
	data = get_int_array(data_str);//char형으로 저장된 값을 int형으로 변환, int형의 배열 획득
	for (int i = 0; i < 20; i++)
	{
		a = sort_gen(data,length);//length를 모르면 배열의 크기를 판단할 수 없음
		printf("%d ", a);
	}
	sort_gen(NULL, 0);
	printf("\n");
	while (sum <= 50) 
	{
		a = sort_gen(data,length);
		sum += a * a;
		if (sum > 50) {
			printf("Sum = %d\n", sum);
			break;
		}
	}
	
	return 0;

}

int sort_gen(int* data, int size)
{
	static int checker = 0;//pivot이 return된 후 다시 함수에 접근하는 것인지 recursion에 의해 다시 함수에 접근하는 것인지 구분하는 변수
	int pivot;//return값
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	element bigger;
	element smaller;
	element same;
	element next;

	if (data != NULL) {//한번의 sort_gen 사용이 끝나고 stack을 비우고 원하는 데이터를 입력받아 사용하기 위해
		if (checker == 0) {//recursion에 의해 접근된 경우
			next.arr = data;
			next.size = size;
			push(next);//밑에서 pop하기 때문에 push해서 pop이 한번 더 일어나는 것을 방지함
		}
		next = pop();	//매개변수 값이 아닌 stack에 저장된 값을 사용하기 위함, recursion을 통해 접근하였다면 이미 pop을 한 후 그 값을 매개변수에 주기때문에
						//매개변수값을 next에 저장 후 push하여 stack에 저장하는 과정을 거침

		pivot = next.arr[0];//첫번째 값을 pivot으로
		size = next.size;//배열의 크기
		bigger.arr = (int*)malloc(sizeof(int) * size);//크거가 작거나 같은 값이 몇개인지 모르기에 최대 갯수로 동적할당
		smaller.arr = (int*)malloc(sizeof(int) * size);
		same.arr = (int*)malloc(sizeof(int) * size);
		while (i < size)//큰값과 작은값, 같은값 구분
		{
			if (next.arr[i] > pivot) {
				bigger.arr[j++] = next.arr[i];
			}
			else if (next.arr[i] < pivot) {
				smaller.arr[k++] = next.arr[i];
			}
			else
			{
				same.arr[l++] = next.arr[i];
			}
			i++;
		}
		bigger.size = j;//큰값, 작은값, 같은값의 원소의 개수가 몇개인지 기록
		smaller.size = k;
		same.size = l;
		if (bigger.size > 0)//원소가 있을때만 stack에 push
			push(bigger);
		if (same.size > 0)
			push(same);
		if (smaller.size > 0)
			push(smaller);


		if (smaller.size == 0) {//더 작은 값이 없으므로 pivot이 가장 작음>>return pivot
			checker = 1;//다음에 함수가 호출된다면 recursion에 의한 호출이 아니기에 매개변수를 무시하고 stack에서 pop하여 사용함
			next = pop();//pivot과 stack에 저장된 값을 비교하기 위해 pop
			if (pivot == next.arr[0]) {//pivot에 값이 다음의 값과 같은 경우, 실제로 중복된 값이 있거나 아니면 pivot의 값이 stack에 들어가 있는 경우가 있음
				next.size--;//이때 두 경우 모두 pivot이 포함되어 있기 때문에 값을 하나 줄여서 이를 방지함
				if (next.size > 0)//값을 줄이고도 size가 0보다 크다면 데이터 자체에 중복된 값이 있는것이므로 
					push(next);//stack에 다시 push, 만일 size가 0또는 그보다 작다면 중복된 값이 없는 것이므로 push하지 않음
			}
			else
				push(next);//pop한 배열을 다시 stack에 push(배열이 pivot보다 더 큰 경우)
			return pivot;
		}
		else {
			checker = 0;//다음에 함수가 호출된다면 recursion에 의해 호출되는 것이기에 매개변수를 살림
			next = pop();//recursion시 다음에 매개변수로 필요한 값을 stack에서 pop
			return sort_gen(next.arr, next.size);
		}
	}
	else//기존의 sort_gen의 사용이 마쳤기에 기존 stack에 있던 값을 모두 pop하고 static 변수를 0으로 초기화
	{
		next=pop();
		while (next.arr!=NULL)//stack의 값 모두 pop
		{
			next = pop();
		}
		checker = 0;//static변수 초기화

	}
}

void push(element item)//stack push
{
	stackPtr temp;
	temp = (stackPtr)malloc(sizeof(stack));
	if (!temp)
	{
		item.arr = NULL;
		item.size = 0;
		return item;
	}
	temp->set = item;
	temp->link = top;
	top = temp;
}

element pop()//stack pop
{
	stackPtr temp = top;
	element item;
	if (!temp) {//stack이 empty면 item.arr=NULL을 통해 stack이 empty인 것을 판단함
		item.arr = NULL;
		item.size = 0;
		return item;
	}
	item = temp->set;
	top = top->link;
	free(temp);
	return item;
}


int*  get_int_array(char* data)//char배열을 int배열로 변환시켜줌
{
	char* copy;
	int result_i;
	int length_data = strlen(data);
	copy = (char*)malloc(sizeof(char) * (length_data + 1));
	strcpy(copy, data);

	int i = 0;
	int multiplier = 0;
	int checker_a = 0;
	int checker_b = 0;
	int* array_i;
	char* result = strtok(copy, " [],");
	while (result != NULL)
	{
		length++;
		if (checker_a == 1)//+뒤의 문자는 반복되는 문자이지 반복횟수가 아니기에 length에 고려하지 않음
		{
			length--;
		}
		if (result[0] == '+') {//기호는 length에 고려하지 않음
			checker_a = 1;
			length--;
		}
		else
			checker_a = 0;

		
		if (checker_b == 1)//length+=multiplier에서 multiplier번 더하기에 여기서 length 하나 감소
		{
			multiplier = atoi(result);
			length--;
		}

		if (result[0] == '*') {//기호는 length에 고려하지 않음
			checker_b = 1;
			length--;
		}
		else
			checker_b = 0;
		length +=  multiplier;

		result = strtok(NULL, " [],");
	}

	strcpy(copy, data);
	array_i = (int*)malloc(sizeof(int) * length);
	int n;
	int m;
	checker_a = 0;
	checker_b = 0;
	result = strtok(copy, " [],");
	while (result != NULL)
	{
		if (checker_a == 0) {
			if (result[0] != '+' && result[0] != '*') {//+나 *이 아니고 +와 *가 나오기 전의 값들은 모두 int형으로 저장
				array_i[i] = atoi(result);
				i++;
			}
		}
		if (checker_a == 1)//+가 나온 직후의 값을 n에 저장
		{
			n = atoi(result);
			checker_a = 2;
		}
		if (checker_b == 1)//*가 나온 직후의 값을 m에 저장
		{
			m = atoi(result);
			checker_b = 2;
		}
		if (checker_a == 2 && checker_b == 2)//n과 m에 값이 저정되었으므로, 배열에 n을 m번 저장
		{
			for (int j = 0; j < m; j++)
			{
				array_i[i++] = n;
			}
		}
		if (result[0] == '+') 
			checker_a = 1;
		
		if (result[0] == '*') 
			checker_b = 1;

		result = strtok(NULL, " [],");
	}

	return array_i;
}