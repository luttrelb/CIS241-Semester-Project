#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAXCHAR 1000

char str[MAXCHAR];
FILE * fp;




struct data
{
    double putCallRatio;
    char date[9];
    int spyPutVol;
    int spyCallVol;
    int spyTotal;
};

struct data dataArray[2331];

void nextLine() {
    fgets(str, MAXCHAR, fp);
}

void importData() {
    char* filename = "SPY241Project.txt";
    int i = 0;
    const char* delim = ",";


    fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("Could not find file %s", filename);
        return;
    }

    // find total lines in txt file
//    int count=0;
//    while(fgets(str,MAXCHAR,fp) != NULL) {
//        count++;
//    }
//    printf("\nTotal Lines: %d", count);
//
//    return; 2331
nextLine();
nextLine();
    int arrayPos = 0;

    char* ptr = strtok(str, delim);
    char *endPtr;

    while (ptr != NULL) {

        switch (i) {
            case 0:
//
                strcpy(dataArray[arrayPos].date,ptr);

                // for testing
                printf("Adding %s to date of struct in array pos %d\n", ptr, arrayPos);
                break;
            case 1:
                dataArray[arrayPos].putCallRatio = strtod(ptr, &endPtr);

                // for testing
                printf("Adding %s to ratio of struct in array pos %d\n\n", ptr, arrayPos);
                break;
            case 2:
                dataArray[arrayPos].spyPutVol = atoi(ptr);
                break;
            case 3:
                dataArray[arrayPos].spyCallVol = atoi(ptr);
                break;
            case 4:
                dataArray[arrayPos].spyTotal = atoi(ptr);
                break;
            default:
                printf("Something went wrong, arrayCount = %d, i = %d", arrayPos, i);
        }

        // reset ptr for each element in the line given
        if(i == 4) {
            nextLine();
            arrayPos++;
            ptr = strtok(str, delim);
            i = 0;
        }
        else {
            i++;
            ptr = strtok(NULL, delim);
        }
    }


    // For debugging purposes. print out each struct in the array to check for correct values
    int j = 0;

    printf("~~~~~~~~~~~~~~~~~~~~\n");
    while (j < 10) {

        printf("Array Item %d: \n", j);
        printf("\tDate: %s\n", dataArray[j].date);
        printf("\tRatio: %.2f\n", dataArray[j].putCallRatio);
        printf("\tPuts: %d\n", dataArray[j].spyPutVol);
        printf("\tCalls: %d\n", dataArray[j].spyCallVol);
        printf("\tTotal: %d\n\n", dataArray[j].spyTotal);


        j++;
    }
    int k;
    fclose(fp);
    double localmax = 0;
    double localmin = 0;
    localmin = dataArray[0].putCallRatio ;
    localmax = dataArray[0].putCallRatio ;
    for(k=0;k<2330;k++){
        if (dataArray[k].putCallRatio < localmin){
            localmin =dataArray[k].putCallRatio ;
            printf("New local min and date: %f, %s\n",localmin, dataArray[k].date);
        }
        if (dataArray[k].putCallRatio > localmax){
            localmax =dataArray[k].putCallRatio ;
            printf("New local max: %f, %s\n",localmax, dataArray[k].date);
        }


    }
    printf("overall local max: %f\n",localmax);
    printf("overall local min: %f",localmin);
}

int main() {
    importData();

    return 0;
}
