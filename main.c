#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

/**
 * @authors Justin Jahlas, Brennan Luttrell 
 */

#define MAXCHAR 1000

char str[MAXCHAR];
FILE * fp;
int tempArrCounter = 0;

/**
 * Structure that holds elements to be used in a structure array
 */
struct data {
    double putCallRatio; //Put Call Ratio is the number of puts over the number of calls
    char date[9]; //date in xx/xx/xx
    int spyPutVol; //SPY put volume for a specific day
    int spyCallVol; //SPY call volume for a specific day
    int spyTotal; // total SPY
};


struct data dataArray[2331];
struct data tempArr[2331];

/**
 * moves the str pointer to the next line in the file
 */
void nextLine() {
    fgets(str, MAXCHAR, fp);
}

/**
 * take in the last two digits of a year and prints to
 * terminal various statistics regarding the years stock
 * trades.
 *
 * @param year string of the last 2 digits of the year
 */
void getInfoOnYear(char* year) {
    int maxPut = tempArr[0].spyPutVol,
            maxCall = tempArr[0].spyCallVol,
            minPut = tempArr[0].spyPutVol,
            minCall = tempArr[0].spyCallVol;


    struct data maxPutD = tempArr[0], minPutD = tempArr[0],
            maxCallD = tempArr[0], minCallD = tempArr[0],
            minRatioD = tempArr[0], maxRatioD = tempArr[0];

    double maxRatio = tempArr[0].putCallRatio, minRatio = tempArr[0].putCallRatio;
    

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

        if(minRatio > tempArr[count].putCallRatio) {
            minRatio = tempArr[count].putCallRatio;
            minRatioD = tempArr[count];
        }

        if(maxRatio < tempArr[count].putCallRatio) {
            maxRatio = tempArr[count].putCallRatio;
            maxRatioD = tempArr[count];
        }

        count++;
    }

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nShowing statistics for year: 20%s\n", year);
    printf("\tThe highest put total was in year %s and reached a total of %d.\n", maxPutD.date, maxPutD.spyPutVol);
    printf("\tThe lowest put total was in year %s and reached a total of %d.\n", minPutD.date, minPutD.spyPutVol);

    printf("\tThe highest call total was in year %s and reached a total of %d.\n", maxCallD.date, maxCallD.spyCallVol);
    printf("\tThe lowest call total was in year %s and reached a total of %d.\n", minCallD.date, minCallD.spyCallVol);

    printf("\n\nThe year began quite %s on %s with a put/call ratio of %.2f.", tempArr[0].putCallRatio < 0.70 ? "bullish" : "bearish", tempArr[0].date, tempArr[0].putCallRatio);
    printf("\nThe market was most bearish on %s with the highest put/call ratio of the year at %.2f.", maxRatioD.date, maxRatioD.putCallRatio);
    printf("\nThe market was most bullish on %s with the lowest put/call ratio of the year at %.2f.", minRatioD.date, minRatioD.putCallRatio);
    printf("\nThe year ended %s, with a put/call ratio of %.2f on %s.", tempArr[tempArrCounter-1].putCallRatio < 0.70 ? "bullish" : "bearish", tempArr[tempArrCounter-1].putCallRatio, tempArr[tempArrCounter-1].date);
}


/**
 * Populates the tempArr with all of the structs that contain the year-range
 * specified
 *
 * @param date last 2 digits of date to grab from file
 */
void getRangeByDate(char *date) {

    tempArrCounter = 0;
    int counter = 0;
    for (int i = 0; i < 2330; i++) {
        if (strstr(dataArray[i].date + 4, date) != NULL) {
            tempArr[counter] = dataArray[i];
            counter++;
        }
    }
      tempArrCounter = counter;
}

/**
 * imports all the file data into structs to be used within the program
 */
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
    fclose(fp);
}



/**
 * prints out basic info of each struct within the range
 *
 * @param start the index to begin reporting from
 * @param end the last index (inclusive) to end reporting.
 * @param arr the array of data that should be iterated through
 */
void printData(int start, int end, struct data arr[]) {
    int j = start;

    printf("~~~~~~~~~~~~~~~~~~~~\n");
    while (j <= end) {

        printf("Date: %s\n", arr[j].date);
        printf("\tRatio: %.2f\n", arr[j].putCallRatio);
        printf("\tPuts: %d\n", arr[j].spyPutVol);
        printf("\tCalls: %d\n", arr[j].spyCallVol);
        printf("\tTotal: %d\n\n", arr[j].spyTotal);


        j++;
    }
}

/**
 * fetches the struct info of a given date
 *
 * @param date last 2 digits of date to grab from file
 */
void findDate(char *date){
    	int i=0;
    	while(i<2331){
    		if(strcmp(date, dataArray[i].date) == 0){
        		printf("Date: %s\n", dataArray[i].date);
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
/**
 * Text Options For User Input.
 */
    printf("Press 0 to Organize And Display The Statistics By Year \n"
                "Press 1 For General Info For Each Year \n"
                "Press 2 To Search For Specific Date \n"
                "Press 3 to close\n"
                "");
    scanf("%d", &switchcase);
/**
 * Switch statement that acts as the user interface. The user has the options
 * to select and display statistical information by year, to display generalized
 * statistical analysis' for each year, and to search for information by date.
 */
	while (switchcase != 4) {

       switch (switchcase) {

            case 0:
                printf("Please Select Year Between 2010-2019 In The Form xx \n");
                scanf(" %s", scanDate);
		        char *ptr = scanDate;
                getRangeByDate(ptr);
		        printData(0, tempArrCounter-1, tempArr);
                printf("\nSystem Exit");
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
                printf("\nSystem Exit");
		        switchcase = 4;
		        break;
            case 2:
                printf("Please Select Date Between 2010-2019 In The Form xx/xx/xx \n");
                scanf(" %s", scanDate2);
		        char *ptr2 = scanDate2;
                findDate(ptr2);
                printf("\nSystem Exit");
                switchcase = 4;
                break;
            case 3:
                exit(0);
	    }
    }
    //ignore
    return 0;
}



