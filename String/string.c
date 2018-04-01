#include <stdio.h> 
#include <malloc.h>

#include "base.h"

typedef struct {
	int len;
	char *str;
} String;

boolean initString(String **pString, const char *start);
boolean destroyString(String **pString);
boolean stringClear(String *str);
int getLength(String string);
boolean stringFrontInsert(String *string, int pos, String insertedStr);
boolean stringDelete(String *string, int start, int len);
boolean subString(String *string, String **pSubString, int start, int end);
boolean stringCat(String *resultStr, String str);
boolean stringCpy(String *resultStr, String str);
boolean stringEqual(String strOne, String strTwo);
int indexOf(String source, String subStr);
boolean stringReplace(String *source, String oldStr, String newStr, boolean isReplaceAll);
void toString(String string); 

void toString(String string) {
	printf("len:%d[%s]", string.len, string.str);
}

/*
 �ַ����滻
 source:Դ��
 oldStr:���滻�Ĵ�
 newStr:�滻�Ĵ�
 isReplaceAll:TRUE���滻���У�FALSE��ֻ�滻һ�� 
*/
boolean stringReplace(String *source, String oldStr, String newStr, boolean isReplaceAll) {
	int matchIndex = NOT_FOUND;
	char *temp = NULL;
	int resLen = source->len - oldStr.len + newStr.len;
	int i = 0;
	
	if (source == NULL || oldStr.len == 0) {
		return FALSE;
	}
	
	matchIndex = indexOf(*source, oldStr);	
	if (matchIndex == NOT_FOUND) {
		return FALSE;
	}
	
	temp = (char*)calloc(sizeof(char), resLen + 1);
	while (i < resLen) {
		if (i < matchIndex) { 
			temp[i] = source->str[i];
		} else if (i >= matchIndex && i < matchIndex+newStr.len) { 
			temp[i] = newStr.str[i-matchIndex];
		} else { 
			temp[i] = source->str[i-newStr.len+oldStr.len];
		}
		i++;
	}
	free(source->str);
	source->str = temp;
	source->len = resLen;
	if (isReplaceAll) {
		stringReplace(source, oldStr, newStr, TRUE);
	} 
	return TRUE;
}

/*
 ��ƥ��
 source:Դ��
 subStr:�Ӵ� 
*/
int indexOf(String source, String subStr) {
	int i = 0;
	int j = 0;
	 
 	for (i; i <= source.len-subStr.len; i++) {
	 	for (j; j < subStr.len && subStr.str[j] == source.str[i+j]; j++);	
	 	if (j == subStr.len) {
	 		return i;
	 	}
 	}
	return NOT_FOUND;
}

/*
 �Ƚ��ַ���ֵ�Ƿ���� 
 stringOne��stringTwo:�ȽϵĴ� 
*/
boolean stringEqual(String strOne, String strTwo) {
	if (strOne.len != strTwo.len) {
		return FALSE;
	}
	
	while (strOne.len > 0) {
		if (strOne.str[strOne.len--] != strTwo.str[strOne.len]) {
			return FALSE;
		}
	}
	return TRUE;
}

/*
 �ַ�������
 resultStr:Դ��
 str:�����ƵĴ� 
*/
boolean stringCpy(String *resultStr, String str) {
	char *temp = NULL;	
	int i = 0;
		
	if (resultStr == NULL) {
		return FALSE;
	}
	temp = (char*)malloc(sizeof(char)*(str.len + 1));
	while (i < str.len) {
		temp[i++] = str.str[i];
	}
	free(resultStr->str);	
	resultStr->str = temp;
	resultStr->len = str.len;
	return TRUE;
}

/*
 �ַ�������
 resultStr:Դ��
 str:���ӵĴ� 
*/ 
boolean stringCat(String *resultStr, String str) {
	char *temp = NULL;	
	int i = 0;
	int resultLen = resultStr->len + str.len;
		
	if (resultStr == NULL || str.len == 0) {
		return FALSE;
	}
	
	temp = (char*)calloc(sizeof(char), resultLen + 1);
	while (i < resultLen) {
		if (i < resultStr->len) {
			temp[i++] = resultStr->str[i];
			continue;
		}
		temp[i++] = str.str[i-resultStr->len];
	}	
	free(resultStr->str);
	resultStr->str= temp;
	resultStr->len= resultLen;
	return TRUE;
}

/*
 ȡ�Ӵ���Դ�����䣬����subString("hello", sub, 2, 4)�����Ӵ�Ϊ"ll"
 string:Դ��
 pSubString:�Ӵ��׵�ַ����ֵӦΪNULL
 start:��ʼλ��
 end:����λ�� 
*/
boolean subString(String *string, String **pSubString, int start, int end) {
	char *temp = NULL;
	int subStrLen = end-start;
	int i = 0;
	
	if (string == NULL || *pSubString != NULL || start < 0 || start > string->len-1
		|| start > end || end > string->len-1) {
		return FALSE;
	}

	initString(pSubString, "");
	temp = (char*)calloc(sizeof(char), subStrLen + 1);
	while (i < subStrLen) {
		temp[i++] = string->str[i+start];
	}
	free((*pSubString)->str); 
	(*pSubString)->str = temp;
	(*pSubString)->len = subStrLen;
	return TRUE;
}

