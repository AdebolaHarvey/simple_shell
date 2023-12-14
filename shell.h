#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unstid.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

void my_print(const char *string);

/* to read or write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* to command chains */
#define COMD_NORM	0
#define COMD_OR		1
#define COMD_AND	2
#define COMD_CHAIN	3

/* to convert number() */
#define CONVRT_LOWERCASE	1
#define CONVRT_UNSIGNED		2

/* 1 if using system getline() */
#define GETLINE	0
#define STROK	0

#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **envirn;

/**
 * struct liststr - Singly linked list.
 * @numb: Number of field.
 * @strn: String.
 * @next: Next node.
 */

typedef struct liststr
{
	int numb;
	char *strn;
	struct liststr *next;
} list_str;

/**
 * struct passinfo - Pseudo-arguments passed into function.
 * @ag: String generated from getline containing arguements.
 * @agv: Arguement vector.
 * @path: Route to current command.
 * @agc: Arguement count.
 * @lc: Error count.
 * @error_num: Error code for exit.
 * linc_flag: Line count of input.
 * @file_name: Program file name.
 * @envr: Copy of local linked list environment.
 * @envirn: Custom modified copy of environ.
 * @hist: History node.
 * @alias: Alias node.
 * @en_change: If environment was changed.
 * @stat: Last executed command.
 * @command_buffer: Pointer to commander buffer.
 * @command_buffer_typ: Command type (||, &&, ;).
 * @read_fd: Input line to be read.
 * @hist_count: History count.
 */
typedef struct passinfo
{
	char *ag;
	char **agv;
	char *path;
	int agc;
	unsigned int lc;
	int error_num;
	int linc_flag;
	char *file_name;
	list_str *envr;
	list_str *hist;
	list_str *alias;
	char **envirn;
	int en_change;
	int stat;

	char **command_buffer; /* memory management */
	int command_buffer_typ; /* ||, &&, ; */
	int read_fd;
	int hist_count;
} infor_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - Contains builtin string and
 * related function.
 * @typ: Builtin command flag.
 * @function: Function in builtin.
 */
typedef struct builtin
{
	char *typ;
	int (*function)(infor_t *);
} b_table;

/* errors.c */
void e_puts(char *s);
int e_putchar(char ch);



#endif /* SHELL_H */
