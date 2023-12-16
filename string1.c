#include "shell.h"

/**
 * str_cpy - Copies string.
 * @des: Destination.
 * @src: Source.
 * Return: The pointer to destination.
 */
char *str_cpy(char *des, char *src)
{
	int indx = 0;

	if (des == src || src == 0)
		return (des);
	while (src[indx])
	{
		des[indx] = src[indx];
		indx++;
	}
	des[indx] = 0;
	return (des);
}

/**
 * str_dupl - Duplicates strings.
 * @strn: String to be duplicated.
 * Return: Pointer to duplivated string.
 */
char *str_dupl(const char *strn)
{
	int len = 0;
	char *retn;

	if (strn == NULL)
		return (NULL);
	while (*strn++)
		len++;
	retn = malloc(sizeof(char) * (len + 1));
	if (!retn)
		return (NULL);
	for (len++; len--;)
		retn[len] = *--strn;
	return (retn);
}

/**
 * put_s - Prints an input string.
 * @strn: Input string to be printed.
 * Return: Nothing.
 */
void put_s(char *strn)
{
	int indx = 0;

	if (!strn)
		return;
	while (strn[indx] != '\0')
	{
		put_char(strn[indx]);
		indx++;
	}
}

/**
 * put_char - Writes character ch to stdout.
 * @ch: Charater to print.
 * Return: 1 (succes),
 * On error, -1 is returned and errno is set appropriately.
 */
int put_char(char ch)
{
	static int indx;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || indx >= WRITE_BUFF_SIZE)
	{
		write(1, buff, indx);
		indx = 0;
	}
	if (ch != BUFF_FLUSH)
		buff[indx] = ch;
	return (1);
}

