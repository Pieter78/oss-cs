#include <stdio.h>
#include <cs50.h>

// this doesn't work, check it
#include "structs.c"

#define STUDENTS 3

int main(void)
{
    student students[STUDENTS];

    for (int i = 0; i < STUDENTS; i++)
    {
        printf("name: ");
        students[i].name = get_string();

        printf("dorm: ");
        students[i].dorm = get_string();
    }

    // write file (1:47 in cs50)

}