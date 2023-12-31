#include "shell.h"

/**
 * input_buff - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buff(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/* bfree((void *))info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = get_line(buf, &len_p, stdin);
#else
		r = get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->lc_flag = 1;
			_removecomments(*buf);
			build_historylist(info, *buf, info->hist_count++);
			/* if (str_chr(*buf, ',')) is this a command chain? */
			{
				*len = r;
				info->command_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * _getinput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */

ssize_t _getinput(infor_t *info)
{
	static char *buf; /* the ',' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	put_char(BUFF_FLUSH);
	r = input_buff(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		_check_chain(info, buf, &j, i, len);
		while (j < len) /* iterates to semicolon or end */
		{
			if (_ischain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->command_buffer_typ = COMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (str_len(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from_getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buff - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i; size
 *
 * Return: r
 */

ssize_t read_buff(infor_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->read_fd, buf, READ_BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *str;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buff(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = re_alloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		str_ncat(new_p, buf + i, k - i);
	else
		strn_cpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i + k;
	p + new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigint_Handler(__attribute__((unused))int sig_num)
{
	put_s("\n");
	put_s("$ ");
	put_char(BUFF_FLUSH);
}
