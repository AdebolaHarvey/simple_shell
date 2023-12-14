#include "shell.h"

/**
 * str_len - Returns the strength of a string.
 * @str: Pointer to string length.
 *
 * Return: Integer value.
 */
int str_len(char *str)
{
	int indx = 0;

	if (!str)
		return (0);

	while (*str++)
		indx++;
	return (indx);
}

/**
 * str_cmp - Compares two strings lexicographically.
 * @str1: First string.
 * @str2: Second string.
 * Return: Positive (str1 > str2), negative
 * (str1 < str2), zero (str1 == str2)
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}


/**
 * start_with - checks code.
 * @hstk: String to search.
 * @ndle: Substring to search.
 * Return: Char value or NULL
 */
char *start_with(const char *hstk, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hstk++)
			return (NULL);
	return ((char *)hstk);
}

/**
 * str_cat - Concatenates two strings.
 * @des: Destination buffer.
 * @sc: Source buffer.
 * Return: Pointer to destination buffer.
 */
char *str_cat(char *des, char *sc)
{
	char *r = des;

	while (*des)
		des++;
	while (*sc)
		*des++ = *sc++;
	*des = *sc;
	return (r);
}
