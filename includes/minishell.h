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

typedef struct  s_split_quotes
{
	int         s_quote;
	int         d_quote;
	int         escaped;
}               t_split_quotes;

typedef	struct	s_command
{
				char *cmd;
				char *next;
				char **args;
}				t_command;

typedef struct	s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;

/*
** ft_env_manager.c
*/
t_list			*g_env;
int				g_last_state;
t_env_var		*new_pair(char *key, char *value);
t_env_var   	*get_env_value(char *key);
void    		set_env_value(char *key, char *value);
int				init_env(char **envp);
void			get_command_list(char *cmd);
void    		loop_pipe(t_list **head);
void    		exec_list(t_list *head);

/*
**	ft_commands_utils.c
*/
t_command    	*get_content(t_list *node);
char	    	*get_next(t_list *node);

/*
** ft_replace_env.c
*/
char			*replace_env_var(char *cmd);

/*
** ft_sinals.c functions
*/
void	ft_shell_mode(int code);
void	ft_apply_signals(void (*signal_func)(int));

/*
** ft_lexer.c functions
*/
char **ft_lexer(char *str, int (*f)(char *, int));
int		is_redirection(char *str, int i);
int		is_separator(char *str, int i);
int		is_space(char *str, int i);
int		is_pipe(char *str, int i);
int		is_pipe_redirection(char *str, int i);
void	check_quotes(t_split_quotes *states, char *str, int i);
int		count_strs(char *str, int (*f)(char *, int));
int     count_from(char *str, int *i, int (*f)(char *, int));
char	**trim_tab(char **res);
void    fill_from(char **res, int j, char *str, int *i, int (*f)(char *, int));
char    **ft_split_quotes(char *str, int (*f)(char *, int));
void	*free_tab_str(char **res);

#endif