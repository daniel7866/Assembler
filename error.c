#include <string.h>
#include "error.h"
#include "input.h"


void fileNotFound(char fileName[]){
    printf("File %s Not Found!\n",fileName);
    errorFlag = 1;
}

void unkownCommand(char command[]){
    printf("Unkown command: '%s' in line %d in file: %s\n",command,lineC,fileName);
    errorFlag = 1;
}

void invalidSyntax(char command[]){
    strtok(command,"\n");
    printf("Invalid syntax: '%s' in line %d in file: %s\n",command,lineC,fileName);
    errorFlag = 1;
}

void invalidSyntaxRegisterName(char registerName[]){
    strtok(registerName,"\n");
    printf("Invalid syntax - register name undefined: '%s' in line %d in file: %s\n",registerName,lineC,fileName);
    errorFlag = 1;
}

void expectedComma(char command[]){
    strtok(command,"\n");
    printf("Expected comma after: '%s' in line %d in file: %s\n",command,lineC,fileName);
    errorFlag = 1;
}
void extraComma(char command[]){
    strtok(command,"\n");
    printf("Extra comma after: '%s' in line %d in file: %s\n",command,lineC,fileName);
    errorFlag = 1;
}

void labelAlreadyDefined(char label[]){
    printf("Label : %s already defined! Cannot duplicate labels, line %d in file: %s\n",label,lineC,fileName);
    errorFlag = 1;
}

void badOperand(){
    printf("Bad operand in line: %d in file: %s\n",lineC,fileName);
    errorFlag = 1;
}

void extraText(char command[]){
    strtok(command, " \t \n");
    printf("Extra text '%s' in line: %d in file: %s\n",command,lineC,fileName);
    errorFlag = 1;
}

void expectedSpace(char command[]){
    strtok(command,"\n");
    printf("Expected white space after label '%s' in line: %d in file: %s\n",command,lineC,fileName);
    errorFlag = 1;
}

void labelUndefined(char label[]){
    printf("Label '%s' in file: %s in line: %d is not defined!\n",label,fileName,lineC);
    errorFlag = 1;
}

void invalidString(char str[]){
    printf("Invalid string: ' %s ' in line: %d must begin and end with \" in file: %s\n",str,lineC,fileName);
    errorFlag = 1;
}

void expectedNumber(char command[]){
    printf("Expected number: '%s' in line: %d in file: %s\n",command,lineC,fileName);
    errorFlag = 1;
}

void invalidLabel(char label[]){
    printf("Label '%s' in line: %d is invalid! in file: %s\n",label,lineC,fileName);
    errorFlag = 1;
}

/*Warnings*/
void redundantLabel(char label[]){
    printf("~warning~Label '%s' in line: %d is redundant and will be ignored! in file: %s\n",label,lineC,fileName);
}
