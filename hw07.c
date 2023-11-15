#include <stdio.h>
#include <stdlib.h>

#define EVEN 0
#define ODD 1

#define FALSE 0
#define TRUE 1

void generateScore(int seed, int num_of_stud, int * score);
void ascendingScore(int num_of_stud, int * score);
void drawHistoram(int num_of_stud, int * score);

int main()
{
  int * score;
  int seed = 0;
  int num_of_stud;
  int exit_condition = FALSE;

  while (exit_condition == FALSE)
  {
    printf("Enter Seed -> ");
    scanf("%d", &seed);
    if (seed <= 0)
    {
      printf("Error: seed must be positive\n");
    }
    else
    {
      exit_condition = TRUE;
    }
  }

  exit_condition = FALSE;

  while (exit_condition == FALSE)
  {
    printf("Enter number of students -> ");
    scanf("%d", &num_of_stud);
    if (num_of_stud <= 0)
    {
      printf("Error: need at least one student\n");
    }
    else if (num_of_stud > 100)
    {
      printf("Error: no more than 100 students\n");
    }
    else
    {
      exit_condition = TRUE;
    }
  }

  score = (int *)malloc(sizeof(num_of_stud));
  generateScore(seed, num_of_stud, score);
  ascendingScore(num_of_stud, score);
  drawHistoram(num_of_stud, score);
  return 0;
}

void generateScore(int seed, int num_of_stud, int * score)
{
  int i;
  int min;
  int max;
  int avg;
  int med;

  srand(seed);

  for (i = 0 ; i < num_of_stud ; i++)
  {
    *score = (rand()%36)*3;
    score++;
  }
}

void ascendingScore(int num_of_stud, int * score)
{
  int i, j, tmp;
  for (i = 0 ; i < num_of_stud; i++)
  {
    for (j = i ; j < num_of_stud; j++)
    {
      if (score[i] > score[j])
      {
        tmp = score[i];
        score[i] = score[j];
        score[j] = tmp;
      }
    }
  }
}

//#1 recursive function
int sumOfScore(int num_of_stud, int * score)
{
  int i;
  int sum;

  if (num_of_stud == 0)
  {
    return 0;
  }
  else
  {
    return score[num_of_stud-1] + sumOfScore(num_of_stud-1, score);
  }
}

void sortBucket(int num_of_stud, int * score, int * bucket)
{
  int i,j = 0;
  int s;//score

  //buceck[0] = 0 ~ 9, bucket[1] = 10 ~ 19...
  for(i = 0 ; i < num_of_stud ; i++)
  {
    s = score[i]/10;
    *(bucket+s) += 1;
  }
}

void drawHistoram(int num_of_stud, int * score)
{
  int i,j = 0;
  int min ,max = 0;
  double avg ,med = 0;
  int bucket[11] = {0,};

  min = score[0];
  max = score[num_of_stud-1];
  avg = (double)((sumOfScore(num_of_stud, score))/num_of_stud);
  
  if (num_of_stud%2 == EVEN) //EVEN
  {
    med = (score[num_of_stud/2-1] + score[num_of_stud/2])/2.0;
  }
  else //ODD
  {
    med = score[num_of_stud/2];
  }

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=\n");
  printf("Minimum:               %d\n", min);
  printf("Average:               %.0f\n", avg);
  printf("Median:                %.0f\n", med);
  printf("Maximum:               %d\n", max);
  printf("=-=-=-=-=-=-=-=-=-=-=-=-=\n");

  sortBucket(num_of_stud, score, bucket);

  for(i = 0 ; i < 11 ; i++)
  {
    if (bucket[i] != 0)
    {
      printf("%3d: ( %2d) ", 10*i, bucket[i]);
      for(j = 0 ; j < bucket[i] ; j++)
      {
        printf("_");
      }
    }
    else
    {
      printf("%3d: ", 10*i);
    }
    printf("\n");
  }
}
