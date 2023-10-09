#include <stdio.h>
#include "timestamp.h"

int main() {

    long long ts;
    int year = 0;
    int month = 0;
    int day = 0;

    int hr = 0;
    int min = 0;
    int sec = 0;

    char meridiem[2] = {'AM','PM'};

    printf("Enter unix timstamp -> ");
    scanf("%lf",&ts);

    year = calcYear(ts);
    month = calcMonth(ts, year);

    printf("-=-=-=-=-=-=-=-=-=-=\n");
    printf("Year: %d\n", year);
    printf("Leap: No. \n");
    printf("Month: d\n", Month);
    printf("Day: %d\n",day);
    printf("-=-=-=-=-=-=-=-=-=-=\n");
    printf("Time: %d:%d:%d %s",hr, min,sec,meridiem[hr/12] );
    return 0;
}
