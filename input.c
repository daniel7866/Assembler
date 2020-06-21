#include "input.h"
#include "code.h"

void startParsing(char line[]) {/*This is the function that recognizes commands ,labels and data*/
    char copy[MAXLINE];/*In many functions here I will make a copy of my lines, since strtok changes the string and I want to hold the original too*/
    int labelLength = 0;
    int addLabel = 0;/*flag for indication if there is a label we need to add*/
    char label[MAXLABEL];
    char *copyPtr, *linePtr;
    ignoreWhiteSpaces(line);/*skip all the white spaces(tabs and spaces)*/
    if (line[0] == '\n' || line[0] == ';' || line[0] == '\0')
        return;/*if it is an empty line or a comment, ignore it and go to the next line in the file*/
    strcpy(copy, line);
    if (checkLabel(copy)) {/*if there is a label definition at the beggining of the line*/
        strcpy(label, copy);
        strtok(label, ":");/*label ends with :*/
        addLabel = 1;/*turns the flag on*/
        if (firstScan && findSymbol(label)) {
            labelAlreadyDefined(label);
            addLabel = 0;
            return;
        }
        if(!validLabel(label)){/*if the label is not valid the method that checks it throws an error*/
            addLabel = 0;
            return;
        }
        labelLength = strlen(label) + 1;/*The length we need to skip, the length of the label + 1 for :    */
    }
    if (firstScan == 0)
        addLabel = 0;/*if it is the second pass on the code, all the symbols are already included*/
    strcpy(copy, line + labelLength);/*skip the label to the next word, recognize what command it is*/
    line += labelLength;
    if (addLabel && line[0] != ' ' && line[0] != '\t') {/*A space must be after a label*/
        expectedSpace(line);
        return;
    }
    copyPtr = copy;
    linePtr = line;
    while(*copyPtr == ' ' || *copyPtr == '\t')
        copyPtr++;
    while(*linePtr == ' ' || *linePtr== '\t')
        linePtr++;
    strtok(copyPtr, " \t\n");
    /*Commands with two operands*/
    if (!strcmp(copyPtr, "mov")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);/*If the flag is on we need to add the label: it is a command and internal(inside this file)*/
        firstWordCode.opcode = MOV;/*set the bits of the opcode using bit-fields*/
        if (firstScan)/*in the first scan we are counting how many instructions there are*/
            ic++;
        else/*in the second scan we are scanning how many instructions/data there are for the external label file*/
            exC++;
        operationWithTwoOperands(linePtr + 4);/*+4 to skip the MOV command*/
    } else if (!strcmp(copyPtr, "cmp")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = CMP;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithTwoOperands(linePtr + 4);
    } else if (!strcmp(copyPtr, "add")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = ADD;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithTwoOperands(linePtr + 4);
    } else if (!strcmp(copyPtr, "sub")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = SUB;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithTwoOperands(linePtr + 4);
    } else if (!strcmp(copyPtr, "lea")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = LEA;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithTwoOperands(linePtr + 4);
        /*commands with one operand*/
    } else if (!strcmp(copyPtr, "not")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = NOT;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "clr")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = CLR;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "inc")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = INC;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "dec")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = DEC;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "jmp")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = JMP;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "bne")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = BNE;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "red")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = RED;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "prn")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = PRN;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
    } else if (!strcmp(copyPtr, "jsr")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = JSR;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithOneOperand(linePtr + 4);
        /*commands with no operands*/
    } else if (!strcmp(copyPtr, "rts")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = RTS;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithNoOperands(linePtr + 5);
    } else if (!strcmp(copyPtr, "stop")) {
        if (addLabel)
            addToSymbolTable(label, command, internal);
        firstWordCode.opcode = STOP;
        if (firstScan)
            ic++;
        else
            exC++;
        operationWithNoOperands(linePtr + 5);
        /*data*/
    } else if (!strcmp(copyPtr, ".data")) {
        if (addLabel)
            addToSymbolTable(label, data, internal);
        dataParse(linePtr + 6);
    } else if (!strcmp(copyPtr, ".string")) {
        if (addLabel)
            addToSymbolTable(label, data, internal);
        stringParse(linePtr + 8);
    } else if (!strcmp(copyPtr, ".entry")) {
        if (addLabel)
            redundantLabel(label);/*Warning about redundant label*/
        entryParse(linePtr + 7);
    } else if (!strcmp(copyPtr, ".extern")) {
        if (addLabel)
            redundantLabel(label);/*Warning about redundant label*/
         externParse(linePtr + 8);
    } else {
        unkownCommand(copy);
    }
}

