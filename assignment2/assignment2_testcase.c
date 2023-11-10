//주석처리한 코드는 i에 영향을 받지 않는 매개변수와 int형이 아닌 구조체 node의 배열이 i에 영향을 받는 매개변수로 입력되는 경우의 코드
//단지 int형 배열일 경우에만 호출이 성립하는 것인지 아닌지를 확인

#include <stdio.h>

int i = 0;

int a[2] = { 1, 1 };
/*
typedef struct node {
    int num;
    int memory;//크기 늘리기 위해서만 사용, 실제 사용X
}node;
node A[2];
*/
void p_reference(int* x, int* y) {
    (*x)++;    i++;    (*y)++;
}
void p_value_result_call(int x, int y, int* px, int* py) {
    x++;    i++;    y++;
    *px = x;
    *py = y;
}
void p_value_result_return(int x, int y, int* px, int* py, int* (*pf)(int*, int), int* pn,int n) {
    x++;    i++;    y++;
    *(*pf)(px, *pn - n) = x;
    *(*pf)(py, *pn - n) = y;
}
void p_name(int x, int y, int* px, int* py, int* (*pf)(int*, int), int* pn,int n) {
    x++;
    *(*pf)(px, *pn) = x;
    i++;
    y++;
    *(*pf)(py, *pn) = y;
}
//상태를 업데이트 시켜주는 함수가 있다면? 배열=>&a[i]가 a+i형태로 넘어감, 일반 변수 => px가 px로 유지됨
//n이 0인지 i인지 구분해야함--main에서만 구분 가능?--int zero=0과 int*pz=&zero 사용
int* update(int* p, int n)
{
    return p + n;
}
/*
int* update_node(node* p, int n)//test용
{
    return p + n;
}
*/
int main() {
    int* pi = &i;//parameter가 i에 영향을 받을 경우 사용됨.
    /*
    int zero = 0;
    int x = 1;
    int y = 1;
    int* px = &x;
    int* py = &y;
    int* pz = &zero;//i에 영향을 받지 않는 parameter가 사용될 경우 사용됨
    */
    p_reference(&a[i], &a[i]);//pass by reference
    printf("%d %d\n", a[0], a[1]);

    a[0] = 1;
    a[1] = 1;
    i = 0;
    p_value_result_call(a[i], a[i], &a[i], &a[i]);//pass by value result determined at call
    printf("%d %d\n", a[0], a[1]);

    a[0] = 1;
    a[1] = 1;
    i = 0;
    p_value_result_return(a[i], a[i], &a[i], &a[i], update, pi,i);//pass by value result determined at return
    printf("%d %d\n", a[0], a[1]);

    a[0] = 1;
    a[1] = 1;
    i = 0;
    p_name(a[i], a[i], &a[i], &a[i], update, pi,i);//pass by reference
    printf("%d %d\n", a[0], a[1]);

    //제대로 작동한다면 배열뿐만 아니라 다른 경우에서도 제대로 동작해야된다고 생각됨...
    //case 1 i에 영향을 받지 않는 변수 사용
    /*
    p_reference(px, py);
    printf("x y\n%d %d\n", x, y);

    x = 1;
    y = 1;
    i = 0;
    p_value_result_call(x, y, px, py);
    printf("%d %d\n", x, y);

    x = 1;
    y = 1;
    i = 0;
    p_value_result_return(x, y, px, py, update, pz,zero);
    printf("%d %d\n", x, y); x = 1;

    y = 1;
    i = 0;
    p_name(x, y, px, py, update, pz,zero);
    printf("%d %d\n", x, y);
    */
    //case 2
    //i에 영향을 받는 구조체 사용시->update함수를 다시 구현해야함--->update_node
    /*
    A[0].memory = 0;
    A[1].memory = 0;
    printf("A\n");

    A[0].num = 1;
    A[1].num = 1;
    i = 0;
    p_reference(&A[i].num, &A[i].num);
    printf("%d %d\n", A[0].num, A[1].num);

    A[0].num = 1;
    A[1].num = 1;
    i = 0;
    p_value_result_call(A[i].num, A[i].num, &A[i].num, &A[i].num);
    printf("%d %d\n", A[0].num, A[1].num);

    A[0].num = 1;
    A[1].num = 1;
    i = 0;
    p_value_result_return(A[i].num, A[i].num, &A[i].num, &A[i].num, update_node, pi,i);
    printf("%d %d\n", A[0].num, A[1].num);

    A[0].num = 1;
    A[1].num = 1;
    i = 0;
    p_name(A[i].num, A[i].num, &A[i].num, &A[i].num, update_node, pi,i);
    printf("%d %d\n", A[0].num, A[1].num);
    */
    return 0;

}