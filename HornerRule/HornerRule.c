#include <stdio.h>

/*
 ���û��ɷ���������ʽ 
 x:����ʽ�Ļ�Ԫ 
 coefficients:ϵ�����飬��Ӧ�±����ָ���Ĵη�(�÷�ʽ����������ɿռ���˷�) 
*/
double hornerRole(double x, double *coefficients, int size);

double hornerRole(double x, double *coefficients, int size) {
	double sum = coefficients[size-1];						//��Ϊsum����ֵΪĩϵ�� 
	int count = 1;
	
	for (count; count < size; count++) { 					//�������ָ��Ϊn�Ķ���ʽѭ��n-1�� 
		sum = sum*x + coefficients[size-count-1	];
	}
	return sum;
} 

int main(void) {
	double coef[] = {
		2,2,2,2
	};
	
	printf("����ʽ��:%f\n", hornerRole(2, coef, 4));
	
	return 0;
}