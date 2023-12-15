#include "shell.h"

/**
 * strn_cpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */

char *str_ncpy(char *dest, char *src, int n)
{
	int indx, j;
	char *s = dest;

	i = 0;
	while (src[indx] != '\0' && indx < n - 1)
	{
		dest[indx] = src[indx];
		indx++;
	}
	if (indx < n)
	{
		j = indx;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * strn_cat - conatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */

char *str_cat(char *s, char c)
{
	int indx, j;
	char *s = dest;

	indx = 0;
	j = 0;
	while (dest[indx] != '\0')
		indx++;
	while (src[j] != '\0' && j < n)
	{
		dest[indx] = src[j];
		indx++;
		j++;
	}
	if (j < n)
		dest[indx] = '\0';
	return (s);
}

/**
 * str_chr - locates a character in a string
 * @s: the string to be parsed
 * @c: the chharacter to look for
 * Return: (s) a pointer to the memory area s
 */

char *str_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while(*s++ != '\0');

	return (NULL);
}
