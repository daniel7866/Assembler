#ifndef UNTITLED9_REGISTERS_H
#define UNTITLED9_REGISTERS_H

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*This file will hold strings of the binaty code, add binary code using a mask, and bitfields, and will convert it to base64 and write the .ob .ent .ext files*/

/*operations*/
#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define NOT 4
#define CLR 5
#define LEA 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15

/*code*/
#define NUM 1
#define LABEL 3
#define REGISTER 5
/*A,R,E*/
#define ABSOLUTE 0
#define RELOCATABLE 2
#define EXTERNAL 1



extern int dc, ic;
extern char machineCodeString[];
extern char machineDataString[];
extern char objBinary[];
extern char objBase64[];
extern int exC;
void appendData(int binary, int len);
void appendTocode(int);
void writeObjFile();
void writeExtFile();
void writeEntFile();
void base64();
void convertToBase64(int a, int b);
int myPower(int a, int power);


enum codeType{firstWord,registerWord,numOrLabelWord};

/*For each word of binary code I am using bit-fields*/
struct binaryCode{
    unsigned int source:3;
    unsigned int opcode:4;
    unsigned int destination:3;
    unsigned int are:2;
}firstWordCode;

struct binaryCodeRegister{
    unsigned int source:5;
    unsigned int destination:5;
    unsigned int are:2;
}registerWordCode;

struct binaryCode10{
    unsigned int number:10;
    unsigned int are:2;
}numOrLabelWordCode;