/*
 ɾ������һ���֣�����stringDelete("hello", 1, 1) ,���Ϊ"hllo"
 string:Դ��
 start:��ʼλ�� 
 len:ɾ�������� 
*/
boolean stringDelete(String *string, int start, int len) {
	char *temp = NULL;	
	int resultStrLen = string->len - len;
	int i = 0;
		
	if (string == NULL || start < 0 || start > string->len-1 || len < 0 || len > string->len) {
		return FALSE;
	}
	
	temp = (char*)calloc(sizeof(char), resultStrLen + 1);
	while (i < resultStrLen) {
		if (i < start) {
			temp[i] = string->str[i];
		} else if (i >= start + len) {
			temp[i] = string->str[i];
		}
		i++;
	}
	free(string->str);
	string->str= temp;
	string->len= resultStrLen;
	return TRUE;
}

/*
 ��Դ��ָ��λ��ǰ�����ַ��� 
 string:Դ��
 pos:����λ�� 
 insertedStr:���봮 
*/
boolean stringFrontInsert(String *string, int pos, String insertedStr) {
	char *temp = NULL;
	int resultStrLen = string->len + insertedStr.len;                                         //�����Ľ�������� 
	int i = 0;
	int j = 0;
	
	if (string == NULL || pos < 0 || pos > string->len || insertedStr.len == 0) {
		return FALSE;
	}
	
	temp = (char*)calloc(sizeof(char), (resultStrLen + 1));
	while (i < resultStrLen) {
		if (i < pos) {
			temp[i] = string->str[i];
		} else if (i >= pos && i < insertedStr.len + pos) {
			temp[i] = insertedStr.str[i-pos];
		} else {
			temp[i] = string->str[i-insertedStr.len];
		}
		i++;
	}
	free(string->str);
	string->str = temp;
	string->len = resultStrLen;
	return TRUE;
}

/*
 �����ַ�������
 string:�ַ�������ͷ 
*/ 
int getLength(String string) {
	return string.len;
}

/*
 ���ַ�����Ϊ�մ�
 str:�ַ�������ͷָ�� 
*/
boolean stringClear(String *str) {
	char *temp = NULL;
	
	if (str == NULL) {
		return FALSE;
	}
	temp = (char*)malloc(sizeof(char));                                 //�մ���"\0" 
	free(str->str);
	str->str = temp;
	str->len = 0;
	str->str[str->len] = '0';
	return TRUE;
}

/*
 �ͷ��ַ���ռ�õĿռ�
 pString:�ַ�������ͷָ��ĵ�ַ  
*/
boolean destroyString(String **pString) {
	if (*pString == NULL) {
		return FALSE;
	}
	free((*pString)->str);
	free(*pString);
	*pString = NULL;
	
	return TRUE;
}

/*
 ���ݸ������ַ���������ʼ�ַ���
 pString:�ַ�������ͷָ��ĵ�ַ
 start:�ַ������� 
*/
boolean initString(String **pString, const char *start) {
	int strLen = 0; 
	String *ptr = NULL;
	
	if (*pString != NULL || start == NULL) {
		return FALSE;
	}

	while (start[strLen++]);                                      //����Ŀ�괮���� 
	strLen -= 1;
	ptr = (String*)malloc(sizeof(String));	
	ptr->len = strLen;
	ptr->str = (char*)malloc(sizeof(char)*(strLen+1));            //ģ��C��Ϊ�ַ���������һ���ռ䣬����ʹ�� 
	
	while (strLen >= 0) {
		ptr->str[strLen--] = start[strLen];
	} 
	
	*pString = ptr;
	return TRUE;
}

int main(void) {
	String *str1 = NULL; 
	String *str2 = NULL;
	String *subStr1 = NULL;
	String *str3 = NULL;
	String *str3Old = NULL;
	String *str3New = NULL;
		
	initString(&str1, "abcde");
	initString(&str2, "12345");
	initString(&str3, "abLababab"); 
	initString(&str3Old, "ab");
	initString(&str3New, "X");
	//stringClear(str1);
	
	stringFrontInsert(str1, 4, *str2);
	puts("str1:"); 
	toString(*str1);
	
	stringDelete(str1, 9, 1);
	puts("\nstr1:"); 
	toString(*str1);
	
	subString(str1, &subStr1, 0, 4);
	puts("\nsubStr1:"); 
	toString(*subStr1);
	
	stringCat(subStr1, *str2);
	puts("\nsubStr1:"); 
	toString(*subStr1);
	
	stringCpy(str1, *subStr1); 
	puts("\nstr1:");
	toString(*str1);
	
	puts("\nstr2:");
	toString(*str2);

	printf("\nstr2��str1�е�ƥ��λ��:%d\n", indexOf(*str1, *str2)); 
	
	stringReplace(str3, *str3Old, *str3New, TRUE);
	puts("str3:");
	toString(*str3);
	
	destroyString(&str1); 
	destroyString(&str2); 
	destroyString(&subStr1); 
	destroyString(&str3);
	destroyString(&str3Old);
	destroyString(&str3New);
	return 0;
}