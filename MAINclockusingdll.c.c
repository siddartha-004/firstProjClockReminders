
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int num=1;
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

// file carrier
typedef struct oprs{
    char name[8];
    FILE *file;
    struct oprs *next;
}fc;
// normalOPERATIONStop and redoOPERATIONStop
fc *nt=NULL, *rdt=NULL;



// stack using sll making sop
fc *SOPpush(char s[], fc *top)
{
    fc *nOP;
    nOP= (fc*)malloc(sizeof(fc));
    strcpy(nOP->name,s);
    if(top==NULL)    nOP->next=NULL;
    else    nOP->next=top;
    return nOP; 
}
//poping from given sop and pushing to other sop
void pop(char a)
{
    if(a=='u') {
        rdt= SOPpush(nt->name, rdt);
        if(nt->next!=NULL) nt=nt->next;
        else nt=NULL;
    }
    else {
        nt= SOPpush(rdt->name, nt);
        if(rdt->next!=NULL) rdt=rdt->next;
        else rdt=NULL;
    }
}
void createfile(int d,struct node *nn)
{
    char s[8];
    sprintf(s, "file%d", num++);
    FILE* ptr = fopen(s, "w+");
    fprintf(ptr,"%d\n%s\n%d/%d/%d\n%d:%d",d,nn->label,nn->dn,nn->mn,nn->yn,nn->Th,nn->Tm);
    fclose(ptr);
    nt=SOPpush(s, nt);
}
struct node *push(char S[], int D, int M, int Y, int TH, int TM)
{
    struct node *nn,*place;
    nn =(struct node*)malloc(sizeof(struct node));
    nn->next= NULL;     nn->prev= NULL;
        strcpy(nn->label, S);
        nn->dn =D , nn->mn =M , nn->yn =Y;
        nn->Th =TH , nn->Tm =TM;
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
        if( place==first){
            nn->next=first;
            first->prev=nn;
            first=nn;
        } 
        else{
            nn->next=place->next;
            nn->prev=place;
            if(place->next!=NULL) place->next->prev=nn;
            place->next=nn;
        }
        
    }
    if(last->next==nn) last=nn;
    return nn;
}
void displayAllReminders()
{
    struct node *tmp=first;
    nl();
    while(tmp!=NULL)
    {
        printf(" %02d/%02d/%04d %02d:%02d   %s ",tmp->dn,tmp->mn,tmp->yn,tmp->Th,tmp->Tm,tmp->label);
        tmp=tmp->next;
        if(tmp!=NULL){
            printf("\n");
        }
    }
}
void del(char c,struct node *pos)
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
        (tmp->prev)->next= tmp->next;
        (tmp->next)->prev= tmp->prev;
    }
    if(c=='m')createfile(2,tmp);
    free(tmp);
}
void src(char S[])
{
    struct node *tmp=first, *lcn[10];
    int count=1, flag=1;
    if(tmp==NULL) {
        printf("THERE ARE NO REMINDERS TO LOOK FOR\n");
        return;
    }
    do{
        if ( strcmp((S),tmp->label)==0 ){
            flag=0;
            printf("\n%d) %s IS FOUND AT %02d/%02d/%d %02d:%02d",count,S,tmp->dn,tmp->mn,tmp->yn,tmp->Th,tmp->Tm);
            lcn[count++]=tmp;
        } 
        tmp=tmp->next;
    }while ( tmp!=last );
    if(flag==1){
        nl();
        printf("NO SUCH LABEL: \" %s \" IS FOUND IN YOUR REMINDERS",S);
    }
    else if(tmp==last){
        int dL=0;
        printf("\n\tEnter anyother number to terminate this \" option-2 \"");
        while(dL<count)
        {
            printf("\nEnter serial number of the reminder to be eliminated : ");   scanf("%d",&dL);
            if(dL<count){
                if(lcn[dL]!=NULL){
                    del('m',lcn[dL]);
                    printf("THE REMINDER \"%s\" AT serial number : %d is successfully removed",S,dL);
                    lcn[dL]=NULL;
                }
                else{
                    printf("REMINDER AT THIS SERIAL NUMBER IS ALREADY REMOVED");
                }
            }
            else{
                printf(" option exited \n");
            }
        }
    }
}
void alter(char c)
{
    int OP,D,M,Y,TH,TM,d,m,y,th,tm;
    char S[100],s[100];
    FILE *ptr;
    if(c=='u') ptr = fopen(nt->name,"r+");
    else ptr = fopen(rdt->name,"r+");
    struct node *tmp=first;
    fscanf(ptr, "%d\n%s\n%d/%d/%d\n%d:%d" ,&OP,S,&D,&M,&Y,&TH,&TM);
    fclose(ptr);
    if( (OP==1 && c=='u') || (OP==2 && c=='r') ){
        while(tmp!=NULL){
            strcpy(s,tmp->label);
            d=tmp->dn, m=tmp->mn, y=tmp->yn, th=tmp->Th, tm=tmp->Tm;
            if ( strcmp(S,s)==0 && D==d && M==m && Y==y && TH==th && TM==tm){
                del('n',tmp);
                printf("THE REMINDER \"%s\" IS REMOVED\n",S);
                tmp=NULL;
                break;
            }
        tmp=tmp->next;
        }
    }
    else{
        tmp=push(S,D,M,Y,TH,TM);
        printf("THE REMINDER \"%s\" IS ADDED AGAIN\n",S);
    }
    
    pop(c);
}


