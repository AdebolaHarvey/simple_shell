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
		if (_interactive(info))
			put_s("$ ");
		e_putchar(BUFF_FLUSH);
		r = _getinput(info);
		if (r != -1)
		{
			_setinfo(info, agv);
			b_retn = _findbuiltin(info);
			if (b_rtn == -1)
				find_comd(info);
		}
		else if (_interactive(info))
			put_char('\n');
		_freeinfo(info, 0);
	}
	_writehistory(info);
	_freeinfo(info, 1);
	if (!_interactive(info) && info->stat)
		exit(info->stat);
	if (b_rtn == -2)
	{
		if (info->error_num == -1)
			exit(info->stat);
		exit(info->error_num);
	}
	return (b_rtn);
}



/**
 * find_comd - finfs a command in PATH.
 * @info: parameter and return info struct.
 * Return: .....
 */
void find_comd(infor_t *)
{
	char *path = NULL;
	int i, k;

	info->path = info->agv[0];
	if (info->lc_flag == 1)
	{
		info->lc++;
		info->lc_flag = 0;
	}
	for (i = 0, k = 0; info->ag[i]: i++)
		if (!_isdelim(info->ag[i], "\t\n"))
			k++;
	if (!k)
		return;
	path = _findpath(info, _get_env(info, "PATH="), info->agv[0]);
	if (path)
	{
		info->path = path;
		fork_comd(info);
	}
	else
	{
		if ((_interactive(info) || _get_env(info, "PATH=")
			|| info->agv[0][0] == '/') && is_comd(info, info->agv[0]))
			fork_comd(info);
		else if (*(info->ag) != '\n')
		{
			info->stat = 127;
			_printerror(info, "not found\n");
		}
	}
}


/**
 * fork_comd - ....
 * @info: ...
 * Return: ...
 */
void fork_comd(infor_t *info)
{
	pid_t child_pid;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (excve(info->path, info->agv, _get_environ(info)) == -1)
		{
			_freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->sta));
		if (WIFEXITED(info->stat))
		{
			info->stat = WEXITSTATUS(info->stat);
			if (info->stat == 126)
				_printerror(info, "Permission denied\n");
		}
	}
}
