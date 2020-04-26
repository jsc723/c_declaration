#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
S   -> int E
E   -> (E)
    -> *E
    -> E([S,]...)
    -> E[N]
    -> literal
N   -> [0-9]+
*/
const int N  = 64;
int nextToken(const char *exp, int begin);
char **tokenlize(const char *statement);
int isAzaz(const char c) {
    return (c >= 'A' && c <= 'Z') || (c>='a' && c<='z') || (c=='_');
}
int isNum(const char c) {
    return c>='0'&&c<='9';
}
int isSpace(const char c) {
    return c == ' ';
}
void parseStatement(char **tokens, int begin, int end);
void parseExpression(char **tokens, int begin, int end);
void printTokens(char **tokens, int begin, int end);
int isStarExp(char **tokens, int begin, int end);
int isArrayExp(char **tokens, int begin, int end, int *info);
int isFuncExp(char **tokens, int begin, int end, int *info);
int isParaExp(char **tokens, int begin, int end);
int isIdExp(char **tokens, int begin, int end);
int prevPara(char **tokens, int begin, int start, const char *p);

int main(int argc, char *argv[]) {
    char *input = "int (*(*vtable)[])(int (*p)(int, int *))";
    printf("input: %s\n", input);
    char **tokens = tokenlize(input);
    int i = 0;
    //printf("tokenlize: ");
    while(tokens[i]) {
        //printf("<%s> ", tokens[i]);
        ++i;
    }
    //printf("\n");
    parseStatement(tokens, 0, i);
    printf("\n");
    return 0;
}
char **tokenlize(const char *statement) {
    char **p = (char **) calloc(N, sizeof(char *));
    int i = 0, j = 0;
    while(statement[i]){
        int next_i = nextToken(statement, i);
        if(!isSpace(statement[i])) {
            int n = sizeof(char) * (next_i - i);
            p[j] = (char *) calloc(1, n + 1);
            strncpy(p[j], statement + i, n);
            ++j;
        }
        i = next_i;
    }
    return p;
}
/*Return the start index of the next token.*/
int nextToken(const char *exp, int begin) {
    int i = begin;
    if(exp[i] != '\0') {
        if(isAzaz(exp[i])) {
            ++i;
            while(isAzaz(exp[i]) || isNum(exp[i])) {
                ++i;
            }
        } else if (isNum(exp[i])) {
            while(isNum(exp[++i]));
        } else if (isSpace(exp[i])) {
            while(isSpace(exp[++i]));
        } else {
            ++i;
        }
    }
    return i;
}
void printTokens(char **tokens, int begin, int end) {
    int i;
    for(i = begin; i != end; i++)
        printf("%s ", tokens[i]);
}
void parseStatement(char **tokens, int begin, int end) {
    parseExpression(tokens, begin + 1, end);
    //printTokens(tokens, begin + 1, end);
    printf(" %s\n", tokens[begin]);
}
void parseExpression(char **tokens, int begin, int end) {
    int info;
    if(isStarExp(tokens, begin, end)) {
        parseExpression(tokens, begin + 1, end);
        //printTokens(tokens, begin + 1, end);
        printf(" a pointer to");
    } else if (isArrayExp(tokens, begin, end, &info)) {
        parseExpression(tokens, begin, info);
        //printTokens(tokens, begin, info);
        printf(" an array of");
    } else if (isFuncExp(tokens, begin, end, &info)) {
        parseExpression(tokens, begin, info);
        //printTokens(tokens, begin, info);
        printf(" a function taking ( ");
        printTokens(tokens, info + 1, end - 1);
        printf(") and returning");
    } else if (isParaExp(tokens, begin, end)) {
        parseExpression(tokens, begin + 1, end - 1);
    } else if (isIdExp(tokens, begin, end)) {
        printTokens(tokens, begin, end);
        printf("is");
    }
     else {
        printTokens(tokens, begin, end);
        printf(" is malformed.\n");
        exit(1);
    }
}

int isStarExp(char **tokens, int begin, int end) {
    return  strcmp(tokens[begin], "*") == 0;
}
int isArrayExp(char **tokens, int begin, int end, int *info) {
    int prev = prevPara(tokens, begin, end - 1, "]");
    if(prev == -1 || prev == begin)
        return 0;
    *info = prev;
    return 1;
}
int isFuncExp(char **tokens, int begin, int end, int *info) {
    int prev = prevPara(tokens, begin, end - 1, ")");
    if(prev == -1 || prev == begin)
        return 0;
    *info = prev;
    return 1;
}
int isParaExp(char **tokens, int begin, int end) {
    int prev = prevPara(tokens, begin, end - 1, ")");
    return prev == begin;
}
int isIdExp(char **tokens, int begin, int end) {
    if(begin + 1 == end) {
        if(isAzaz(tokens[begin][0]) && strcmp(tokens[begin], "int") != 0)
            return 1;
    }
    return 0;
}

/*
    Return the index of the matching previous parathesis of the one at tokens[start] in range [begin, start)
    if not found, return -1.
*/
int prevPara(char **tokens, int begin, int start, const char *p) {
    if(begin >= start || strcmp(tokens[start], p) != 0)
        return -1;
    int i = start;
    const char *target = (strcmp(p, ")") == 0 ? "(" : "[");
    int count = 1;
    while(i >= begin && count > 0) {
        --i;
        if(strcmp(tokens[i], target) == 0)
            count--;
        else if(strcmp(tokens[i], p) == 0)
            count++;
    }
    if(i >= begin)
        return i;
    return -1;
}
