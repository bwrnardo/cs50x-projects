#include <cs50.h>
#include <stdio.h>

int get_positive_int(void);
void print_row(int bricks);

int main(void)
{
    int n = get_positive_int();
    print_row(n);
}

int get_positive_int(void)
{
    int n;
    do{
        n = get_int("Height: ");
    }
    while(n < 1);
    return n;
}

void print_row(int bricks)
{
    for(int i=0; i<bricks; i++)
    {
        for(int k=bricks-1; k>i; k--)
        {
            printf(" ");
        }
        printf("#");
        for(int j=0; j<i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}


