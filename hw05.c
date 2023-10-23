#include <stdio.h>


#define A_HOUR (60*60)
#define A_DAY (24*A_HOUR)
#define A_YEAR (365*A_DAY)

#define TRUE 1
#define FALSE 0

extern int calYear(long long * timestamp);
extern int calMonth(long long * timestamp, int year);

int main()
{
  long long ts;
  int year;
  int month;

  scanf("%lld", &ts);
  printf("timestamp : %lld \n", ts );

  year = calYear(&ts);
  printf("timestamp of months : %lld \n", ts);
  month = calMonth(&ts, year);
  printf("timestamp of days : %lld \n", ts);

  return 0;

}

int is_leap_year(int year)
{
  if (year % 4 == 0 && ((year % 100) != 0) || ((year % 400) == 0)) {
    return TRUE;
  }
  else
    return FALSE;
}

int calYear(long long * timestamp)
{
  int year;
  int days;
  int days_in_year;

  days = *timestamp / A_DAY;
//  printf("days_year : %d \n", days);

  for (year = 1970; year <= 2200; year++) {
    if (is_leap_year(year)) // 윤달 확인 후 일수를 조정함
      days_in_year = 366;
    else
      days_in_year = 365;

    if (days >= days_in_year) {
      days -= days_in_year;
      *timestamp -= days_in_year*A_DAY; //해당 년도의 달을 제외한 일수를 제거 (예,2023년 10/24 이면 2022년 12월31일까지 주어진 timestamp에서 빼준다)
    }
    else
      break;
  }

  //printf("year : %d, timestamp: %lld \n", year, *timestamp);
  return year;
}

int calMonth(long long * timestamp, int year)
{
  int days;
  int month = 0;
  int month_days = 0; // 해당월의 일수
  int months_days = 0;// 해당년도의 일수

  days = *timestamp / A_DAY;
  printf("days_month: %d \n",days);

  for (month = 1; month <= 12; month++)
  {
    switch(month) {
      case 1:
	month_days = 31;
      break;
      case 2:
        if (is_leap_year(year)) 
	{
          month_days = 29;
        }
	else month_days = 28;
        
      break;
      case 3:
	month_days = 31;
      break;
      case 4:
	month_days = 30;
      break;
      case 5:
	month_days = 31;
      break;
      case 6:
	month_days = 30;
      break;
      case 7:
	month_days = 31;
      break;
      case 8:
	month_days = 31;
      break;
      case 9:
	month_days = 30;
      break;
      case 10:
	month_days = 31;
      break;
      case 11:
	month_days = 30;
      break;
      case 12:
	month_days = 31;
      break;
    }
 
    if (days >= month_days) {
      days -= month_days;
 //     printf("days_end : %d \n", days);
      months_days += month_days;
    }
    else break;

  }

//  printf("month : %d, months_days: %d \n", month, months_days);
  *timestamp = *timestamp - months_days*A_DAY;

  return month;
}
