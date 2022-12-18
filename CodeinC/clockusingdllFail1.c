
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>


int times=0;
void nl()
{
    if(times!=0){
        printf("\n");
    }
    times++;
}

//reminders list
struct node
{
    int dt,dn,mn,yn,Th,Tm;
    char label[100];
    struct node *prev;
    struct node *next;
}*first=NULL, *last;

void push()
{
    int f[4]={1};
    struct node *nn,*place;
    nn =(struct node*)malloc(sizeof(struct node));
    nn->next= NULL;     nn->prev= NULL;
                printf("\n mention the label: "); scanf("%s",nn->label);
                printf("\n date(dd/mm/yyyy) : "); scanf("%d/%d/%d",&nn->dn,&nn->mn,&nn->yn);
                // printf("\n date(dd/mm/yyyy) : "); scanf("%d",&nn->dn);
                printf("\n enter time (hr:min) : "); scanf("%d:%d",&nn->Th,&nn->Tm);
    if(first==NULL){
        first=nn;    last=nn;
    }
    else
    {
        place=first;
        while(            ( place->next!=NULL ) && (nn->yn > place->next->yn)  ) place= place->next;
        while(  ( place->next!=NULL && nn->yn == place->next->yn)  && (nn->mn > place->next->mn)  ) place= place->next;
        while(  ( place->next!=NULL && nn->mn == place->next->mn)  && (nn->dn > place->next->dn)  ) place= place->next;
        while(  ( place->next!=NULL && nn->dn == place->next->dn)  && (nn->Th > place->next->Th)  ) place= place->next;
        while(  ( place->next!=NULL && nn->Th == place->next->Th)  && (nn->Tm > place->next->Tm)  ) place= place->next;
        if( place==first && nn->Tm<place->Tm){
            nn->next=first;
            first->prev=nn;
            first=nn;
        } 
        else{
            nn->next=place->next;
            nn->prev=place;
            place->next=nn;
        }
        
    }
    if(last->next==nn) last=nn;
}
void displayAllReminders()
{
    struct node *tmp=first;
    nl();
    while(tmp!=NULL)
    {
        printf(" %d/%d/%d %d:%d   %s ",tmp->dn,tmp->mn,tmp->yn,tmp->Th,tmp->Tm,tmp->label);
        tmp=tmp->next;
        if(tmp!=NULL){
            printf("\n");
        }
    }
}
void del(struct node *pos)
{
    struct node *tmp=pos, *nn;
    if(tmp==last){
        nn=pos->prev;
        last=nn;
        last->next=NULL;
    }
    else if(tmp==first){
        nn=tmp->next;
        first=nn;
        tmp->next=NULL;
    }
    else{
        (tmp->prev)->next=(tmp->next);
    }
    free(tmp);
}
void src(char S[])
{
    struct node *tmp=first, *lcn[10];
    int count=1, flag=1;
    do{
        if ( strcmp((S),tmp->label)==0 ){
            flag=0;
            printf("\n%d) %s is found at %d/%d/%d %d:%d",count,S,tmp->dn,tmp->mn,tmp->yn,tmp->Th,tmp->Tm);
            lcn[count++]=tmp;
        } 
        tmp=tmp->next;
    }while ( tmp!=last );
    if(flag==1){
        nl();
        printf("No such LABEL: \" %s \" is found among the reminders",S);
    }
    else if(tmp==last){
        int dL=0;
        printf("\n\nEntering any number which is not in the remained serial numbers will terminate this \" option-2 \" \n");
        while(dL<count)
        {
            printf("\nEnter serial number of the reminder to be eliminated : ");   scanf("%d",&dL);
            if(dL<count){
                if(lcn[dL]!=NULL){
                    del(lcn[dL]);
                    printf(" serial number : %d reminder is successfully removed ", dL);
                    lcn[dL]=NULL;
                }
            }
            else{
                printf(" option exited \n");
            }
        }
    }
}
int main()
{
    int Th,Tm,dn,mn,yn,hr,min,e1,o=0;
    long long int i,wait=500000000;
    char SrcLabel[100];
    printf("\n \t\t\t\t\t\t ~Clock follows 24hr format for input~\n"); 
    
    // printf("\nEnter current Clock time \n(INPUT FORMAT) - hr:min  :  ");    scanf("%d:%d",&hr,&min);
    // printf("\nEnter current Clock date(dd/mm/yyyy) : ");                    scanf("%d/%d/%d",&d,&m,&y);
    
    while(o!=9)
    {
    system("clear");   
    printf("Allowed options:\n1.Add reminder label and time \n2.Remove a label from the queue \n3.Check available events for the day\n4.Undo the most recent option\n5.Redo(if possible)\n6.View all events in your calender\n7.Start Clock(this action can't be interpted)\n");
        printf("\n \t\t\t\t\t\t ~Enter a valid Choice: ");        scanf("%d",&o);
        // performing option
            if(o==1){
                push();
                printf("\n\t\t\t\t ~reminder Added~\n"); 
            }
            else if(o==2){
                scanf("%s",SrcLabel);
                src(SrcLabel);
            }
            else if(o==6){
                displayAllReminders();
            }
            else printf("\nINVALID option\n");
           for(i=0; i<wait; i++);
    }
    
    //run clock
    
    
    
    
    
    // clearing malloc data
    struct node *nn,*tmp=first;
    while(tmp!=NULL)
    {
        nn=tmp;
        tmp=tmp->next;
        free(nn);
    }
    
    return 0;
}






