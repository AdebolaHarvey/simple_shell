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

/**
 * fd_put - Writes the ch character to fd.
 * @ch: The character to print.
 * @f: File descriptor to write to.
 * Return: 1 (success).
 * On error, -1 is returned and errno is set appropriately.
 */
int fd_put(char ch, int f)
{
	static int indx;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || indx >= WRITE_BUFF_SIZE)
	{
		write(f, buff, indx);
		indx = 0;
	}
	if (ch != BUFF_FLUSH)
		buff[indx++] = ch;
	return (1);
}

/**
 * fd_puts - Prints an input string.
 * @st: A pointer of the string to be printed.
 * @f_d: File descriptor to be printed.
 * Return: Number of string to be printed.
 */
int fd_puts(char *st, int f_d)
{
	int indx = 0;

	if (!st)
		return (0);
	while (*st)
	{
		indx += fd_put(*st++, f_d);
	}
	return (indx);
}
