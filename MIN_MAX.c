struct data MIN_MAX(dataarray){
    double localmax = 0;
    int k;
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
            printf("New local max and date: %f, %s\n",localmax, dataArray[k].date);
        }

    }
    printf("overall local max: %f\n",localmax);
    printf("overall local min: %f",localmin);
}
