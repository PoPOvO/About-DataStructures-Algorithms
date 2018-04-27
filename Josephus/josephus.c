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
	    
	    pDelete=p->next;               //需要删除的节点为移动节点的下一节点  
	    printf("约瑟夫环出环顺序:%d\n",pDelete->num);  
	    p->next=pDelete->next;         //链表重新连接，去除删除节点  
	    p=pDelete->next;               //链表指针重新移动;  
	    free(pDelete);                 //删除需要出列的节点  
    }  
    printf("约瑟夫环出环顺序:%d\n",p->num);//最后一个出列的链表  
}

void destroyList(Node **head) {
	if (*head == NULL) {
		return;
	}
	
	free(*head);
	*head = NULL;
}

Node* CreateList(int num) {  		//传递参数生成多少个节点  
    Node* node,*pTemp,*Head; 
    int i = 1;
    
    pTemp=(Node*)malloc(sizeof(Node));      //第一个节点单独生成  
    pTemp->num=i;  
    pTemp->next=NULL;  
    Head=pTemp; 
	 
    while(i<num) {  
        node=(Node*)malloc(sizeof(Node));  
        memset(node,0,sizeof(node));  
        node->num=++i;;                 	//节点从1-i,有i个节点  
        node->next=NULL;  
        pTemp->next=node;  
        pTemp=node;       
    }     
    pTemp->next=Head;                      //链表的尾巴连接链表头，形成一个循环链表  
    return Head;  
}  

int main(void) {  
    int num;  
    int count;  
    Node *p = NULL;
    Node *pDelete = NULL;
    
    printf("请输入约瑟夫环的节点数目:");  
    scanf("%d",&num);  

    printf("请输入报数间隔:");   
    scanf("%d",&count);  
 
   	p=CreateList(num);      
	numberOff(p, pDelete, count);
    
	destroyList(&p);      
    return 0;  
} 