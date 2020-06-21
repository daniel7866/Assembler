
#ifndef UNTITLED9_SYMBOLTABLE_H
#define UNTITLED9_SYMBOLTABLE_H

#endif

/*The symbol table will contain all the labels in the assembly code along with their type and address in memory*/

#include <stdlib.h>
#include <string.h>
#include "error.h"
#define MAXLABEL 31

extern int dc, ic;
enum Type{data,command};

enum Place {internal,external};

void addToSymbolTable(char label[],int,int);
int findSymbol(char label[]);
int getSymbolAddress(char label[]);
int getSymbolPlace(char *label);
void updateSymbolsAdresses();
void freeList();

void printList();
