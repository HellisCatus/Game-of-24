// This program checks if, for any given a,b,c,d numbers, (a±b±c)*d=24 and if a*(b±c±d)=24;

#include <stdio.h>
#include <stdlib.h>

void v1(int a, int b, int c, int d){
    int sum=0;
    if(24%d==0){
        sum=24/d; // we verify if d is a divisor of 24, if so, then sum=24/d;
        if(a+b+c==sum){
            printf("(( %d + %d + %d) * %d)\n", a,b,c,d);
            // if (a+b+c)*d=24, then print the calculus on the screen;
        }
        else if(a+b-c==sum){
            printf("(( %d + %d - %d) * %d)\n", a,b,c,d);
            // if (a+b-c)*d=24, then print the calculus on the screen;
        }
        else if(a-b+c==sum){
            printf("(( %d - %d + %d) * %d)\n", a,b,c,d);
            // if (a-b+c)*d=24, then print the calculus on the screen;
        }
        else if(a-b-c==sum){
            printf("(( %d - %d - %d) * %d)\n", a,b,c,d);
            // if (a-b-c)*d=24, then print the calculus on the screen;
        }
    }
    if(24%a==0){
        sum=24/a; // we verify if a is a divisor of 24, if so, then sum=24/a;
        if(b+c+d==sum){
            printf("( %d * ( %d + %d + %d))\n", a,b,c,d);
            // if a*(b+c+d)=24, then print the calculus on the screen;
        }
        else if(b-c+d==sum){
            printf("( %d * ( %d - %d + %d))\n", a,b,c,d);
            // if a*(b-c+d)=24, then print the calculus on the screen;
        }
        else if(b+c-d==sum){
            printf("( %d * ( %d + %d - %d))\n", a,b,c,d);
            // if a*(b+c-d)=24, then print the calculus on the screen;
        }
        else if(b-c-d==sum){
            printf("( %d * ( %d - %d - %d))\n", a,b,c,d);
            // if a*(b-c-d)=24, then print the calculus on the screen;
        }
    }
}

int main(){
    int a,b,c,d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    v1(a,b,c,d);
    return 0;
}
