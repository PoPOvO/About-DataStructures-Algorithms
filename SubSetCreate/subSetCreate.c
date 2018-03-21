#include<stdio.h>
#include<string.h>
#include<math.h>

/*
 建立一个子集
 str:子集序列 
*/ 
void createSubset(char *str);

void createSubset(char *str) {
	int i;
	static int count = 0;
	
	for(i = strlen(str) - 1; i >= 0 && str[i] == '1'; i--);  //从右向左遍历字符串，找到最右边0的下标 
	if(i >= 0){ 											 //将最右0后的元素都置0 
		str[i] = '1';
		for( ++i; str[i]; i++){
			str[i] = '0';
		} 
	} 
	printf("子集%d:%s\n", ++count, i >= 0 ? str : "该串全是1"); 
}

int main(void) {
	char str[6] = "0000";
	int i;
	
	for(i = 0; i < (int)pow( 2, (double)strlen(str)); i++) {
		createSubset(str);	
	}
	
	return 0;	
}