/*.data parser*/
/*data can have unlimited numbers, so there are two flags:
 * expectComma and expect number
 * at first we are expecting a number, after a number we are expecting a comma, or the end of the line so it is ok to reach end of line with the comma flag on*/
void dataParse(char command[]){
    char copy[MAXLINE];
    int num;
    int expectComma = 0;
    int expectNumber = 1;
    char *ptr;
    char *commandptr = command;
    strcpy(copy,command);
    ptr = copy;

    while(*ptr) {
        ignoreWhiteSpaces(ptr);
        ignoreWhiteSpaces(commandptr);
        strtok(ptr, " \t,");
        if(ptr[0] == '\n')
            return;
        if(expectComma && ptr[0] != ','){
            expectedComma(command);
            return;
        }
        if(expectNumber && (!isDigit(ptr[0]) && ptr[0] != '+' && ptr[0] != '-')){
            expectedNumber(command);
            return;
        }
        if(expectComma) {
            expectComma = 0;
            expectNumber = 1;/*After a comma there must be a number*/
            ptr++;
            commandptr++;
        }else
        if(expectNumber) {
            expectComma = 1;/*After a number there must be a comma(or end of line)*/
            expectNumber = 0;
            num = atoi(ptr);
            if(!firstScan) {
                appendData(num,12);
                /*strcat(machineCodeString, "\n");*/
            }
            commandptr += strlen(ptr);
            strcpy(copy,commandptr);
            ptr = copy;
            if(firstScan)
                dc++;
        }
    }

}

/*handels .string*/
void stringParse(char command[]){
    char copy[MAXLINE];
    char *ptr;
    char *commandPtr;
    char string[MAXLABEL];
    strcpy(copy, command);
    ptr = copy;

    ignoreWhiteSpaces(ptr);
    ignoreWhiteSpaces(copy);
    ignoreWhiteSpaces(command);
    strtok(ptr,"\n");
    if(!copyToString(ptr,string))
    	return;
    commandPtr = command+strlen(string);
    ignoreWhiteSpaces(commandPtr);
    if(*commandPtr != '\n' && *commandPtr != '\0'){
        extraText(commandPtr);
        return;
    }
    ptr = string+1;/*point past the " */
    if(firstScan) {
        while (*(ptr + 1)) {/*insures that we get all the characters except the double quotes at the end*/
            appendData((unsigned int) *ptr,12);/*Add the ascii code of the character to the machine code*/
            ptr++;
        }

        appendData(0, 12);/*add null character at the end of the string*/
        dc += strlen(string)-1;/*increase data counter by number of characters in the string + 1 for null character -2 because of the two double quotes*/
    }
}

void entryParse(char command[]) {
    char copy[MAXLINE];
    char *ptr;
    char label[MAXLABEL];
    char stringToApped[MAXLINE];
    strcpy(copy, command);
    ptr = copy;

    ignoreWhiteSpaces(ptr);
    ignoreWhiteSpaces(copy);
    ignoreWhiteSpaces(command);
    strtok(ptr, " \t\n");
    strcpy(label,ptr);
    if (!firstScan && !findSymbol(ptr)) {
        labelUndefined(ptr);
        return;
    }

    if (!firstScan && getSymbolPlace(ptr) == external) {/*.entry is for internal labels only..*/
        labelAlreadyDefined(ptr);
        return;
    }

    ptr = command + strlen(ptr);
    ignoreWhiteSpaces(ptr);

    if (*ptr != '\n' && *ptr != '\0') {
        extraText(ptr);
        return;
    }

    /*Add to entry file*/
    if(!firstScan){
        sprintf(stringToApped,"%s:\t%d\n",label,getSymbolAddress(label));
        strcat(entryString,stringToApped);
    }
}

