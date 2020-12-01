#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAXCHAR 1000

struct data
{
    double putCallRatio;
    char date[8];
    int spyPutVol;
    int spyCallVol;
    int spyTotal;
}

void importData() {
    FILE * fp;
    char str[MAXCHAR];
    char* filename = "..\\SPY241Project.txt";
    char* token;
    int i = 0;
    const char de[2] = ",";

    fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("Could not find file %s", filename);
        return;
    }


    while (fgets(str, MAXCHAR, fp) != NULL) {


        printf("%s", str);

        i++;
    }

    fclose(fp);
}

int main() {
    importData();

    return 0;
}
