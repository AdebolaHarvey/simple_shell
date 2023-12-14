#include "shell.h"

/**
 * e_puts - Prints a string.
 * @s: Pointer to the string to be printed.
 * Return: Nothing.
 */
void e_puts(char *s)
{
	int indx = 0;

	if (!s)
		return;
	while (s[indx] != '\0')
	{
		e_putchar(s[indx]);
		indx++;
	}
}

/**
 * e_putchar - Writes the character ch to stderr.
 * @ch: Character to be printed.
 * Return: 1  on success.
 * On error, -1 is returned and errno is set appropriately.
 */
int e_putchar(char ch)
{
	static int indx;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || indx >= WRITE_BUFF_SIZE)
	{
		write(2, buff, indx);
		indx = 0;
	}
	if (ch != BUFF_FLUSH)
		buff[indx++] = ch;
	return (1);
}




