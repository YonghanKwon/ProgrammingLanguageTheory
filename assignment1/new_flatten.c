#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* nodePointer;

typedef struct node {
	int data;
	char* current_str;
	char* str_next;
	nodePointer next;
}node;

nodePointer get_node()
{
	nodePointer* ptr;
	ptr = (nodePointer*)malloc(sizeof(node));
	return ptr;
}

nodePointer array_num;

int flatten(char* data);
void node_free();
void remove_bracket(char* data, nodePointer list);

int main()
{
	char data[] = "[1, [-2, [[[4]]],[0, 5], [], 3], [4], 2, 7]";//이러한 표현방법을 찾지 못해 string으로 표현
	int a;//flatten시행 결과를 담아두는 변수
	int sum = 0;
	while (sum < 10) {
		a = flatten(data);
		sum += a;
		printf("%d\n", a);
		if (sum >= 10)
			flatten(NULL);//list 초기화
	}
	printf("sum = %d\n", sum);	

	return 0;

}

void node_free() 
{
	nodePointer f, temp;//동적 메모리 해제
	temp = array_num;
	while (1)
	{
		if (temp != NULL) {
			f = temp->next;
			if (temp->current_str != NULL) {
				free(temp->current_str);
			}
			if (temp->str_next != NULL) {
				free(temp->str_next);
			}
			free(temp);
			temp = f;
		}
		else
			break;
	}
}

int flatten(char* data)
{
	static int counter = 0;//첫 경우엔 array_num에 노드를 받기위해 몇번째인지 세기 위해 static으로 선언, array_num이 main함수에서 노드를 받게된다면 없어도 됨


	if (data==NULL)//리스트 초기화(연산 끝난경우)
	{
		node_free();
		counter = 0;
		return 0;
	}
	else {
		int length = strlen(data);
		char* str_temp;
		str_temp = (char*)malloc(sizeof(char) * (length + 1));
		strcpy(str_temp, data);
		if (counter == 0)
		{
			array_num = get_node();
			array_num->next = NULL;
		}
		nodePointer current;
		current = array_num;
		while (current->next != NULL)
		{
			length = strlen(current->str_next);
			str_temp = (char*)malloc(sizeof(char) * (length + 1));
			strcpy(str_temp, current->str_next);
			current = current->next;

		}

		current->current_str = (char*)malloc(sizeof(char) * (length + 1));
		strcpy(current->current_str, str_temp);

		remove_bracket(current->current_str, current);
		current->next = get_node();
		current->next->next = NULL;
		current->next->current_str = NULL;
		current->next->str_next = NULL;
		free(str_temp);
		counter++;
		return current->data;
	}
}

void remove_bracket(char* data, nodePointer list)
{
	int result_i;
	int length = strlen(data);
	int i = 1;
	char* list_char;
	char* result = strtok(data, " [],");
	int a = sizeof(data);
	result_i = atoi(result);
	list->data = result_i;
	list_char = (char*)malloc(sizeof(char) * (length + 1));
	list_char[0] = '[';
	result = strtok(NULL, " [],");

	while (result != NULL)
	{
		for (int j = 0; j < strlen(result); j++)
		{
			list_char[i++] = result[j];
		}
		list_char[i++] = ',';
		result = strtok(NULL, " [],");
	}
	list_char[i - 1] = ']';

	list_char[i] = NULL;
	list->str_next = (char*)malloc(sizeof(char) * (i + 1));
	strcpy(list->str_next, list_char);
	free(list_char);
}