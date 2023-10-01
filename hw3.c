#include <stdio.h>
#include <math.h>

#define  A_MIN 184*0.85
#define  B_MIN 184*0.75
#define  C_MIN 184*0.65
#define  D_MIN 184*0.55

#define MAX_POINTS 184
#define MAX_Q_POINT 84

typedef struct {
    double ept;
    double epc;
} gradePoint;

gradePoint calPoint(char dgr, double qpt) {

    gradePoint gp;
    double dg;
    double totalPoints;
    double examPoints;
    double examPercents;

    double grade_arr[6] = {0.85, 0.75, 0.65, 0.55,0.00, 0.00};

    examPoints = MAX_POINTS*grade_arr[dgr%'A'] - qpt;
    examPercents = examPoints/MAX_POINTS;
    
    gp.ept = examPoints;
    gp.epc = examPercents*100;

    return gp;
}

int main() {

int qpt; //earned quiz point
char dgr; //desired grade
gradePoint gp;

printf("Enter desired letter grade -> ");
scanf("%c", &dgr);
printf("Enter points earned to date (max 84) -> ");
scanf("%d", &qpt);
gp = calPoint(dgr, qpt);
printf("Points earned to date: %.2lf (%.2lf) \n", (double)qpt, ((double)qpt/(double)MAX_Q_POINT)*100); // "%" 출력 해줘야함
printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
printf("Points required to earn %c grade: %.2lf (%.2lf)\n", dgr, gp.ept, gp.epc);// "%" 출력 해줘야함
printf("Minimum exam questions correct: %d (%.2lf)\n",(int)ceil(gp.ept/3), (ceil(gp.ept/3)/35)*100);// "%" 출력 해줘야함
gp = calPoint((int)(dgr+round((double)(dgr-65)/(double)5)+1), qpt);
printf("Points required to earn %c grade: %.2lf (%.2lf)\n",(char)(dgr+round((double)(dgr-65)/(double)5)+1), gp.ept, gp.epc);// "%" 출력 해줘야함
printf("Minimum exam questions correct: %d (%.2lf)\n",(int)ceil(gp.ept/3), (ceil(gp.ept/3)/35)*100);// "%" 출력 해줘야함
printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
//printf("Points Earned : %d , Grade Earned: %c \n", totalPoints, courseGrade);
return 0;
}
