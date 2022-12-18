/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int num=1;
    char s[8];
    while(num<35){
    sprintf(s, "file%d", num);
    printf("%s\t",s);
    num*=2;
    FILE* ptr = fopen(s, "w+");
    }
    return 0;
}

