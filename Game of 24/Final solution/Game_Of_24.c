#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int min=-10000, outputCount=0, **formPos, nrLines = -1, *answer;

double calculate(double a, double b, int operation) {
    switch (operation) {
        case 0:
            return a + b;
        case 1:
            return a * b;
        case 2:
            return a - b;
        case 3:
            if(b != 0) {
                return a / b;
            }
            else {
                return min; // If the denominator is null, show the division operation as invalid
            }
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
    return '\0';
}

//The following function prints out expression that equals to 24. The function has the characters, positions of input numbers
void print(int *inNum, const int *pos, int operations, const int *type) {
    int op1 = (operations / 16) % 4; // Extract the first operation
    int op2 = (operations / 4) % 4;  // Extract the second operation
    int op3 = operations % 4;        // Extract the third operation

    if (type[1] == 1) {
        // Type 1 expression: (a#b)#(c#d)=24
        printf("(%d %c %d) %c (%d %c %d) = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    if (type[2] == 1) {
        // Type 2 expression: ((a#b)#c)#d=24
        printf("((%d %c %d) %c %d) %c %d = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    if (type[3] == 1) {
        // Type 3 expression: (a#(b#c))#d=24
        printf("(%d %c (%d %c %d)) %c %d = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    if (type[4] == 1) {
        // Type 4 expression: a#(b#(c#d))=24
        printf("%d %c (%d %c (%d %c %d)) = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
    if (type[5] == 1) {
        // Type 5 expression: a#((b#c)#d)=24
        printf("%d %c ((%d %c %d) %c %d) = 24\n", inNum[pos[0]], getChar(op1), inNum[pos[1]], getChar(op2), inNum[pos[2]], getChar(op3), inNum[pos[3]]);
        outputCount++;
    }
}

int *getResult(int *inNum, const int *pos, int oper) {
    double res1, res2, finalRes;

    // Calculate the first possible result
    int op1 = (oper / 4) % 4;
    int op2 = oper % 4;
    int op3 = (oper / 16) % 4;
    res1 = calculate(inNum[pos[1]], inNum[pos[2]], op1);
    res2 = calculate(res1, inNum[pos[3]], op2);
    finalRes = calculate(inNum[pos[0]], res2, op3);

    if(23.9 < finalRes && finalRes < 24.1) { // Check for possible floating point errors
        finalRes = round(finalRes);
    }

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && finalRes == 24) {
        answer[5] = 1; // Type 5 expression: a#((b#c)#d)=24
    }
    else {
        answer[5] = 0;
    }

    // Calculate the second possible result
    op1 = oper % 4;
    op2 = (oper / 4) % 4;
    op3 = (oper / 16) % 4;
    res1 = calculate(inNum[pos[2]], inNum[pos[3]], op1);
    res2 = calculate(inNum[pos[1]], res1, op2);
    finalRes = calculate(inNum[pos[0]], res2, op3);

    if(23.9 < finalRes && finalRes < 24.1) { // Check for possible floating point errors
        finalRes = round(finalRes);
    }

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && finalRes == 24) {
        answer[4] = 1; // Type 4 expression: a#(b#(c#d))=24
    }
    else {
        answer[4] = 0;
    }

    // Calculate the third possible result
    op1 = (oper / 4) % 4;
    op2 = (oper / 16) % 4;
    op3 = oper % 4;
    res1 = calculate(inNum[pos[1]], inNum[pos[2]], op1);
    res2 = calculate(inNum[pos[0]], res1, op2);
    finalRes = calculate(res2, inNum[pos[3]], op3);

    if(23.9 < finalRes && finalRes < 24.1) { // Check for possible floating point errors
        finalRes = round(finalRes);
    }

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && finalRes == 24) {
        answer[3] = 1; // Type 3 expression: (a#(b#c))#d=24
    }
    else {
        answer[3] = 0;
    }

    // Calculate the fourth possible result
    op1 = (oper / 16) % 4;
    op2 = (oper / 4) % 4;
    op3 = oper % 4;
    res1 = calculate(inNum[pos[0]], inNum[pos[1]], op1);
    res2 = calculate(res1, inNum[pos[2]], op2);
    finalRes = calculate(res2, inNum[pos[3]], op3);

    if(23.9 < finalRes && finalRes < 24.1) { // Check for possible floating point errors
        finalRes = round(finalRes);
    }

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && finalRes == 24) {
        answer[2] = 1; // Type 2 expression: ((a#b)#c)#d=24
    }
    else {
        answer[2] = 0;
    }

    // Calculate the fifth possible result
    op1 = (oper / 16) % 4;
    op2 = oper % 4;
    op3 = (oper / 4) % 4;
    res1 = calculate(inNum[pos[0]], inNum[pos[1]], op1);
    res2 = calculate(inNum[pos[2]], inNum[pos[3]], op2);
    finalRes = calculate(res1, res2, op3);

    if(23.9 < finalRes &&finalRes < 24.1) { // Check for possible floating point errors
        finalRes = round(finalRes);
    }

    // Check if the result is valid and equals 24
    if (res1 != min && res2 != min && finalRes == 24) {
        answer[1] = 1; // Type 1 expression: (a#b)#(c#d)=24
    }
    else {
        answer[1] = 0;
    }

    return answer;
}


// generate all possible operations
void backOp(int *inNum, int *pos) {
    int *type;
    for (int i = 0; i < 64; i++) {
        type = getResult(inNum, pos, i);
        print(inNum, pos, i, type);
    }
}

// checks if the element is already in the position array
int isInNum(const int *pos, int i, int size) {
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
        nrLines++;
        for (int i=0; i<4; i++) {
            formPos[nrLines][i] = inNum[pos[i]];
        }
        int verif;
        for (int j = 0; j < nrLines; j++) {
            verif = 0;
            for (int i = 0; i < 4; i++) {
                if(formPos[j][i] == inNum[pos[i]]) {
                    verif++;
                }
            }
            if(verif == 4) {
                break;
            }
        }
        if(verif != 4) {
            //backtrack how to get the result
            backOp(inNum, pos);
        }
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
    int *inNum, *pos;
    inNum = (int*)malloc(4 *sizeof(int)); // array for input cards
    pos = (int*)calloc(4,sizeof(int)); // array for possible combinations of card positions
    answer = (int*)calloc(6,sizeof(int)); // array for possible types of answers when the order of the numbers and the operations has been determined

    int row;
    // formPos is the matrix used for storing all the permutations of the four input numbers, to make sure that the same permutation is not taken into consideration more than once
    formPos = (int**)calloc(24,sizeof(int*));
    for(row = 0; row < 24; row++) {
        formPos[row] = (int*)calloc(4,sizeof(double));
    }

    // read input cards
    for (int i = 0; i < 4; i++)
        scanf("%d", &inNum[i]);

    // sort the input numbers in ascending order
    for(int i = 0; i < 3; i++) {
        for(int j = i + 1; j < 4; j++) {
            if (inNum[i] > inNum[j]) {
                int aux = inNum[i];
                inNum[i] = inNum[j];
                inNum[j] = aux;
            }
        }
    }

    if (backVal(inNum, pos, 0)==0 && outputCount==0)
        printf("There are no solutions for these cards :(\n");
    else if (outputCount == 1){
        printf("\n%d solution found :)\n", outputCount);
    }
    else{
        printf("\n%d solutions found :)\n", outputCount);
    }

    free(inNum);
    free(pos);
    free(answer);
    for(row = 0; row < 24; row++)
        free(formPos[row]);
    free(formPos);

    return 0;
}
