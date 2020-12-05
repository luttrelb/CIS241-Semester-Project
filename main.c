#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAXCHAR 1000

char str[MAXCHAR];
FILE * fp;
int tempArrCounter = 0;

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

double getInfoOnYear(char* year) {
    int maxPut, maxCall,
            minPut = tempArr[0].spyPutVol,
            minCall = tempArr[0].spyCallVol;


    struct data maxPutD, minPutD, maxCallD, minCallD;

    int maxTotal, minTotal;
    int dateHighestTotal;

    double largestGrowthDiff;

    int count = 0;
    while(count < tempArrCounter) {

        if (maxPut < tempArr[count].spyPutVol) {
            maxPut = tempArr[count].spyPutVol;
            maxPutD = tempArr[count];
        }

        if (minPut > tempArr[count].spyPutVol) {
            minPut = tempArr[count].spyPutVol;
            minPutD = tempArr[count];
        }

        if (maxCall < tempArr[count].spyCallVol) {
            maxCall = tempArr[count].spyCallVol;
            maxCallD = tempArr[count];
        }

        if (minCall > tempArr[count].spyCallVol) {
            minCall = tempArr[count].spyCallVol;
            minCallD = tempArr[count];
        }

        count++;
    }

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nShowing statistics for year: 20%s\n", year);
    printf("\tThe highest put total was in year %s and reached a total of %d\n", maxPutD.date, maxPutD.spyPutVol);
    printf("\tThe lowest put total was in year %s and reached a total of %d\n", minPutD.date, minPutD.spyPutVol);

    printf("\tThe highest call total was in year %s and reached a total of %d\n", maxCallD.date, maxCallD.spyCallVol);
    printf("\tThe lowest call total was in year %s and reached a total of %d\n", minCallD.date, minCallD.spyCallVol);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}



void getRangeByDate(char *date) {

    int counter = 0;
    for (int i = 0; i < 2330; i++) {
        if (strstr(dataArray[i].date + 4, date) != NULL) {
            tempArr[counter] = dataArray[i];
            counter++;
        }
    }
      tempArrCounter = counter;
}


void importData() {
    char *filename = "SPY241Project.txt";
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

    int k;
    fclose(fp);
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


        j++;
    }
}

void findDate(char *date){
    	int i=0;
    	while(i<2331){
    		if(strcmp(date, dataArray[i].date) == 0){
    			printf("Array Item %d: \n", i);
        		printf("\tDate: %s\n", dataArray[i].date);
        		printf("\tRatio: %.2f\n", dataArray[i].putCallRatio);
        		printf("\tPuts: %d\n", dataArray[i].spyPutVol);
        		printf("\tCalls: %d\n", dataArray[i].spyCallVol);
        		printf("\tTotal: %d\n\n", dataArray[i].spyTotal);
        		break;
    		}
    		i++;
    	}
}

int main() {
    importData();

    char scanDate[3];
	char scanDate2[9];
    int switchcase = 0;
    printf("Press 0 to Organize And Display The Statistics By Year \n"
                "Press 1 For General Info For Each Year \n"
                "Press 2 To Search For Specific Date \n"
                "Press 3 to close\n"
                "");
    scanf("%d", &switchcase);
	while (switchcase != 4) {

       switch (switchcase) {

            case 0:
                printf("Please Select Year Between 2010-2019 In The Form xx \n");
                scanf(" %s", scanDate);
		        char *ptr = scanDate;
                getRangeByDate(ptr);
		        printData(0, tempArrCounter-1, tempArr);
                printf("System Exit");
                switchcase = 4;
                break;
	        case 1:
		        getRangeByDate("10");
            	getInfoOnYear("10");
                getRangeByDate("11");
            	getInfoOnYear("11");
                getRangeByDate("12");
            	getInfoOnYear("12");
                getRangeByDate("13");
            	getInfoOnYear("13");
                getRangeByDate("14");
            	getInfoOnYear("14");
                getRangeByDate("15");
		        getInfoOnYear("15");
                getRangeByDate("16");
            	getInfoOnYear("16");
                getRangeByDate("17");
            	getInfoOnYear("17");
                getRangeByDate("18");
            	getInfoOnYear("18");
                getRangeByDate("19");
            	getInfoOnYear("19");
                printf("System Exit");
		        switchcase = 4;
		        break;
            case 2:
                printf("Please Select Date Between 2010-2019 In The Form xx/xx/xx \n");
                scanf(" %s", scanDate2);
		        char *ptr2 = scanDate2;
                findDate(ptr2);
                printf("System Exit");
                switchcase = 4;
            case 3:
                exit(0);
	    }
    }
    return 0;
}