void externParse(char command[]) {
    char copy[MAXLINE];
    char *ptr;
    char label[MAXLABEL];
    strcpy(copy, command);
    ptr = copy;

    ignoreWhiteSpaces(ptr);
    ignoreWhiteSpaces(copy);
    ignoreWhiteSpaces(command);
    strtok(ptr, " \t\n");
    strcpy(label,ptr);
    ptr = command + strlen(ptr);
    ignoreWhiteSpaces(ptr);
	
    if (*ptr != '\n' && *ptr != '\0') {/*check that there is no garbage after the command*/
        extraText(ptr);
        return;
    }
    if(firstScan && validLabel(label)){
        if(!findSymbol(label))/*if label is not defined already*/
            addToSymbolTable(label,data,external);
            else
                labelAlreadyDefined(label);
    }
}

void operationWithNoOperands(char command[]) {
    char *ptr = command;
    ignoreWhiteSpaces(ptr);
    if (*ptr != '\n' && *ptr != '\0') {/*check that there is no extra text after the command*/
        extraText(command);
        return;
    }

    if(!firstScan) {
        firstWordCode.are = ABSOLUTE;
        firstWordCode.source = 0;/*no operands*/
        firstWordCode.destination = 0;/*no operands*/
        appendTocode(firstWord);
    }
}

void operationWithOneOperand(char command[]) {
    char copy[MAXLINE];
    char *ptr;
    char v1[MAXLABEL];
    char exStringToAppend[MAXLINE];

    ignoreWhiteSpaces(command);
    strcpy(copy, command);
    ptr = copy;
    firstWordCode.source = 0;/*There is no source operand*/
    operandParser(copy, ptr, v1, destination);/*This will set the operand to v1, destination because there is only one operand*/
    ptr = copy + strlen(v1);
    ignoreWhiteSpaces(ptr);
    if (*ptr != '\n' && *ptr != '\0') {
        extraText(copy);
        return;
    }
    if (isLetter(v1[0])) {/*if it is a label*/
        if (!firstScan) {
            if (!findSymbol(v1)) {/*if it is the second scan and we can't find it it was not defined*/
                labelUndefined(v1);
                return;
            }
        }
        numOrLabelWordCode.number = getSymbolAddress(v1);
        if(getSymbolPlace(v1) == external){
            numOrLabelWordCode.are = EXTERNAL;/*external*/
            if(!firstScan) {
                sprintf(exStringToAppend, "%s:\t%d\n", v1, exC);
                strcat(externString, exStringToAppend);
            }
        }
        else
            numOrLabelWordCode.are = RELOCATABLE;/*relocatable*/
    }

    else if (validNumber(v1) && firstWordCode.opcode != PRN) {/*if it is a number- only prn(from one operand opcodes) can have a number as a destination operand*/
        badOperand();
        return;
    } else if(validNumber(v1)){/*if it is prn and number*/
        numOrLabelWordCode.number = atoi(v1);
        numOrLabelWordCode.are = ABSOLUTE;
    } else{/*if it's a register*/
        numOrLabelWordCode.number = convertToDigit(v1[2]);
        numOrLabelWordCode.are = ABSOLUTE;/*absolute*/
    }
    if(!firstScan)
        exC++;

    if (firstScan)
        ic++;
    else {/*we are writing the machine code only in the second scan of the file*/
        appendTocode(firstWord);
        appendTocode(numOrLabelWord);
    }
}

void operandParser(char *command, char *ptr, char *var, int varType) {
    char copy[MAXLINE];
    strcpy(copy, command);
    ptr = copy;
    ignoreWhiteSpaces(ptr);
    strtok(copy, " ,\t\n");
    if (ptr[0] == ',') {
        extraComma(command);
        return;
    }

    strcpy(var, ptr);
    if (var[0] == '@') {
        if (!validRegister(var)) {
            invalidSyntaxRegisterName(var);
            return;
        }
        if (varType == source)
            firstWordCode.source = REGISTER;
        else if (varType == destination)
            firstWordCode.destination = REGISTER;
    } else {
        if (isLetter(var[0])) { /*if it's a label*/

            if (!validLabel(var)) {
                /*prompt on invalid labelname*/
                return;
            }
            if (varType == source)
                firstWordCode.source = LABEL;
            else if (varType == destination)
                firstWordCode.destination = LABEL;
        } else {/*if it's a number*/
            if (!validNumber(var)) {
                /*Prompt on invalid number*/
                return;
            } else if (varType == source)
                firstWordCode.source = NUM;
            else if (varType == destination)
                firstWordCode.destination = NUM;
        }
    }
}

