#include <stdio.h> 
#include <time.h>

int main(void) {
	int a = 4;
	int b = 6;
	time_t start,end;
	int i = 0;
	
	start = clock();	
	while (i++ < (1 << 30)) {
		a = a+b;;
		b = a-b;
		a = a-b;
	}
	end	= clock();
	
	printf("%d:%f\n", a, difftime(end, start));
	
	return 0;
}