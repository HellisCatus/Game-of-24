#include <stdio.h>
#include <stdlib.h>

int min=-10000, outputCount=0;

float calculate(float a, float b, int operation) {
    if (operation == 3) {
        if (b == 0 /*|| a % b != 0*/) {
            return min; // Division by zero or fractional result, consider it invalid
        }
        return a / b;
    }

    switch (operation) {
        case 0:
            return a + b;
        case 1:
            return a * b;
        case 2:
            return a - b;
    }

    return min; // Invalid operation
}

// This function finds the needed character
char getChar(int operation) {
    switch (operation) {
        case 0:
            return '+';
        case 1:
            return '*';
        case 2:
            return '-';
        case 3:
            return '/';
    }
}

//The following function prints out expression that equals to 24. The function has the characters, positions of input numbers
void print(int* inNum, int* pos, int operations, int type) {
    int op1 = (operations / 16) % 4; // Extract the first operation
    int op2 = (operations / 4) % 4;  // Extract the second operation
    int op3 = operations % 4;        // Extract the third operation

    if (type == 3) {
        // Type 3 expression: (a#(b#c))#d=24
        printf("(%d %c (%d %c %d)) %c %d = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    else if (type == 2) {
        // Type 2 expression: ((a#b)#c)#d=24
        printf("((%d %c %d) %c %d) %c %d = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    else if (type == 1) {
        // Type 1 expression: (a#b)#(c#d)=24
        printf("(%d %c %d) %c (%d %c %d) = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    else if (type == 4) {
        // Type 4 expression: a#(b#(c#d))=24
        printf("%d %c (%d %c (%d %c %d)) = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    else if (type == 5) {
        // Type 5 expression: a#((b#c)#d)=24
        printf("%d %c ((%d %c %d) %c %d) = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
}

int getResult(int* inNum, int* pos, int oper) {
    float res1, res2, res;

    // Calculate the first possible result
    int op1 = (oper / 4) % 4;
    int op2 = oper % 4;
    int op3 = (oper / 16) % 4;
    res1 = calculate(inNum[pos[1]], inNum[pos[2]], op1);
    res2 = calculate(res1, inNum[pos[3]], op2);
    res = calculate(inNum[pos[0]], res2, op3);

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && res == 24) {
        return 5; // Type 5 expression: a#((b#c)#d)=24
    }

    // Calculate the second possible result
    op1 = oper % 4;
    op2 = (oper / 4) % 4;
    op3 = (oper / 16) % 4;
    res1 = calculate(inNum[pos[2]], inNum[pos[3]], op1);
    res2 = calculate(inNum[pos[1]], res1, op2);
    res = calculate(inNum[pos[0]], res2, op3);

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && res == 24) {
        return 4; // Type 4 expression: a#(b#(c#d))=24
    }

    // Calculate the third possible result
    op1 = (oper / 4) % 4;
    op2 = (oper / 16) % 4;
    op3 = oper % 4;
    res1 = calculate(inNum[pos[1]], inNum[pos[2]], op1);
    res2 = calculate(inNum[pos[0]], res1, op2);
    res = calculate(res2, inNum[pos[3]], op3);

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && res == 24) {
        return 3; // Type 3 expression: (a#(b#c))#d=24
    }

    // Calculate the fourth possible result
    op1 = (oper / 16) % 4;
    op2 = (oper / 4) % 4;
    op3 = oper % 4;
    res1 = calculate(inNum[pos[0]], inNum[pos[1]], op1);
    res2 = calculate(res1, inNum[pos[2]], op2);
    res = calculate(res2, inNum[pos[3]], op3);

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && res == 24) {
        return 2; // Type 2 expression: ((a#b)#c)#d=24
    }

    // Calculate the fifth possible result
    op1 = (oper / 16) % 4;
    op2 = oper % 4;
    op3 = (oper / 4) % 4;
    res1 = calculate(inNum[pos[0]], inNum[pos[1]], op1);
    res2 = calculate(inNum[pos[2]], inNum[pos[3]], op2);
    res = calculate(res1, res2, op3);

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && res == 24) {
        return 1; // Type 1 expression: (a#b)#(c#d)=24
    }

    // Return 0 for no valid result
    return 0;
}


// generate all possible operations
void backOp(int* inNum, int* pos) {
    float result;
    for (int i = 0; i < 64; i++) {
        result = getResult(inNum, pos, i);
        if (result==1) {
            print(inNum, pos, i, result);
        }
        if (result==2) {
            print(inNum, pos, i, result);
        }
        if (result==3) {
            print(inNum, pos, i, result);
        }
        if (result==4) {
            print(inNum, pos, i, result);
        }
        if (result==5) {
            print(inNum, pos, i, result);
        }
    }
}

// checks if the element is already in the position array
int isInNum(int* pos, int i, int size) {
    for (int e = 0; e < size; e++) {
        if (pos[e] == i) {
            return 1;
        }
    }
    return 0;
}

// calculate all possible variations of positions for inNum
int backVal(int *inNum, int *pos, int location) {
    int four = 4;
    if (location == 4) {
        //backtrack how to get the result
        backOp(inNum, pos);
    }

    for (int i = 0; i < four; i++) {
        if (isInNum(pos, i, location)==0) {
            // if i is not yet in order we can add it and backtrack the rest of order array
            pos[location] = i;
            if (backVal(inNum, pos, location + 1)==1) { //recursive function
                // there is a solution, keep executing the code
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int *inNum, *pos, four=4;
    inNum = (int*)malloc(four*sizeof(int)); //array for input cards
    pos = (int*)calloc(four,sizeof(int)); //array for possible combinations of card positions

    // read input cards
    for (int i = 0; i < four; i++)
        scanf("%d", &inNum[i]);

    if (backVal(inNum, pos, 0)==0 && outputCount==0)
        printf("There are no solutions for these cards :(\n");

    free(inNum);
    free(pos);

    return 0;
}
