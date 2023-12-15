#include "shell.h"

/**
 * h_sh - Shell loop.
 * @inf: Parameter and return information struct.
 * @agv: Arguement vector.
 * Return: 0 (success), 1 (error).
 */

int h_sh(infor_t *inf, char **agv)
{
	ssize_t rtn = 0;
	int b_rtn = 0;

	while (rtn != -1 && b_rtn != -2)
	{
		clear_info(inf);
		if (
