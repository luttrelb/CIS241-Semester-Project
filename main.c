#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAXCHAR 1000

char str[MAXCHAR];
FILE *fp;


struct data {
    double putCallRatio;
    char date[9];
    int spyPutVol;
    int spyCallVol;
    int spyTotal;
};

struct data dataArray[2331];
struct data tempArr[2331];

void nextLine() {
    fgets(str, MAXCHAR, fp);
}

<<<<<<< HEAD
void getRangeByDate(char* date) {

    int counter = 0;
    for (int i = 0; i < 2330; i++) {
        if (strstr(dataArray[i].date + 4, date) != NULL) {
            tempArr[counter] = dataArray[i];
            counter++;
        }
    }
}

void importData() {
    char *filename = "..\\SPY241Project.txt";
=======
// void switchCase() {

//     char* filename = "SPY241Project.txt";
//     int i = 0;
//     const char* delim = ",";



//     fp = fopen(filename, "r");

//     if(fp == NULL) {
//         printf("Could not find file %s", filename);
//         return;
//     }
//     char *endPtr;
//     char* ptr = strtok(str, delim);
//     char scanDate;
//     int switchcase=0;
//     printf("Press 0 to Organize SPY Put/Call Ratio By Date \n"
//                 "Press 1 For SPY Put/Call Ratio Local Minimum\n"
//                 "Press 2 for SPY Put/Call Ratio Local Maximum\n"
//                 "");
//     scanf("%d", &switchcase);
//     while (switchcase != 4){

//        switch (switchcase) {

//             case 0:
//                 printf("Please Select Year Between 2010-2019 In The Form x/xx/xxxx \n");
//                 scanf("%c",&scanDate);
//                 printf("%c"scanDate);
            
//             // case 1:

//             // case 2:

//             // case 3:

//             // case 4:
//         }

//     }
// }

void importData() {
    char* filename = "..\\SPY241Project.txt";
>>>>>>> 402d05ab3060c5f592845d511f14f52cd883cc50
    int i = 0;
    const char *delim = ",";


    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Could not find file %s", filename);
        return;
    }

    nextLine();
    nextLine();

    int arrayPos = 0;

    char *ptr = strtok(str, delim);
    char *endPtr;

    while (ptr != NULL) {

        switch (i) {
            case 0:
                strcpy(dataArray[arrayPos].date, ptr);

                break;
            case 1:
                dataArray[arrayPos].putCallRatio = strtod(ptr, &endPtr);

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
        if (i == 4) {
            nextLine();
            arrayPos++;
            ptr = strtok(str, delim);
            i = 0;
        } else {
            i++;
            ptr = strtok(NULL, delim);
        }
    }

<<<<<<< HEAD
    int k;
    fclose(fp);
    double localmax = 0;
    double localmin = 0;
    localmin = dataArray[0].putCallRatio;
    localmax = dataArray[0].putCallRatio;
    for (k = 0; k < 2330; k++) {
        if (dataArray[k].putCallRatio < localmin) {
            localmin = dataArray[k].putCallRatio;
            printf("New local min and date: %.2f, %s\n", localmin, dataArray[k].date);
        }
        if (dataArray[k].putCallRatio > localmax) {
            localmax = dataArray[k].putCallRatio;
            printf("New local max and date: %.2f, %s\n", localmax, dataArray[k].date);
        }


    }
    printf("overall local max: %f\n", localmax);
    printf("overall local min: %f", localmin);
}

double min[2300];
double max[2300];

void findMinMax() {

}

void printData(int start, int end, struct data arr[]) {
    int j = start;

    printf("~~~~~~~~~~~~~~~~~~~~\n");
    while (j <= end) {

        printf("Array Item %d: \n", j);
        printf("\tDate: %s\n", arr[j].date);
        printf("\tRatio: %.2f\n", arr[j].putCallRatio);
        printf("\tPuts: %d\n", arr[j].spyPutVol);
        printf("\tCalls: %d\n", arr[j].spyCallVol);
        printf("\tTotal: %d\n\n", arr[j].spyTotal);
=======

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
>>>>>>> 402d05ab3060c5f592845d511f14f52cd883cc50


        j++;
    }
}

int main() {
    importData();
<<<<<<< HEAD
    getRangeByDate("15");
    //printData(0, 200, tempArr);
=======
    char scanDate;
    int switchcase=0;
    printf("Press 0 to Organize SPY Put/Call Ratio By Date \n"
                "Press 1 For SPY Put/Call Ratio Local Minimum\n"
                "Press 2 for SPY Put/Call Ratio Local Maximum\n"
                "");
    scanf("%d", &switchcase);
	while (switchcase != 4){
>>>>>>> 402d05ab3060c5f592845d511f14f52cd883cc50

       switch (switchcase) {

            case 0:
                printf("Please Select Year Between 2010-2019 In The Form x/xx/xxxx \n");
                scanf("%c",&scanDate);
                printf("%c", scanDate);
            	
        }

    }
    return 0;
}
