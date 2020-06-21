#include "input.h"

int lineC;/*Line Counter*/
int dc;/*Data Counter*/
int ic;/*Instructions Counter*/
/*exC = external counter-> is being counted in the second scan,
 * to know the addresses in which external variables are being used, for the ext File*/
int exC;

int errorFlag;/*if the error flag turns on there is no need for a second scan, and no need to write a machine code*/
char fileName[MAXFILENAME];
