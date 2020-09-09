#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct  t_split_quotes
{
	int         s_quote;
	int         d_quote;
	int         escaped;
}               s_split_quotes;

typedef	struct	t_command
{
				char *cmd;
				char *args;
}				s_command;

typedef struct 	s_cmd
{
	char		*pwd;
}				t_cmd;

typedef struct 	s_builtin
{
	char		**argv;
}				t_builtin;

/*
** ft_env_manager.c
*/
typedef struct	s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;
t_list			*g_env;
int				g_last_state;
t_env_var		*new_pair(char *key, char *value);
t_env_var   	*get_env_value(char *key);
void    		set_env_value(char *key, char *value);
int				init_env(char **envp);

/*
** ft_replace_env.c
*/
char			*replace_env_var(char *cmd);


int	ft_read_line(int *get, char **line);
char **ft_lexer(char *str);
char *ft_strdup(const char *s1);
int parse_echo(char *cmd, int i);
int parse_cd(char *cmd, int i);
void ft_error(char *cmd);
int ft_pwd(t_cmd *cmd, t_builtin *builtin);
int parsing(char **cmd_lexer);
void get_env(char *cmd);
int ft_env(char *cmd);
int ft_export(char *cmd, int i);
int ft_unset(char *cmd, int i);
void	ft_apply_signals(void (*signal_func)(int));
void	ft_shell_mode(int code);
void	ft_ignore_signals(void);

char   	**command_from_string(char *cmd_param);
char    *ft_isinpath(char *executable);
int     start_process(char *path, char **args, int cont);
int exec_correct(char *cmd, int cont, int (*f)(char *, char **, int));
int     simple_exec(char *path, char **args, int cont);

/*
** lexer.c functions
*/
int		is_redirection(char *str, int i);
int		is_separator(char *str, int i);
int		is_space(char *str, int i);
int		is_pipe(char *str, int i);
void	check_quotes(s_split_quotes *states, char *str, int i);
int		count_strs(char *str, int (*f)(char *, int));
int     count_from(char *str, int *i, int (*f)(char *, int));
char	**trim_tab(char **res);
void    fill_from(char **res, int j, char *str, int *i, int (*f)(char *, int));
char    **ft_split_quotes(char *str, int (*f)(char *, int));
void	*free_tab_str(char **res);

#endif