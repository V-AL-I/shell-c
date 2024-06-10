#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define NB_OF_BUILTIN 3

typedef struct {
    char* name;
    int size;
} Builtin;


void displayErrorNotFound(char input[SIZE]) {
    printf("%s: command not found\n", input);
}

int checkExit(char input[SIZE]) {
    // returns -1 if input is not exit
    // returns a positive int if input is exit, the int being the exit code displayErrorNotFound
    if (strlen(input) == 6) {
        if (strncmp(input, "exit", 4) == 0) {
            return ((int) input[5]) - 48;
        }
    }
    return -1;

}

int checkEcho(char input[SIZE]) {
    return strncmp(input, "echo", 4) == 0;
}

int checkType(char input[SIZE]) {
    return strncmp(input, "type", 4) == 0;
}

void echo(char input[SIZE]) { 
    input += 5;
    printf("%s\n", input);
}

void type(char input[SIZE], Builtin builtin[NB_OF_BUILTIN]) {
    input += 5;
    for (int i = 0; i < NB_OF_BUILTIN; i++) {
        if (strncmp(builtin[i].name, input, builtin[i].size) == 0) {
            printf("%s is a shell builtin\n", input);
            return;
        }
    }
    printf("%s not found\n", input);
}

int main() {
    Builtin myType = {"type", 4};
    Builtin myEcho = {"echo", 4};
    Builtin myExit = {"exit", 4};

    Builtin builtin[NB_OF_BUILTIN] = {myType, myEcho, myExit};
    
    // Wait for user input
    char input[SIZE];
    while(1) {
        printf("$ ");
        fflush(stdout);

        fgets(input, SIZE, stdin);
        input[strlen(input) - 1] = '\0';
        int exit = checkExit(input);
        if (exit >= 0) {
            return exit;
        }
        else if (checkEcho(input)) {
            echo(input);
        }
        else if (checkType(input)) {
            type(input, builtin);
        }
        else {
            displayErrorNotFound(input);
        }
    }
    
    return 0;
}
