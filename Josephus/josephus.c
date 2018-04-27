#include <stdio.h>  
#include <malloc.h>   
#include <memory.h>

typedef struct Node {  
    int num;
    struct Node *next; 
} Node; 

Node* CreateList(int num); 
void destroyList(Node **head);
void numberOff(Node *p, Node *pDelete, int count);

void numberOff(Node *p, Node *pDelete, int count) {
	int i;
	
    while(p != p->next) {  
	    for(i = 1; i < count-1;i++) {  
	        p=p->next;  
	    }  
	    
	    pDelete=p->next;               //��Ҫɾ���Ľڵ�Ϊ�ƶ��ڵ����һ�ڵ�  
	    printf("Լɪ�򻷳���˳��:%d\n",pDelete->num);  
	    p->next=pDelete->next;         //�����������ӣ�ȥ��ɾ���ڵ�  
	    p=pDelete->next;               //����ָ�������ƶ�;  
	    free(pDelete);                 //ɾ����Ҫ���еĽڵ�  
    }  
    printf("Լɪ�򻷳���˳��:%d\n",p->num);//���һ�����е�����  
}

void destroyList(Node **head) {
	if (*head == NULL) {
		return;
	}
	
	free(*head);
	*head = NULL;
}

Node* CreateList(int num) {  		//���ݲ������ɶ��ٸ��ڵ�  
    Node* node,*pTemp,*Head; 
    int i = 1;
    
    pTemp=(Node*)malloc(sizeof(Node));      //��һ���ڵ㵥������  
    pTemp->num=i;  
    pTemp->next=NULL;  
    Head=pTemp; 
	 
    while(i<num) {  
        node=(Node*)malloc(sizeof(Node));  
        memset(node,0,sizeof(node));  
        node->num=++i;;                 	//�ڵ��1-i,��i���ڵ�  
        node->next=NULL;  
        pTemp->next=node;  
        pTemp=node;       
    }     
    pTemp->next=Head;                      //�����β����������ͷ���γ�һ��ѭ������  
    return Head;  
}  

int main(void) {  
    int num;  
    int count;  
    Node *p = NULL;
    Node *pDelete = NULL;
    
    printf("������Լɪ�򻷵Ľڵ���Ŀ:");  
    scanf("%d",&num);  

    printf("�����뱨�����:");   
    scanf("%d",&count);  
 
   	p=CreateList(num);      
	numberOff(p, pDelete, count);
    
	destroyList(&p);      
    return 0;  
} 