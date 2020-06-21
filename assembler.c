#include "input.h"
#include "code.h"

extern int lineC;/*line counter*/
extern char fileName[MAXFILENAME];
/*strings for ext and ent files*/
extern char externString[];
extern char entryString[];
/*strings that will contain binary code of operations and data*/
char machineCodeString[MAXFILE];
char machineDataString[MAXFILE];
/*the machinecode that contains both code and data in binary*/
char objBinary[MAXFILE];
/*the final machinecode that conatins everything in base64*/
char objBase64[MAXFILE];
int firstScan = 1;/*Flag to know if it is the first file's scan*/

void reset();

int main(int argc, char *argv[]) {
    FILE *fileptr;
    int file,scan;
    char fileContent [MAXLINE];
    char fname[MAXFILENAME] = "";
    for(file=1;file<argc;file++) {
        errorFlag = 0;/*There are no errors in the new file untill we find them*/
        firstScan = 1;/*First scan on the new file*/

        /*reset all the counters in the new file*/
        ic = 100;/*instructions counter*/
        dc = 0;/*data counter*/
        exC = 100;/*counter that is being calculated on the second scan, to know when .extern labels are used*/
	    lineC = 1;/*The line counter*/
	    strcpy(fileContent,"");
	    strcpy(fname,"");
	    strcpy(fileName,"./");
            strcat(fileName,argv[file]);
            strcat(fname,fileName);
            strcat(fname,".as");
        for(scan = 0;scan<2;scan++) {/*We will make two scans on each assembly file*/
            fileptr = fopen(fname, "r");
            if (fileptr == NULL) {
                fileNotFound(fname);
                break;
            }
            while (fgets(fileContent, MAXLINE, fileptr) != NULL) {
                startParsing(fileContent);
                lineC++;/*increase the line counter for every new line*/
            }
            if(firstScan)/*when we are done with the first scan, we need to update the data label addresses*/
                updateSymbolsAdresses();
            lineC = 1;/*reset the line in the end of file*/
            firstScan = 0;/*turn the firstScan flag off*/
            if(errorFlag) {/*There is no need to go to another scan if there is an error*/
                break;
            }
        }
        if(!errorFlag){/*write the machineCode only if there are no errors*/
            ;/*Write all necessary Files*/

            strcat(objBinary,machineCodeString);
            strcat(objBinary,machineDataString);
            writeExtFile();
            writeEntFile();
            writeObjFile();
        }
        if(fileptr != NULL)
            fclose(fileptr);
        freeList();/*when we are done with a file, we will remove all the labels*/
        reset();
    }

    return 0;
}

void reset(){
    firstWordCode.are = 0;
    firstWordCode.destination = 0;
    firstWordCode.opcode = 0;
    firstWordCode.source = 0;
    registerWordCode.source = 0;
    registerWordCode.destination = 0;
    registerWordCode.are = 0;
    numOrLabelWordCode.are = 0;
    numOrLabelWordCode.number = 0;
    strcpy(objBase64,"");
    strcpy(machineDataString,"");
    strcpy(machineCodeString,"");
    strcpy(objBinary,"");
    strcpy(externString,"");
    strcpy(entryString,"");
    dc = 0;
    ic = 100;
    exC = 0;
}
