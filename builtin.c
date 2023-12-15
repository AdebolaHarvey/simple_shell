#include "shell.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int my_exit(infor_t *info)
{
	int exitcheck;

	if (info->agv[1]) /* if there is an exit argument */
	{
		exitcheck = err_atoi(info->agv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			_printerror(info, "illegal number: ");
			e_puts(info->agv[1]);
			e_putchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->agv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int my_cd(infor_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		put_s("TODO: >>getcwd failure emsg here<<\n");
	if (!info->agv[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should be? */
				chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_get_env(info, "OLDPWD="))
	{
		if (!_get_env(info, "OLDPWD="))
		{
			put_s(s);
			put_char('\n');
			return (1);
		}
		put_s(_get_env("OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->agv[1]);
	if (chdir_ret == -1)
	{
		_printerror(info, "can't cd to ");
		e_puts(info->agv[1]), e_putchar('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", _get_env(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * my_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int my_help(infor_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	e_puts("help call works. Function not yet implemented \n");
	if (0)
		put_s(*arg_array); /* temp att_unused workaround */
	return (0);
}
