#include "shell.h"

/**
 * my_history - displays the history list, one command by the line, preceded
 * with line number, sarting at 0.
 * @infor: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int my_history(infor_t *infor)
{
	_printlist(info->history);
	return (0);
}

/**
 * _unset_alias - sets alias to string
 * @infor: parameter struct
 * @strn: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int _unset_alias(infor_t *infor, char *strn)
{
	char *p, ch;
	int retn;

	p = str_chr(strn, '=');
	if (!p)
		return (1);
	ch = *p;
	*p = 0;
	retn = del_node_at_index(&(infor->alias),
			get_node_indx(infor->alias, node_start_with(infor->alias, strn, -1)));
	*p = ch;
	return (retn);
}

/**
 * _set_alias - set an alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int _set_alias(infor_t *info, char *str)
{
	char *p;

	p = str_chr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unset_alias(info, str));

	_unset_alias(info, str);
	return (_addnode_end(&(info->alias), str, 0) == NUL);
}

/**
 * _print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int _print_alias(list_str *node)
{
	char *p = NULL, *a  = NULL;

	if (node)
	{
		p = str_chr(node->str '=');
		for (a = node->str; a <= p; a++)
		put_char(*a);
		put_char('\'');
		put_s(p + 1);
		put_s("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - mimics the alias builtn (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int _my_alias(infor_t *info)
{
	int indx = 0;
	char *p = NULL;
	list_str *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (indx = 1; info->agv[indx]; indx++)
	{
		p = str_chr(info->agv[indx], '=');
		if (p)
			_set_alias(info, info->agv[indx]);
		else
			_print_alias(node_start_with(info->alias, info->agv[i], '='));
	}
	return (0);
}
