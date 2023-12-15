#include "shell.h"

/**
 * gethistory_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *gethistory_file(infor_t *info)
{
	char *buf, *dir;

	dir = _get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, dir);
	str_cat(buf, "/");
	str_cat(buf, HISTORY_FILE);
	return (buf);
}

/**
 * _writehistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int _writehistory(infor_t *info)
{
	ssize_t fd;
	char *filename = gethistory_file(info);
	list_str *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->hist; node; node = node->next)
	{
		fd_puts(node->str, fd);
		fd_put('\n', fd);
	}
	fd_put(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int _read_history(infor_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gethistory_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!stat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_historylist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_historylist(info, buf + last, linecount++);
	free(buf);
	info->hist_count = linecount;
	while (info->hist_count-- >= HISTORY_MAX)
		del_node_at_index(&(info->hist), 0);
	re_number_history(info);
	return (info->hist_count);
}

/**
 * build_historylist - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_historylist(infor_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->hist)
		node = info->hist;
	add_node_end(&node, buf, linecount);

	if (!info->hist)
		info->hist = node;
	return (0);
}

/**
 * re_number_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int re_number_history(infor_t *info)
{
	list_t *node = info->hist;
	int i = 0;

	while (node)
	{
		node->numb = i++;
		node = node->next;
	}
	return (info->hist_count = i);
}
