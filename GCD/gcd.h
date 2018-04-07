#ifndef _GCD_H_
#define _GCD_H_

#include <conio.h>

//更相减损法 
int chinaGCD(int m, int n) {
	static int count = 1;
	while((m%2 == 0 && n%2 == 0) ? (m>>=1) > 0 && (n>>=1) > 0 : !(m%2 == 1 || n%2 == 1))
		count<<=1;
	if (m == n) return m*count;
	m > n ? (m -= n) : (n -= m);
	return (m == n) ? m*count : chinaGCD(m, n);
}

//辗转相除法 
int euclidGCD(int m, int n) {
	return (m % n) != 0 ? euclidGCD(n, m % n) : n;
}

//穷举法 
int exhaustionGCD(int m, int n) {
	int i;
	for (i = (m > n ? n : m); i > 1; i--) {
		if (m % i == 0 && n % i == 0) {
			return i;
		}
	}
	return 1;
} 

#endif