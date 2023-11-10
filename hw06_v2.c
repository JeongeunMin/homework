/*****+*--*-*------*-**---**--***-**--**--*-***--***************************
 *
 *  Homework #:6
 *
 *  Academic Integrity Statement:
 *
 *  I have not used source code obtained from any other unauthorized source, 
 *  either modified or unmodified.  Neither have I provided access to my code 
 *  to another. The effort I am submitting is my own original work.
 *
 *  Program Description:
 *
 ******+*--*-*------*-**---**--***-**--**--*-***--**************************/

#include <stdio.h>

#define SECONDS_IN_A_MINUTE 60
#define SECONDS_IN_A_HOUR (60*SECONDS_IN_A_MINUTE)
#define SECONDS_IN_A_DAY (24*SECONDS_IN_A_HOUR)

#define HOURS_IN_A_DAY 24
#define DAYS_IN_A_YEAR 365

#define MERIDIEM_PM 1
#define MERIDIEM_AM 0

#define TRUE 1
#define FALSE 0

#define MAX_OFFSET 14
#define MIN_OFFSET -12
#define EXIT_OFFSET -100

#define MAX_COUNT 10

void showTimeInfo (long long timestamp,int year, int month, int offset );
void awareTimezone(long long timestamp);
int calcYear(long long * timestamp);
int calcMonth(long long * timestamp, int year);

int main (void)
{
  // Declarations
  long long ts = 0;
  int utc_offset = 0;
  int spanned_hours = 0;

  printf("Enter unix timestamp -> ");
  scanf("%lld", &ts);
  // Statements
  while (ts < 0) 
  {
    printf("\nError! Timestamp must be >= 0.\n");
    printf("\nEnter unix timestamp -> ");
    scanf("%lld", &ts);
  }

  awareTimezone(ts);

  return 0;
}

int checkLeafYear (int year)
{
  // Declarations
  int isLeafYear; // Variable to store the result indicating if the year is a leap year.

  // Statements
  if (((!(year % 4) && (year % 100)) || !(year % 400))) // Check for Leap Year
  {
    isLeafYear = TRUE; // The year is a leap year.
  }
  else
  {
    isLeafYear = FALSE; // The year is not a leap year.
  }
  return isLeafYear;
}

int getNumOfDays(int month, int year)
{
  int num_of_days = 0;

  switch(month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        num_of_days = 31;
        break;
    case 2:
        if (checkLeafYear(year))
        {
        num_of_days = 29;
        } 
        else num_of_days = 28;  
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        num_of_days = 30;
        break;
  }

  return num_of_days;
}

int calcYear(long long * timestamp)
{
  int year = 1970;
  int days;
  int days_in_year = 0;

  days = *timestamp / SECONDS_IN_A_DAY;

  if (checkLeafYear(year))
  {
    days_in_year = DAYS_IN_A_YEAR + 1;
  }
  else
  {
    days_in_year = DAYS_IN_A_YEAR;
  }

  while(days >= days_in_year)
  {

    days -= days_in_year;
    *timestamp -= days_in_year*SECONDS_IN_A_DAY;
    year++;
    if (checkLeafYear(year))
    {
      days_in_year = DAYS_IN_A_YEAR + 1;
    }
    else
    {
      days_in_year = DAYS_IN_A_YEAR;
    }
  }

  return year;
}

int calcMonth(long long * timestamp, int year)
{
  int days;
  int month = 1; // 1
  int days_of_month = 31; // 1
  int days_so_far = 0; //

  days = *timestamp / SECONDS_IN_A_DAY;
  if(days <= days_of_month) //January
  {
    days_so_far = days;
  }
  else
  {
    while(days >= days_of_month)
    {
      days -= days_of_month;
      days_so_far += days_of_month;
      month++;

      days_of_month = getNumOfDays(month, year); 
    }
    
    *timestamp = *timestamp - days_so_far * SECONDS_IN_A_DAY;
  }
  return month;
}