void operationWithTwoOperands(char command[]) {
    char copy[MAXLINE];
    char *ptr, *ptr2;
    char v1[MAXLABEL];
    char v2[MAXLABEL];
    ignoreWhiteSpaces(command);
    strcpy(copy, command);
    ptr = copy;
    operandParser(copy, ptr, v1, source);
    /*Finished with the first operand*/
    ptr = copy + strlen(v1);
    ignoreWhiteSpaces(ptr);
    /*now expecting a comma*/
    if (ptr[0] != ',') {
        expectedComma(command);
        return;
    }

    ptr++;
    ignoreWhiteSpaces(ptr);/*after a comma there might be white spaces*/
    ptr2 = ptr;
    strcpy(copy, ptr2);
    ptr2 = copy;
    ptr = copy;
    operandParser(copy, ptr2, v2, destination);
    ptr += strlen(v2);/*find out if there is extra text after the command*/
    ignoreWhiteSpaces(ptr);
    if (*ptr == '\n')
        ptr++;
    if (*ptr) {
        extraText(ptr);
        return;
    }
    firstWordCode.are = ABSOLUTE;

    twoOperandsMachineCode(v1, v2);/*This function will write the necessary binary code*/
}


void ignoreWhiteSpaces(char line[]) {/*a simple method to skip white spaces*/
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    strcpy(line, line + i);
}

int validRegister(char *registerName) {/*check if a register is valid*/
    if (registerName[1] != 'r') {
        return 0;
    } else {
        switch (registerName[2]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                return 1;
            default:
                return 0;
        }
    }
}

/*Check if a number is valid*/
int validNumber(char *num) {
    char *ptr;
    if (num[0] == '\0')
        return 0;
    ptr = num;
    if (*ptr == '-' || *ptr == '+')
        ptr = num + 1;

    while (*ptr != '\0') {
        if (*ptr < '0' || *ptr > '9')
            return 0;
        ptr++;
    }
    return 1;
}

/*Checks that the word is supposed to be a label->does not make sure that it's valid YET*/
int checkLabel(char line[]) {
    char label[MAXLINE];
    strcpy(label, line);
    strtok(label, ":");
    if (!strcmp(label, line))
        return 0;/*No label*/
    else
        return 1;
}
/*makes sure that the label is valid*/
int validLabel(char label[]) {
    char *ptr = label;
    if (validRegister(label) && strlen(label) == 2) {/*if it is a register name*/
        invalidLabel(label);
        return 0;
    }
    /*if it is an operation name*/
    if (!strcmp(label, "mov") || !strcmp(label, "cmp") || !strcmp(label, "add") || !strcmp(label, "sub") ||
        !strcmp(label, "not") || !strcmp(label, "clr") || !strcmp(label, "lea") || !strcmp(label, "inc")
        || !strcmp(label, "dec") || !strcmp(label, "jmp") || !strcmp(label, "bne") || !strcmp(label, "red") ||
        !strcmp(label, "prn") || !strcmp(label, "jsr") || !strcmp(label, "rts") || !strcmp(label, "stop")) {
        invalidLabel(label);
        return 0;
    }
    if (!isLetter(ptr[0])) {/*First character must be a letter*/
        invalidLabel(label);
        return 0;
    }
    while (*ptr != '\0') {
        if (!isDigit(ptr[0]) && !isLetter(ptr[0])) {/*if it is not a number and not a letter*/
            invalidLabel(label);
            return 0;
        }
        ptr++;
    }
    if (strlen(label) > MAXLABEL) {/*if it is too long*/
        invalidLabel(label);
        return 0;
    }

    return 1;
}

/*makes sure that the string is valid and makes ptr point at the string*/
int copyToString(char *line,char *string){
    char *endptr = line;/*endptr will point to the end of the string*/
     if(*endptr != '"'){
        invalidString(line);
        return 0;
    }
    endptr++;
    while(*endptr && *endptr != '"')
        endptr++;
     if(*endptr != '"'){
     	invalidString(line);
     	return 0;
     }
    endptr++;
    if(*endptr != ' ' && *endptr != '\0' && *endptr != '\t' && *endptr != '\n'){
        extraText(endptr);
        return 0;
    }
    *endptr = '\0';
    strcpy(string,line);
    return 1;/*successfully copied*/
}

int isDigit(char n) {
    if (n < 48 || n > 57)
        return 0;
    else
        return 1;
}

