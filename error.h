#ifndef UNTITLED9_ERROR_H
#define UNTITLED9_ERROR_H

#endif

#include <stdio.h>

/*This file will produce the necessary errors and warnings, and contain an error flag-if it is turned on no .ob .ext .ent files will be created*/

int errorFlag;
extern char fileName[];

void fileNotFound(char[]);
void unkownCommand(char[]);
void invalidSyntax(char[]);
void invalidSyntaxRegisterName(char[]);
void expectedComma(char[]);
void extraComma(char []);
void labelAlreadyDefined(char []);
void badOperand();
void extraText(char []);
void invalidLabel(char label[]);
void expectedSpace(char command[]);
void redundantLabel(char []);
void labelUndefined(char label[]);
void invalidString(char str[]);
void expectedNumber(char command[]);
