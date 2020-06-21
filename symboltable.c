#include "symboltable.h"

typedef struct symbolNode{/*node in the linked list of labels*/
    char labelName[MAXLABEL];
    int address;
    enum Type t;/*Type=could be data or command*/
    int external;/*boolean value= 1 for external and 0 for non external*/
    struct symbolNode *next;
}symbolNode;


typedef struct symbolTable{/*linked list to store all the labels in the assembly code*/
    symbolNode *head;
}symbolTable;

symbolTable symbols;

void addToSymbolTable(char label[],int type, int place){/*arguments are label-name, type=command/data, place=external or internal*/
    symbolNode *ptr = symbols.head;
    symbolNode *node = NULL;
    if(symbols.head ==NULL){
        symbols.head = (symbolNode *)malloc(sizeof(symbolNode));
        symbols.head->next = NULL;
        strcpy(symbols.head->labelName,label);
        if(place == external) {/*if it is external then we put a fake address of zero because the linker will need to calculate its address in memory*/
            symbols.head->external = 1;
            symbols.head->address = 0;
            symbols.head->t = type;
        }
        else/*if it is internal*/
        if(type == data) {
            symbols.head->external = 0;
            symbols.head->t = data;
            symbols.head->address = dc;/*if it is data then the address is data counter*/
        }
        else {
            symbols.head->external = 0;
            symbols.head->t = command;
            symbols.head->address = ic;/*if it is internal then the address is instructions counter*/
        }
    }
    else {/*if head is not a null then go to the end of the list and append the new label there*/
        while (ptr->next != NULL)
            ptr = ptr->next;
        node = (symbolNode *)malloc(sizeof(symbolNode));
        ptr->next = node;
        strcpy(node->labelName,label);
        node->next = NULL;
        if(place == external){
            node->external = 1;
            node->t = type;
            node->address = 0;
            return;
        }
        else
            node->external = 0;
        if(type == data) {
            node->t = data;
            node->address = dc;
        }
        else {
            node->t = command;
            node->address = ic;
        }
    }
}

int findSymbol(char label[]){/*check wheter a symbol is in the list (1 if yes 0 if not)*/
    symbolNode *ptr = symbols.head;
    while(ptr != NULL){
        if(!strcmp(ptr->labelName,label))
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

int getSymbolPlace(char *label){/*return if a label is internal or external*/
    symbolNode *ptr = symbols.head;
    while(ptr){
        if(!strcmp(ptr->labelName,label))
            return ptr->external;
        ptr = ptr->next;
    }
    return 0;
}

int getSymbolAddress(char label[]){
    symbolNode *ptr = symbols.head;
    while(ptr){
        if(!strcmp(ptr->labelName,label))
            return ptr->address;
        ptr = ptr->next;
    }
    return 0;
}

void updateSymbolsAdresses(){/*after the end of the first scan, we need to update the addresses of all the data labels to be after the instructions*/
    symbolNode *ptr = symbols.head;
    while(ptr){
        if(ptr->t == data && ptr->external == 0)/*if it is external we don't care about it's address*/
            ptr->address += ic;
        ptr = ptr->next;
    }
}

void printList(){/*made this function for debugging my code, could be useful*/
    symbolNode *ptr = symbols.head;
    while(ptr){
        printf("%s:%d\n",ptr->labelName,ptr->address);
        ptr = ptr->next;
    }
}

void freeList(){/*after we are done with a file we can clear all the labels from the symbol table and free the memory*/
    symbolNode *node = symbols.head;
    symbolNode *tmp;
    while(node != NULL){
        tmp = node->next;
        free(node);
        node->next = NULL;
        node = tmp;
    }
    symbols.head = NULL;
}
