#include "code.h"
#include "input.h"
#include <stdio.h>

char entryString[MAXFILE];
char externString[MAXFILE];

void appendOpcode(int binary, int len){/*This method adds the binary code with a mask to a string,later on we will convert this string to base64*/
    int mask = 1;
    int i;
    for(i=len-1;i>=0;i--){
        mask = 1<<i;
        if(mask & binary)
            strcat(machineCodeString,"1");
        else
            strcat(machineCodeString,"0");
    }
}

void appendData(int binary, int len){
    int mask = 1;
    int i;
    for(i=len-1;i>=0;i--){
        mask = 1<<i;
        if(mask & binary)
            strcat(machineDataString,"1");
        else
            strcat(machineDataString,"0");
    }
}

void appendTocode(int type){
    switch(type) {
        case firstWord:
            appendOpcode(firstWordCode.source, 3);
            appendOpcode(firstWordCode.opcode, 4);
            appendOpcode(firstWordCode.destination, 3);
            appendOpcode(firstWordCode.are, 2);
            break;
        case registerWord:
            appendOpcode(registerWordCode.source, 5);
            appendOpcode(registerWordCode.destination, 5);
            appendOpcode(registerWordCode.are, 2);
            break;
        case numOrLabelWord:
            appendOpcode(numOrLabelWordCode.number, 10);
            appendOpcode(numOrLabelWordCode.are, 2);
            break;
    }
}

void writeObjFile(){
    char firstLine[MAXLINE];
    char objName[MAXFILENAME] = "";
    FILE *fp;
    sprintf(firstLine,"%d %d\n",ic-100,dc);
    strcat(objBase64,firstLine);
    base64();
    strcat(objName,"./");
    strcat(objName,fileName);
    strcat(objName,".ob");
    fp = fopen(objName,"w");
    if(!fp){
        printf("Sorry could not write obj file\nobjFileName is: %s\n",objName);
        return;
    }
     fprintf(fp,"%s",objBase64);
     if(fp)
     	fclose(fp);
}

void writeExtFile(){
    char extName[MAXFILENAME];
    FILE *fp;
    strcpy(extName,fileName);
    strcat(extName,".ext");
    if(!strcmp(externString,""))
        return;
    fp = fopen(extName,"w");
    if(!fp){
        printf("Sorry could not write ext file\nextFileName is: %s\n",extName);
        return;
    }
    fprintf(fp,"%s",externString);
    if(fp)
     	fclose(fp);
}

void writeEntFile(){
    char entName[MAXFILENAME];
    FILE *fp;
    strcpy(entName,fileName);
    strcat(entName,".ent");
    if(!strcmp(entryString,""))
        return;
    fp = fopen(entName,"w");
    if(!fp){
        printf("Sorry could not write ent file\nentFileName is: %s\n",entName);
        return;
    }
    fprintf(fp,"%s",entryString);
    if(fp)
     	fclose(fp);
}

int myPower(int a, int power){
    int num = a;
    while(power>=2){
        a *= num;
        power--;
    }
    if(power == 0)
        return 1;
    return a;
}

/*The method takes 2 pairs of 6 bits, converts them to decimal, and sends the decimal values to convertToBase64()*/
void base64(){
    char word1[7] = "";
    char word2[7] = "";
    char *ptr = objBinary;
    int a =0, b = 0, power;
    int i;
    int digit;
    while(ptr[0] != '\0'){
        for(i=0;i<6;i++) {
            word1[i] = ptr[0];
            ptr++;
        }
        for(i=0;i<6;i++) {
            word2[i] = ptr[0];
            ptr++;
        }
        for(power = 5,i=0;power>=0;power--,i++){
            digit = convertToDigit(word1[i]);
            a = a + digit * myPower(2, power);
        }
        for(power = 5,i=0;power>=0;power--,i++){
            b += convertToDigit(word2[i]) *(int) myPower(2, power);
        }
        convertToBase64(a,b);
        a=0;
        b=0;
    }
}

void convertToBase64(int a, int b){
    char array[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";/*All base64 symbols in order*/
    char words[4];
    sprintf(words,"%c%c\n",array[a],array[b]);
    strcat(objBase64,words);
}
