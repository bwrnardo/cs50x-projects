#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int soma_total = 0;
    int contador_posicao = 1;
    int conta_digitos = 0;

    long cartao = get_long("Numero: ");
    long copia = cartao;

    while (cartao > 0)
    {
        conta_digitos++;
        int digito = cartao % 10;

        if (contador_posicao % 2 == 1)
        {
            soma_total += digito;
        }
        else
        {
            digito *= 2;

            if (digito >= 10)
            {
                soma_total += digito % 10;
                soma_total += digito / 10;
            }
            else
            {
                soma_total += digito;
            }
        }
        cartao = cartao / 10;
        contador_posicao++;
    }

    if (soma_total % 10 == 0)
    {
        while (copia > 100)
        {
            copia /= 10;
        }
        if ((copia == 37 || copia == 34) && conta_digitos == 15)
        {
            printf("AMEX\n");
        }
        else if ((conta_digitos == 13 || conta_digitos == 16) && (copia >= 40 && copia <= 49))
        {
            printf("VISA\n");
        }
        else if ((copia >= 51 && copia <= 55) && conta_digitos == 16)
        {
            printf("MASTERCARD\n");
        }
        else
            printf("INVALID\n");
    }
    else
        printf("INVALID\n");
}
