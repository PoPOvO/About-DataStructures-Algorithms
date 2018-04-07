#include <stdio.h> 

#include "gcd.h"

typedef int(*actualGCD)(int, int);

//���庯��ָ������ 
static const actualGCD gcdType[] = {
	exhaustionGCD,            //��ٷ� 
	euclidGCD,                //ŷ����÷�(շת�ദ) 
	chinaGCD                  //�������(���Ծ�������) 
};

/*
 �����Լ��
 m��nΪĿ����
 GCD_TYPE����ѡ��������Լ���ĺ��� 
*/ 
int gcd(int m, int n, int GCD_TYPE);

int gcd(int m, int n, int GCD_TYPE) {
	return gcdType[GCD_TYPE](m, n);
}

int main(void) {	
	printf("���:%d\n", gcd(64, 18, 2));
		
	return 0;
}