// This program verifies if, for any given a,b,c,d numbers, (a±b)*(c±d)=24;

#include <stdio.h>
#include <stdlib.h>

void v2(int a, int b, int c, int d){
    int sum1=a+b, sum2=c+d, dif1=a-b, dif2=c-d;
    if(sum1*sum2==24){
        printf("(( %d + %d) * ( %d + %d))\n", a,b,c,d);
        // if (a+b)*(c+d)==24, them print the calculus on the screen;
    }
    else if(dif1*sum2==24){
        printf("(( %d - %d) * ( %d + %d))\n", a,b,c,d);
        // if (a-b)*(c+d)==24, them print the calculus on the screen;
    }
    else if(sum1*dif2==24){
        printf("(( %d + %d) * ( %d - %d))\n", a,b,c,d);
        // if (a+b)*(c-d)==24, them print the calculus on the screen;
    }
    else if(dif1*dif2==24){
        printf("(( %d - %d) * ( %d - %d))\n", a,b,c,d);
        // if (a-b)*(c-d)==24, them print the calculus on the screen;
    }
}
int main(){
    int a,b,c,d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    v2(a,b,c,d);
    return 0;
}
