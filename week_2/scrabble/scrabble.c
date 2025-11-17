#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                         'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

string make_uppercase(string s);
int sum_of_points(string input);
void check_winner(int p1, int p2);

int main(void)
{
    int p1_points = 0;
    int p2_points = 0;

    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    make_uppercase(player1);
    make_uppercase(player2);

    p1_points = sum_of_points(player1);
    p2_points = sum_of_points(player2);

    check_winner(p1_points, p2_points);
}

int sum_of_points(string input)
{
    int points = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (input[i] == ALPHABET[j])
            {
                points += POINTS[j];
                break;
            }
        }
    }
    return points;
}

string make_uppercase(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        s[i] = toupper(s[i]);
    }
    return s;
}

void check_winner(int p1, int p2)
{
    if (p1 > p2)
    {
        printf("Player 1 wins!\n");
    }
    else if (p2 > p1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}