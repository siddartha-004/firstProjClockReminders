#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int a=5,min,hour,date,month,year;
    time_t currentTime;
    time(&currentTime);
    struct tm *myTime = localtime(&currentTime);
    min=myTime->tm_min ;
    hour=myTime->tm_hour ;
    date=myTime->tm_mday ;
    month= ++myTime->tm_mon ;
    year=myTime->tm_year ;

    
    while(1){
        year++;    month=1;
        while(month<13){
            month++;    date=1;
            while(date<31){
                date++;    hour=0;
                while(hour<24){
                    hour++;    min=0;
                    while(min<60){
        system("clear");
        time(&currentTime);
        myTime = localtime(&currentTime);
        printf("%s\n",ctime(&currentTime));
        sleep(1);
        min++;
    }   }   }   }   }
    return 0;
}

