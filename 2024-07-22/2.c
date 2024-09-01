/*
2. Write a C program to assign values to each member of the following structure.
Pass the populated structure to a function Using call-by-value and another
function using call-by-address and print the value of each member of the
structure.
struct student_info{
int roll_no;
char name [50];
float CGPA;
struct dob age;
};
*/

#include <stdio.h>
#include <string.h>

typedef struct dob {
    int year;
    int month;
    int date;
} dob;

typedef struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    dob age;
} student_info;

void call_by_value(student_info s1) {
    printf("%d\n", s1.roll_no);
    printf("%s\n", s1.name);
    printf("%f\n", s1.CGPA);
    printf("%d-%d-%d\n", s1.age.date, s1.age.month, s1.age.year);
} 

void call_by_reference(student_info *s1) {
    printf("%d\n", s1->roll_no);
    printf("%s\n", s1->name);
    printf("%f\n", s1->CGPA);
    printf("%d-%d-%d\n", s1->age.date, s1->age.month, s1->age.year);
}   

int main(int argc, char* argv[]) {

    student_info s1;

    s1.roll_no = 22051662;
    strncpy(s1.name, "Aman", 50);
    s1.CGPA = 9.47;
    s1.age.date = 31;
    s1.age.month = 3;
    s1.age.year = 2003;

    printf("Call by value: \n");
    call_by_value(s1);

    printf("\n\n");

    printf("Call by reference: \n");
    call_by_reference(&s1);

    return 0;
}