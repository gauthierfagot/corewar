/*
** EPITECH PROJECT, 2023
** my strlen
** File description:
** display the number of character of a string
*/

int my_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        i = i + 1;
    }
    return (i);
}