int main()
{
    
    int OP,D,M,Y,TH,TM,Th,Tm,d,m,y,sec,o=0;
    char SrcLabel[100],note[100],S[100];
    struct node *p;
    printf("\n \t\t\t\t\t\t ~Clock follows 24hr format for input~\n"); 
    
    printf("Allowed options:\n1.Add reminder label and time \n2.Remove a label from the queue \n3.Undo / Redo(if possible) the most recent option\n5.View all events in your calender\n6.Start Clock(this action can't be interpted)\n");
    
    while(o!=7)
    {
    // system("clear");   
        
        printf(" \t\t\t\t\t\t ~Enter a valid Choice: ");        scanf("%d",&o);
        // performing option
          
            if(o==1)
            {
                printf(" mention the label: "); scanf("%s",note);
                printf(" date(dd/mm/yyyy) : "); scanf("%d/%d/%d",&d,&m,&y);
                printf(" enter time (hr:min) : "); scanf("%d:%d",&Th,&Tm);
                p=push(note,d,m,y,Th,Tm);
                createfile(1,p);
                printf("\t\t\t\t ~reminder Added~\n"); 
            }
            
            else if(o==2){
                printf("Enter search label: "), scanf("%s",SrcLabel);
                src(SrcLabel);
            }
            
            else if(o==3){
                do{
                    printf("Select option:\t3.Undo    4.Redo    5.displayAllReminders\t: "); scanf(" %d",&o);
                    // printf("           %d          \n",o);
                    if(o==3){
                        if(nt==NULL) printf("reminder list is empty\n");
                        else 
                            alter('u');
                    }
                    else if(o==4){
                        if(rdt==NULL) printf("no UNDO operation was performed recently\n");
                        else 
                            alter('r');
                    }
                    else if(o==5){
                        displayAllReminders(); printf("\n");
                    }
                    else{
                        printf("Quitting option\n");
                        break;
                    }
                }while(1);
                fc *nn,*tmp=rdt;
                while(tmp!=NULL)
                {
                    nn=tmp;
                    tmp=tmp->next;
                    remove(nn->name);
                    free(nn);
                }
                rdt = NULL;    
            }
            
            else if(o==5){
                displayAllReminders(); printf("\n");
            }
            
            else if(o>6)printf("\nINVALID option\n");
        //   for(i=0; i<wait; i++);
           
    }

            {
                printf("\nSTARTING CLOCK IN 5 seconds.");
                int a=4;
                while(a--) {
                    sleep(1);
                    printf(".");
                }   
                o=7;
            }    
    //run clock

    
        int min,hour,date,month,year;
        time_t currentTime;
        time(&currentTime);
        struct tm *myTime = localtime(&currentTime);
        sec=myTime->tm_sec ;
        Tm=min=myTime->tm_min ;
        Th=hour=myTime->tm_hour ;
        d=date=myTime->tm_mday ;
        m=month= ++myTime->tm_mon ;
        y=year=myTime->tm_year ;
    
int flag[5]={0};
struct node *nn,*tmp=first;
D=tmp->dn, M=tmp->mn, Y=tmp->yn, TH=tmp->Th, TM=tmp->Tm;

while(tmp->yn<year  && tmp->next!=NULL)                      tmp=tmp->next, flag[0]=1;
if(tmp->next!=NULL  && flag[0]==1) tmp=tmp->next;
while(tmp->mn<month && tmp->yn<=year   && tmp->next!=NULL)   tmp=tmp->next, flag[1]=1;
if(tmp->next!=NULL  && flag[1]==1) tmp=tmp->next;
while(tmp->dn<date  && tmp->mn<=month  && tmp->next!=NULL)   tmp=tmp->next, flag[2]=1;
if(tmp->next!=NULL  && flag[2]==1) tmp=tmp->next;
while(tmp->Th<hour  && tmp->dn<=date   && tmp->next!=NULL)   tmp=tmp->next, flag[3]=1;
if(tmp->next!=NULL  && flag[3]==1) tmp=tmp->next;
while(tmp->Tm<min   && tmp->Th<=hour   && tmp->next!=NULL)   tmp=tmp->next, flag[4]=1;
if(tmp->next!=NULL  && flag[4]==1) tmp=tmp->next;
else if(tmp==NULL) 
    goto finish;
myTime = localtime(&currentTime);
        sec=myTime->tm_sec ;
        Tm=myTime->tm_min ;
        Th=myTime->tm_hour ;
        d=myTime->tm_mday ;
        m= ++myTime->tm_mon ;
        y=myTime->tm_year ;
        y+=1900;
set:
    D=tmp->dn, M=tmp->mn, Y=tmp->yn, TH=tmp->Th, TM=tmp->Tm;
    strcpy(S,tmp->label);
    // printf(" %d/%d/%d %d:%d   %s\n" ,d,m,y,Th,Tm,S);
    // printf(" %d/%d/%d %d:%d   %s\n" ,tmp->dn,tmp->mn,tmp->yn,tmp->Th,tmp->Tm,tmp->label);
        
        while(1){
            while(m<13){
                while(d<31){
                    while(Th<24){
                        while(Tm<60){
                              while(sec<60)
                                {
                system("clear");
                // printf(" %d/%d/%d %d:%d   %s\n" ,d,m,y,Th,Tm,S);
                time(&currentTime);
                myTime = localtime(&currentTime);
                printf("%s\n",ctime(&currentTime));
                
                sec++;
                if (( d==D && m==M && y==Y && Th==TH && Tm==TM)){
                    printf("TIME FOR \"%s\"\n",S);
                    if(Tm==59){
                        tmp=tmp->next;
                        if(tmp==NULL){
                            goto finish;
                        }
                        goto set;
                    } 
                }
                sleep(1);    
            
                                } 
                            ++Tm;   sec=1;  } 
                        Th++;    Tm=1;  } 
                    d++;    Th=0;  }
                m++;    d=1;   }
            y++;    m=1;   }
    


    
    
finish:    
// clearing malloc data of reminders
    tmp=first;
    while(tmp!=NULL)
    {
        nn=tmp;
        tmp=tmp->next;
        free(nn);
    }
// clearing malloc data of reminders
    fc *n,*temp=nt;
    while(temp!=NULL)
    {
        n=temp;
        temp=temp->next;
        remove(n->name);
        free(n);
    }
    nt = NULL;   
    return 0;
}







