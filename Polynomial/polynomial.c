#include <stdio.h>
#include <math.h>
#include <string.h>

//�������ʽ��һ�� 
typedef struct {
	double coefficient;   //ϵ�� 
	int index;            //ָ�� 
} Item, USER_TYPE;

#include "oneWayLinkedList.h"

static boolean first = FALSE;  

boolean inputItem(Item *item); 
void printOneItem(Item item); 
boolean comparaTo(Item one, Item two);
void  polynomialAddition(LinkedList aPoly, LinkedList bPoly, LinkedList *result);

/*
 ����ʽ���
 aPoly��bPoly: ����ӵ�Ŀ�����ʽ 
 *result:�������ʽ 
*/ 
void  polynomialAddition(LinkedList aPoly, LinkedList bPoly, LinkedList *result) {
	Item copiedItem, comparaedItem;
	LinkedList copiedPoly, comparaedPoly;
	int copiedPolyLen;                                         //copiedPoly�ĳ��� 
	int comparaedPolyLen;                                      //comparaedPoly�ĳ��� 
	int copiedIndex = 0;                                       //copidedIndex��������Ŀ��������±� 
	int comparaedIndex = 0;                                    //comparaedIndexָʾ���Ƚϵ�Ŀ��������±�          
	int resultIndex = 0;                                       //resultIndexָʾ����������һ��������޸�λ�� 
	
	bubbleSortList(aPoly, TRUE, comparaTo);                    //�ȶ�Ŀ�����ʽ���� 
	bubbleSortList(bPoly, TRUE, comparaTo);	
	copiedPoly = (getLength(aPoly) > getLength(bPoly) ? aPoly : bPoly);     //ѡ�������ӵ���������ʽ�������ϳ��� 
	comparaedPoly = (copiedPoly == aPoly ? bPoly : aPoly);
	copiedPolyLen = getLength(copiedPoly);
	comparaedPolyLen = getLength(comparaedPoly);
	linkedListCopy(copiedPoly, result);                         //�������Ŀ��������Ϊ�������
	
	while (copiedIndex < copiedPolyLen && comparaedIndex < comparaedPolyLen) {
		getValueByIndex(copiedPoly, &copiedItem, copiedIndex);	
		getValueByIndex(comparaedPoly, &comparaedItem, comparaedIndex);
		
		if (copiedItem.index > comparaedItem.index) {
			insertNode(result, comparaedItem, resultIndex);
			comparaedIndex++;
		} else if (copiedItem.index < comparaedItem.index) {
			copiedIndex++;
		} else if (copiedItem.index == comparaedItem.index) {
			copiedItem.coefficient += comparaedItem.coefficient;		
			modifyNodeByIndex(*result, copiedItem, resultIndex);
			copiedIndex++;
			comparaedIndex++;
		}
		resultIndex++;
	}

	while (comparaedIndex < comparaedPolyLen) {                 //����comparaedPolyLen�����ָ������copiedPoly������ָ������� 
		getValueByIndex(comparaedPoly, &comparaedItem, comparaedIndex);
		appendValue(*result, comparaedItem);
		comparaedIndex++;
	}	
}

boolean comparaTo(Item one, Item two) {
	return one.index > two.index;
}

void printOneItem(Item item) {		
	if (first == TRUE) {                                   //��Ϊ��һ��Ϊ������+�ţ��ֿ����� 
		puts("����ʽ����:"); 
		if (fabs(item.coefficient+1) < 1e-6) {             //ϵ��Ϊ-1
	 		printf("%s", "-");
		} else if (fabs(item.coefficient-1) > 1e-6) {      //ϵ����Ϊ1 
			printf("%.2lf", item.coefficient);
		}    
	}
	
	if (first == FALSE) {
		if (item.coefficient > 1e-6) {                      //����������+�� 
			printf("%c", '+');
		}
		if (fabs(item.coefficient+1) < 1e-6) {              //ϵ��Ϊ-1 
			printf("%c", '-');
		} else if (fabs(item.coefficient-1) > 1e-6) {   	//ϵ����Ϊ1
			printf("%.2lf", item.coefficient);
		}	
	}

	if (item.index == 1) {  					            //���ָ�� 
		printf("%c", 'x');
 	} else if (item.index != 0) {
		printf("%c^%d", 'x', item.index);
	}
	first = FALSE;
}

boolean inputItem(Item *item) {
	printf("����һ��,��(3.14(ϵ��), 1(ָ��)),Ctrl+Z����ϵ��Ϊ0����:");
	return 2 == scanf("%lf%d", &(item->coefficient), &(item->index)) && fabs(item->coefficient) > 1e-6;
}

//-1 -1 -1 7 5 0
int main(void) {
	LinkedList poly1 = NULL;
	LinkedList poly2 = NULL;
	LinkedList result = NULL;
	
	first = TRUE;
	printf("\n%s\n", "--------------����ʽ1--------------");
	initLinkedList(&poly1, inputItem);
	iterator(poly1, printOneItem);

	first = TRUE;
	printf("\n%s\n", "--------------����ʽ2--------------");
	initLinkedList(&poly2, inputItem);
	iterator(poly2, printOneItem);

	first = TRUE; 
	printf("\n%s\n", "--------------��ӽ��-------------");
	polynomialAddition(poly1, poly2, &result);
	iterator(result, printOneItem);
	
	destoryLinkedList(&result);
	destoryLinkedList(&poly2);
	destoryLinkedList(&poly1);
	return 0;
}