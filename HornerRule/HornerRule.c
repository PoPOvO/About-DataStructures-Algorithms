#include <stdio.h>

/*
 利用霍纳法则计算多项式 
 x:多项式的基元 
 coefficients:系数数组，对应下标代表指数的次方(该方式不合理，会造成空间的浪费) 
*/
double hornerRole(double x, double *coefficients, int size);

double hornerRole(double x, double *coefficients, int size) {
	double sum = coefficients[size-1];						//向为sum赋初值为末系数 
	int count = 1;
	
	for (count; count < size; count++) { 					//对于最高指数为n的多项式循环n-1次 
		sum = sum*x + coefficients[size-count-1	];
	}
	return sum;
} 

int main(void) {
	double coef[] = {
		2,2,2,2
	};
	
	printf("多项式和:%f\n", hornerRole(2, coef, 4));
	
	return 0;
}