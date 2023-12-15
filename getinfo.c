#include "shell.h"

/**
 * _clearinfo - initializes info_t struct
 * @info: struct address
 */

void _clearinfo(infor_t *info)
{
	info->ag = NULL;
	info->agv = NULL;
	info->path = NULL;
	info->agc = 0;
}

/**
 * _setinfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */

void _setinfo(info_t *info, char **av)
{
	int i = 0;

	info->file_name = agv[0];
	if (info->agv)
	{
		info->agv = str_tow(info->, " \t");
		if (!info->agv)
		{
			info->agv = malloc(sizeof(char *) * 2);
			if (info->agv)
			{
				info->agv[0] = str_dupl(info->ag);
				info->agv[1] = NULL;
			}
		}
		for (i = 0; info->agv && info->agv[i]; i++)

			info->agc = i;

		repl_alias(info);
		replace_var(info);
	}
}

/**
 * _freeinfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */

void _freeinfo(infor_t *info, int all)
{
	f_free(info->agv);
	info->agv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->ag);
		if (info->envr)
			free_list(&(info->envr));
		if (info->history)
			free_list(&(info->hist));
		if (info->alias)
			_freelist(&(info->alias));
		ffree(info->envirn);
		info->envirn = NULL;
		builtin_free((void **)info->command_buffer);
		if (info->read_fd > 2)
			close(info->read_fd);
		put_char(BUFF_FLUSH);
	}
}