int isLetter(char l) {
    if (l < 65 || l > 122)
        return 0;
    else
        return 1;
}

unsigned int convertToDigit(unsigned char c) {/*converts a single character of digit into it's value in int*/
    return (unsigned int) c - '0';
}

/*Two operands machine code- takes in two variables from a command, and decides how many word of binary code there should be
 * and adds them to the machine code*/
void twoOperandsMachineCode(char *v1, char *v2) {
    char exStringToAppend[MAXLINE];/*external labels to add to the ext file*/
    if (!firstScan)
        appendTocode(firstWord);/*The first binary word is ready from the previous methods*/
    if (firstWordCode.destination != LABEL && firstWordCode.opcode == LEA) {
        /*report on error! source on lea must be a label! */
        badOperand();
        return;
    }
    if (firstWordCode.source == REGISTER) {
        if(firstScan)
            ic++;
        else
            exC++;

        registerWordCode.source = convertToDigit(v1[2]);/*The number of the register at the third place(@ r num)*/
        registerWordCode.destination = 0;
        registerWordCode.are = ABSOLUTE;
        if (firstWordCode.destination != REGISTER)
            if (!firstScan)
                appendTocode(registerWord);/*The source register will be alone in this binary word*/
    } else if (firstWordCode.source == NUM) {
        if (firstScan)
            ic++;
        else
            exC++;
        numOrLabelWordCode.number = (unsigned) atoi(v1);
        numOrLabelWordCode.are = ABSOLUTE;/*absolute*/
        if (!firstScan)
            appendTocode(numOrLabelWord);
    } else if (firstWordCode.source == LABEL) {
        if (firstScan)
            ic++;
        if (!firstScan) {
            if (!findSymbol(v1)) {
                labelUndefined(v1);
                return;
            }
        }
        numOrLabelWordCode.number = getSymbolAddress(v1);
        if(getSymbolPlace(v1) == external){
            numOrLabelWordCode.are = EXTERNAL;/*external*/
            if(!firstScan) {
                sprintf(exStringToAppend, "%s:\t%d\n", v1, exC);
                strcat(externString, exStringToAppend);
            }
        } else
            numOrLabelWordCode.are = RELOCATABLE;/*relocateable*/
        if (!firstScan) {
            appendTocode(numOrLabelWord);
        }

        if(!firstScan)
            exC++;
    }

    /*One thing- I am aware to the fact that labels can be commands or data, and that jmp with data label won't work and command label with mov is not good either
     * but I asked you and you told me it is ok to assume that such thing won't happen and just write it in the comments that I am aware of it*/

    if (firstWordCode.destination == REGISTER) {
        if (firstWordCode.source != REGISTER) {
            if (firstScan)
                ic++;/*If both operands are registers they will share the same machine code word, otherwise, there will be a line for each one*/
            else
                exC++;
            registerWordCode.source = 0;
        }
        registerWordCode.destination = convertToDigit(v2[2]);/*The number of the register*/
        registerWordCode.are = ABSOLUTE;
        if (!firstScan)
            appendTocode(registerWord);
    }
    if (firstWordCode.destination == NUM) {
        if(firstWordCode.opcode !=CMP) {/*report on error! destination cannot be a number ! (unless it is cmp)*/
            badOperand();
            return;
        }

        numOrLabelWordCode.number = (unsigned ) atoi(v2);
        numOrLabelWordCode.are = ABSOLUTE;
        if(!firstScan)
            appendTocode(numOrLabelWord);
    } else if (firstWordCode.destination == LABEL) {
        if (firstScan)
            ic++;

        if (!firstScan) {
            if (!findSymbol(v2)) {
                labelUndefined(v2);
                return;
            }
        }
        numOrLabelWordCode.number = getSymbolAddress(v2);
        if(getSymbolPlace(v1) == external){
            numOrLabelWordCode.are = EXTERNAL;/*external*/
            if(!firstScan) {
                sprintf(exStringToAppend, "%s:\t%d\n", v1, exC);/*This is where exC counter comes into play*/
                strcat(externString, exStringToAppend);
            }
        }
        else
            numOrLabelWordCode.are = RELOCATABLE;/*relocatable*/
        if (!firstScan)
            appendTocode(numOrLabelWord);

        if(!firstScan)
            exC++;
    }
}
