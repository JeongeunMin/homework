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
#include "timestamp.h"

#define HOUR_OF_ONEDAY 24

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

int calcYear(long long * timestamp)
{
  int year = EPOCH;
  int days;
  int days_in_year = 0;

  days = *timestamp / SECONDS_IN_DAY;

  if (checkLeafYear(year))
  {
    days_in_year = DAYS_IN_YEAR + 1;
  }
  else
  {
    days_in_year = DAYS_IN_YEAR;
  }

  while(days >= days_in_year)
  {
    days -= days_in_year;
    *timestamp -= days_in_year*SECONDS_IN_DAY;
    year++;

    if (checkLeafYear(year))
    {
      days_in_year = DAYS_IN_YEAR + 1;
    }
    else
    {
      days_in_year = DAYS_IN_YEAR;
    }
  }

  return year;
}

int calcMonth(long long * timestamp, int year)
{
  int days;
  int month = 1; // 1
  int month_days = 31; // 1
  int months_days = 0; // 

  days = *timestamp / SECONDS_IN_DAY;
  if(days <= month_days) //January
  {
    months_days = days;
  }
  else
  {
    while(days >= month_days)
    {
      days -= month_days;
      months_days += month_days;
      month++;
 
      switch(month)
      {
        case 1:
          month_days = 31;
          break;
        case 2:
          if (checkLeafYear(year))
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
    }

    *timestamp = *timestamp - months_days * SECONDS_IN_DAY;
  }
  return month;
}

void showTimeInfo (long long timestamp, int year, int month, int offset)
{
  // Declarations
  long secondOfDay; // Variable to store the number of seconds since midnight.
  int month_days;
  int years = year;
  int months = month;
  int days;
  int hours; // Variable to store the calculated hours.
  int minutes; // Variable to store the calculated minutes.
  int seconds; // Variable to store calculated seconds.
  int meridiem = MERIDIEM_AM; // Variable to store whether it is AM or PM.

  // Statements
  secondOfDay = timestamp % SECONDS_IN_DAY;
  seconds = secondOfDay % SECONDS_IN_MINUTE;
  secondOfDay = secondOfDay / SECONDS_IN_MINUTE;
  minutes = secondOfDay % SECONDS_IN_MINUTE;
  secondOfDay = secondOfDay / SECONDS_IN_MINUTE;
  hours = secondOfDay % HOUR_OF_ONEDAY;

  // Display Time
  days = timestamp / SECONDS_IN_DAY + 1;

  switch(months)
  {
    case 1:
        month_days = 31;
        break;
    case 2:
        if (checkLeafYear(year))
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

  if (hours % 12 >= 0 )
  {
    hours %= 12;
  }

  hours = hours + offset;

  if (hours < 0)
  {
    hours += 24;
    days -= 1;
    if (days <= 0)
    {
        days += month_days;
        months -= 1;
        if (months <= 0)
        {
            months += 12;
            years -= 1;
        }
    }
  } 
  else if (hours > 12)
  {
    days += 1;
    if (days > month_days)
    {
        days -= month_days;
        months += 1;
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

  printf("%d-%d-%d ", years, months, days);
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
  int earliest_offset = MAX_OFFSET;
  int latest_offset = MIN_OFFSET;

  int offset[MAX_COUNT] = {0,};
  int count = 0;

  int spanned_hours = 0;

  while((utc_offset != EXIT_OFFSET) && (count <= MAX_COUNT))
  {
    printf("Enter offset, or -100 to finish -> ");
    scanf("%d", &utc_offset);

    if((utc_offset > MAX_OFFSET || utc_offset < MIN_OFFSET) && (utc_offset != EXIT_OFFSET))
    {
      printf("Error! Offset must be between %d and %d inclusive\n", MIN_OFFSET, MAX_OFFSET);
    }
    else if(utc_offset != EXIT_OFFSET)
    {
      if(earliest_offset > utc_offset)
      {
        earliest_offset = utc_offset;
      }
      
      if(latest_offset < utc_offset)
      {
        latest_offset = utc_offset; 
      }
      offset[count] = utc_offset;
      count++;
    } 
  }

  spanned_hours = latest_offset - earliest_offset + 1;

  year = calcYear(&ts);
  month = calcMonth(&ts, year);


  for(int i = 0 ; i < count; i++)
  {
    printf("UTC %d:  ", offset[i]);
    showTimeInfo(ts, year, month, offset[i]);
  }

  printf("Hours spanned: %d\n", spanned_hours);
}
