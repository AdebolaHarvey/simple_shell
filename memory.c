#include "shell.h"

/**
 * builtin_free -Frees a pointer and NULL the add.
 * @pntr: Address of the pointer to be freed.
 * Return: 1 (free'd), otherwise 0.
 */
int builtin_free(void **pntr)
{
	if (pntr && *pntr)
	{
		free(*pntr);
		*pntr = NULL;
		return (1);
	}
	return (0);
}
