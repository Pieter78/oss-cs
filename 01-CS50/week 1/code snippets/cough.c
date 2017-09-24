#include <cs50.h>
#include <stdio.h>

void say(string s, int n);
void sneeze(int n);
void cough(int n);

int main(void)
{
    sneeze(2);
    cough(3);
}

void cough(int n)
{
    say("Cough!", n);
}

void sneeze(int n)
{
    say("Achoo!", n);
}

void say(string s, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%s\n", s);
    }
}