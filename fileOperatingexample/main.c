#include <stdio.h>
#include <stdlib.h>
struct operation{
    int op,d,m,y,h,min;
    char LABEL[100];
};
// file carrier
typedef struct oprs{
    FILE *file;
    struct oprs *next;
}fc;
// normalOPERATIONStop and redoOPERATIONStop
fc *nt=NULL, *rdt=NULL;

// stack using sll making sop
void SOPpush(FILE *fp, fc *top){
    fc *nOP= malloc(sizeof(fc));
    nOP->file=fp;
    nOP->next=NULL;
    if(top==NULL){
        top=nOP;
    }else{
        nOP->next=top;
        top=nOP;
    } 
}

//poping from given sop and pushing to other sop
void pop(fc *c, fc *new){
    fc *tmp1,*tmp2;
    tmp1=c;
    if(tmp1->next!=NULL) c=tmp1->next;
    else c=NULL;
    SOPpush(tmp1->file, new);
}

void undo(){
    int op,d,m,y,th,tm;
    char s[100];
    FILE *ptr = nt->file;
    fscanf(ptr, "%d\n%s\n%d %d %d\n%d %d" ,&op,s,&d,&m,&y,&th,&tm);
    if(op==1){
        
    }
    
}
 
int main()
{
    
    // sprintf(s, "file%d", num*=2);
    
    int num=1,d;
    FILE* ptr = fopen("abcd.txt", "w+");
    char a[100],b[100],c[100];
    fprintf(ptr, "%d\n%s\n%s\n%s", 2012, "We", "are", "in");
    rewind(ptr);
    ptr = fopen("abcd.txt", "r+");
    fscanf(ptr, "%d",&d);
        printf("%d ",d); 
    fscanf(ptr, "\n%s\n%s\n%s", a,b,c);
        printf("%s %s %s",a,b,c); 
    fclose(ptr);
    return 0;
}