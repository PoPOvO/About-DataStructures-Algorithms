#include<stdio.h>
#include<string.h>
#include<math.h>

/*
 ����һ���Ӽ�
 str:�Ӽ����� 
*/ 
void createSubset(char *str);

void createSubset(char *str) {
	int i;
	static int count = 0;
	
	for(i = strlen(str) - 1; i >= 0 && str[i] == '1'; i--);  //������������ַ������ҵ����ұ�0���±� 
	if(i >= 0){ 											 //������0���Ԫ�ض���0 
		str[i] = '1';
		for( ++i; str[i]; i++){
			str[i] = '0';
		} 
	} 
	printf("�Ӽ�%d:%s\n", ++count, i >= 0 ? str : "�ô�ȫ��1"); 
}

int main(void) {
	char str[6] = "0000";
	int i;
	
	for(i = 0; i < (int)pow( 2, (double)strlen(str)); i++) {
		createSubset(str);	
	}
	
	return 0;	
}