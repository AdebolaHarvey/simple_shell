#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

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
 * @lc_flag: Line count of input.
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
	int lc_flag;
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
int fd_put(char ch, int f);
int fd_puts(char *st, int f_d);

/* memory.c */
int builtin_free(void **pntr);

/* string.c */
int str_len(char *str);
int str_cmp(char *str1, char *str2);
char *start_with(const char *hstk, const char *ndle);
char *str_cat(char *des, char *sc);

/* string.c */
char *str_cpy(char *des, char *src);
char *str_dupl(const char *strn);
void put_s(char *strn);
int put_char(char ch);

/* builtin1.c */
int my_history(infor_t *infor);
int _unset_alias(infor_t *infor, char *strn);
int _set_alias(infor_t *info, char *str);
int _print_alias(list_str *node);
int _my_alias(infor_t *info);

/* exit.c */
char *str_ncpy(char *dest, char *src, int n);
char *str_chr(char *s, char c);
char *str_chr(char *s, char c);

/* biultin.c */
int my_exit(infor_t *info);
int my_cd(info_t *);
int my_help(info_t *);

/* get1line.c */
ssize_t _getinput(infor_t *);
int get_line(infor_t *, char **, size_t *);
void sigint_Handler(int);
ssize_t input_buff(info_t *info, char **buf, size_t *len);
ssize_t read_buff(infor_t *info, char *buf, size_t *i);

/* getinfo.c */
void _clearinfo(infor_t *);
void _setinfo(infor_t *, char **);
void _freeinfo(infor_t *, int);

/* environ.c */
char *_get_env(infor_t *, const char *);
int _my_env(infor_t *);
int _my_setenv(infor_t *);
int _populate_env_list(infor_t *);
int populate_envlist(info_t *);

/* getenv.c */
char **_get_environ(infor_t *);
int _unset_env(infor_t *, char *);
int _set_env(infor_t *, char *, char *);

/* history.c */
char *gethistory_file(infor_t *info);
int _writehistory(infor_t *info);
int _read_history(infor_t *info);
int build_historylist(infor_t *info, char *buf, int linecount);
int re_number_history(infor_t *info);

/* lists.c */
list_str *_addnode(list_str **, const char *, int);
list_str *_addnode_end(list_str **, const char *, int);
size_t _print_list_str(const list_str *);
int del_node_at_index(list_str **, unsigned int);
void _freelist(list_str **);

/* list1.c */
size_t list_lenght(const list_str *);
char **list_to_string(list_str *);
size_t _printlist(const list_str *);
list_str *node_start_with(list_str *, char *, char);
ssize_t get_node_indx(list_str *, list_str *);

/* vars.c */
int _ischain(infor_t *, char *, size_t *);
void _check_chain(infor_t *, char *, size_t *, size_t, size_t);
int repl_alias(infor_t *);
int replace_var(infor_t *);
int _replacestring(char **, char *);

/* shell_loop.c */
int h_sh(infor_t *, char **);
int _findbuiltin(infor_t *);
void find_comd(infor_t *);
void fork_comd(infor_t *);

/* parser.c */
int is_comd(infor_t *, char *);
char *duplicate_chars(char *, int, int);
char *_findpath(info_t *, char *, char *);

/* loopsh.c */
int loop_hsh(char **);

/* tokenizer */
char **str_tow(char *, char *);
char **strtow2(char *, char);
void f_free(char **);
void *re_alloc(void *, unsigned int, unsigned int);

/* realloc.c */
char *_mem_set(char *, char, unsigned int);

/* atoi.c */
int _interactive(infor_t *);
int _isdelim(char, char *);
int _is_alpha(int);
int is_atoi(char *);

/* errors1.c */
int err_atoi(char *);
void _printerror(infor_t *, char *);
int print_dp(int, int);
char *_convertnumber(long int, int, int);
void _removecomments(char *);



#endif /* SHELL_H */
