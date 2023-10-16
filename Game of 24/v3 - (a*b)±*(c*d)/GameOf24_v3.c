// This program checks if, for any given a,b,c,d numbers, (a*b)±*(b*c)=24;

#include <stdio.h>
#include <stdlib.h>

void v3(int a, int b, int c, int d){
    int prod1=a*b, prod2=c*d;
    if(prod1+prod2==24){
        printf("(( %d * %d) + ( %d * %d))\n", a,b,c,d);
        // if (a*b)+(c*d)=24, then print the calculus on the screen;
    }
    if(prod1-prod2==24){
        printf("(( %d * %d) - ( %d * %d))\n", a,b,c,d);
        // if (a*b)-(c*d)=24, then print the calculus on the screen;
    }
    if(prod1*prod2==24){
        printf("( %d * %d * %d * %d)\n", a,b,c,d);
        // if (a*b)*(c+d)=24, then print the calculus on the screen;
    }
}
int main(){
    int a,b,c,d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    v3(a,b,c,d);
    return 0;
}
