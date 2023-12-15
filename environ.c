#include "shell.h"

/**
 * _my_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int _my_env(infor_t *info)
{
	_printlist_str(info->env);
	return (0);
}

/**
 * _get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */

char *_get_env(infor_t *info, const char *name)
{
	list_str *node = info->env;
	char *p;

	while (node)
	{
		p = start_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _my_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure constaining potential arguments. Used to m,aintain
 * constant function prototype.
 * Return: Always 0
 */

int _my_setenv(infor_t *info)
{
	if (info->agc != 3)
	{
		e_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (_set_env(info, info->agv[1], info->agv[2]))
		return (0);
	return (1);
}

/**
 * _my_setenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * consta function prototype.
 * Return: Always 0
 */

int _my_setenv(infor_t *info)
{
	int indx;

	if (info->agc == 1)
	{
		e_puts("Too few arguments.\n");
		return (1);
	}
	for (indx = 1; indx <= info->argc; indx++)
		_unset_env(info, info->agv[indx]);

	return (0);
}

/**
 * populate_envlist - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int populate_envlist(infor_t *info)
{
	list_str *node = NULL;
	size_t i; i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