void showTimeInfo (long long timestamp, int year, int month, int offset)
{
  // Declarations
  long secondOfDay; // Variable to store the number of seconds since midnight.
  int years = year;
  int months = month;
  int days;
  int hours; // Variable to store the calculated hours.
  int minutes; // Variable to store the calculated minutes.
  int seconds; // Variable to store calculated seconds.
  int meridiem = MERIDIEM_AM; // Variable to store whether it is AM or PM.

  // Statements
  secondOfDay = timestamp % SECONDS_IN_A_DAY;
  seconds = secondOfDay % SECONDS_IN_A_MINUTE;
  secondOfDay = secondOfDay / SECONDS_IN_A_MINUTE;
  minutes = secondOfDay % SECONDS_IN_A_MINUTE;
  secondOfDay = secondOfDay / SECONDS_IN_A_MINUTE;
  hours = secondOfDay % HOURS_IN_A_DAY;

  // Display Time
  days = timestamp / SECONDS_IN_A_DAY + 1;
  hours = hours + offset;

  if (hours < 0)
  {
    hours += 24;
    days -= 1;
    if (days <= 0)
    {
        months -= 1;
        days += getNumOfDays(months, year);
        if (months <= 0)
        {
            months += 12;
            years -= 1;
        }
    }
  }
  else if (hours >= 24)
  {
    hours -= 24;
    days += 1;
    if (days > getNumOfDays(months, year))
    {
        months += 1;
        days -= getNumOfDays(months, year);
        if(months > 12)
        {
            months -= 12;
            years += 1;
        }
    } 
  }
 
  if ((hours / 12 > 0) && (hours % 12 >= 0))
  {
    meridiem = MERIDIEM_PM;
  }
  else
  {
    meridiem = MERIDIEM_AM;
  }

  if (hours % 12 > 0 )
  {
    hours %= 12;
  }
  else if (hours == 0)
  {
    hours = 12;
  }
   

  printf("UTC %d:   ", offset);
  printf("%d-%d%d-%d%d ", years, months / 10,months % 10, days / 10, days % 10);
  printf("%d%d", hours / 10, hours % 10);
  printf(":%d%d", minutes / 10, minutes % 10);
  printf(":%d%d", seconds / 10, seconds % 10);

  if (meridiem ==  MERIDIEM_PM)
  {
    printf(" %s\n", "PM");
  }
  else
  {
    printf(" %s\n", "AM");
  }
}

void awareTimezone(long long timestamp)
{
  long long ts = timestamp; // Variable to store the input unix timestamp.
  int year; // Variable to store the calculated year.
  int month; // Variable to store the calculated month.
  
  int utc_offset = 0;
  int min_offset = MAX_OFFSET;
  int max_offset = MIN_OFFSET;

  int offset[MAX_COUNT] = {0,};
  int count = 0;//number of offset

  int spanned_hours = 0;

  int exit_condition = FALSE;

  while (!exit_condition)
  {
    printf("Enter offset, or -100 to finish -> ");
    scanf("%d", &utc_offset);

    if((utc_offset > MAX_OFFSET || utc_offset < MIN_OFFSET) && (utc_offset != EXIT_OFFSET))
    {
      printf("Error! Offset must be between %d and %d inclusive\n", MIN_OFFSET, MAX_OFFSET);
    }
    else if(utc_offset != EXIT_OFFSET)
    {
      if(min_offset > utc_offset)
      {
        min_offset = utc_offset;
      }
      
      if(max_offset < utc_offset)
      {
        max_offset = utc_offset; 
      }
      offset[count] = utc_offset;
      count++;
    }

    if (utc_offset == EXIT_OFFSET || count >= MAX_COUNT)
    {
      exit_condition = TRUE;
    } 
  }


  year = calcYear(&ts);
  month = calcMonth(&ts, year);

  for(int i = 0 ; i < count; i++)
  {
    showTimeInfo(ts, year, month, offset[i]);
  }

  spanned_hours = max_offset - min_offset + 1;
  printf("Hours spanned: %d\n", spanned_hours);
}
