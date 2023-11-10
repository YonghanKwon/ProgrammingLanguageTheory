#include <stdio.h>

int i = 0;

int a[2] = { 1, 1 };

void p_reference(int* x, int* y) {
    (*x)++;    i++;    (*y)++;
}
void p_value_result_call(int x, int y,int*px,int*py) {
    x++;    i++;    y++;
    *px = x;
    *py = y;
}
void p_value_result_return(int x, int y,int* px ,int* py,int*(*pfx)(int*,int),int*(*pfy)(int*,int),int*pn) {
    x++;    i++;    y++;
    *(*pfx)(px, *pn) = x;
    *(*pfy)(py, *pn) = y;
}
void p_name(int x, int y, int* px, int* py, int* (*pfx)(int*, int), int* (*pfy)(int*, int), int* pn) {
    x++;
    *(*pfx)(px, *pn) = x;
    i++; 
    y++;
    *(*pfy)(py, *pn) = y;
}
//상태를 업데이트 시켜주는 함수가 있다면? 배열=>&a[i]가 a+i형태로 넘어감, 일반 변수 => px가 px로 유지됨
int* update(int* p, int n)//n이 0인지 i인지 구분해야함--main에서만 구분 가능?
{
    return p + n;
}
int main() {
    int* pi = &i;//parameter가 i에 영향을 받을 경우 사용됨.
    p_reference(a,a);//pass by reference
    printf("%d %d\n", a[0], a[1]);
    
    a[0] = 1;
    a[1] = 1;
    i = 0;
    p_value_result_call(a[i], a[i],&a[i],&a[i]);//pass by value result determined at call
    printf("%d %d\n", a[0], a[1]);

    a[0] = 1;
    a[1] = 1;
    i = 0;
    p_value_result_return(a[i], a[i], a, a, update, update, pi);//pass by value result determined at return
    printf("%d %d\n", a[0], a[1]);

    a[0] = 1;
    a[1] = 1;
    i = 0;
    p_name(a[i], a[i], a, a, update, update, pi);//pass by reference
    printf("%d %d\n", a[0], a[1]);

    return 0;

}