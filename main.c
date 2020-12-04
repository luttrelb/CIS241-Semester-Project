#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAXCHAR 1000

char str[MAXCHAR];
FILE * fp;

void printImportData();

struct data
{
    double putCallRatio;
    char date[9];
    int spyPutVol;
    int spyCallVol;
    int spyTotal;
};

struct data dataArray[2350];

int nextLine() {

    if (fgets(str, MAXCHAR, fp) == NULL)
        return 0;
    return 1;
}

void importData() {
    char* filename = "..\\SPY241Project.txt";
    int i = 0;
    const char* delim = ",";



    fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("Could not find file %s", filename);
        return;
    }

    nextLine();
    nextLine();

    int arrayPos = 0;
    char *endPtr;
    char* ptr = strtok(str, delim);

    while (arrayPos != 2330 && ptr != NULL) {

        switch (i) {
             //add date
            case 0:
               strcpy(dataArray[arrayPos].date, ptr);

                i++;
                ptr = strtok(NULL, delim);
                break;
            case 1:
                dataArray[arrayPos].putCallRatio = strtod(ptr, &endPtr);

                i++;
                ptr = strtok(NULL, delim);
                break;
            case 2:
                dataArray[arrayPos].spyPutVol = atoi(ptr);

                i++;
                ptr = strtok(NULL, delim);
                break;
            case 3:
                dataArray[arrayPos].spyCallVol = atoi(ptr);

                i++;
                ptr = strtok(NULL, delim);
                break;
            case 4:
                dataArray[arrayPos].spyTotal = atoi(ptr);

                arrayPos++;

                if (ptr != NULL)
                    if (nextLine() == 0)
                        ptr = NULL;
                    else
                        ptr = strtok(str, delim);
                    //ptr = (nextLine() == 0) ? NULL : strtok(str, delim);
                i = 0;
                break;
            default:
                printf("Something went wrong, arrayCount = %d, i = %d", arrayPos, i);
        }
    }
    fclose(fp);

//    printImportData();
}

void printImportData() {
    printf("\n~~~~~~~~~~~~~~~~~~~~~\n");
    int j = 0;
    while (j < 2330) {
        printf("Array Item %d: \n", j);
        printf("\tDate: %s\n", dataArray[j].date);
        printf("\tRatio: %.2f\n", dataArray[j].putCallRatio);
        printf("\tPuts: %d\n", dataArray[j].spyPutVol);
        printf("\tCalls: %d\n", dataArray[j].spyCallVol);
        printf("\tTotal: %d\n\n", dataArray[j].spyTotal);

        j++;
        int k;
    fclose(fp);
    double localmax = 0;
    double localmin = 0;
    localmin = dataArray[0].putCallRatio ;
    localmax = dataArray[0].putCallRatio ;
    for(k=0;k<2330;k++){
        if (dataArray[k].putCallRatio < localmin){
            localmin =dataArray[k].putCallRatio ;
        }
        if (dataArray[k].putCallRatio > localmax){
            localmax =dataArray[k].putCallRatio ;
        }


    }
    printf("overall local max: %f\n",localmax);
    printf("overall local min: %f",localmin);
    }
}
int main() {
    importData();

    return 0;
}
