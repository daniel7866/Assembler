#ifndef UNTITLED9_INPUT_H
#define UNTITLED9_INPUT_H

#endif

/*This file will read the input files line by line, parsing all labels variables and assembly code, will find errors if there are any*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "error.h"

#define MAXLINE 82
#define MAXLABEL 31
#define MAXFILE 20000
#define MAXFILENAME 80

extern int lineC;
extern int firstScan;
extern int ic,dc;
extern char fileName[MAXFILENAME];
extern char entryString[];
extern char externString[];
extern int exC;

enum varType{source,destination};

void startParsing(char line[]);
int checkLabel(char label[]);
void ignoreWhiteSpaces(char[]);
int validRegister(char *registerName);
int validNumber(char *num);
int validLabel(char[]);
int isLetter(char l);
int isDigit(char n);
void operandParser(char *command, char *ptr, char *var, int varType);
unsigned int convertToDigit(unsigned char c);
void twoOperandsMachineCode(char *v1, char *v2);
void operationWithTwoOperands(char command[]);
void operationWithOneOperand(char command[]);
void operationWithNoOperands(char command[]);
void entryParse(char command[]);
void externParse(char command[]);
void stringParse(char command[]);
void dataParse(char command[]);
int copyToString(char *line,char *string);
