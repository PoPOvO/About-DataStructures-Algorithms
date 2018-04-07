#include <stdio.h> 

#include "gcd.h"

typedef int(*actualGCD)(int, int);

//定义函数指针数组 
static const actualGCD gcdType[] = {
	exhaustionGCD,            //穷举法 
	euclidGCD,                //欧几里得法(辗转相处) 
	chinaGCD                  //更相减损法(出自九章算术) 
};

/*
 求最大公约数
 m、n为目标数
 GCD_TYPE：所选择的求最大公约数的函数 
*/ 
int gcd(int m, int n, int GCD_TYPE);

int gcd(int m, int n, int GCD_TYPE) {
	return gcdType[GCD_TYPE](m, n);
}

int main(void) {	
	printf("结果:%d\n", gcd(64, 18, 2));
		
	return 0;
}