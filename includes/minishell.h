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
	char		*cmd;
	char		*next;
	char		**args;
}				t_command;

typedef struct	s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;

/*
** builtins
*/
void			ft_env();
void			ft_pwd();
void 			ft_cd(t_command *cmd);
void    		ft_exit(t_command *cmd);
void    		ft_echo(t_command *cmd);
void    		ft_unset(t_command *cmd);
void    		ft_export(t_command *cmd);

/*
** ft_env_manager.c
*/
t_list			*g_env;
int				g_last_state;
int				g_in;
int				g_out;
char    		*g_cmd;
char			**g_cmd_split;
char			**g_cmd_lexer;
t_env_var		*new_pair(char *key, char *value);
t_env_var   	*get_env_value(char *key);
void    		set_env_value(char *key, char *value);
void        	remove_env_value(char *key);
int				init_env(char **envp);
int	    		exec_command_list(char **cmd_list);
char       		**env_to_tab();
t_boolean 		check_exit(char *cmd_list);
char        	**ft_remove_void_elem(char **args);

/*
** ft_file_descriptor_manager.c
*/
void			setup_input(char *cmd_lexer);
void			setup_output(char *redirect, char *cmd);
void			reset_fd(int save[2]);

/*
**	ft_commands_utils.c
*/
t_command		*get_current(t_list *head);
t_command		*get_right(t_list *head);
t_command		*get_left(t_list *head);
t_boolean   	is_str(char *str, char *red);

/*
** ft_replace_env.c
*/
char			*replace_env_var(char *cmd);

/*
** ft_sinals.c functions
*/
void			ft_shell_mode(int code);
void			ft_apply_signals(void (*signal_func)(int));

/*
** ft_lexer.c functions
*/
char			**ft_lexer(char *str, int (*f)(const char *, int));
int				is_spaceredirection(const char *str, int i);
int				is_redirection(const char *str, int i);
int				is_separator(const char *str, int i);
int				is_space(const char *str, int i);
int				is_equal(const char *str, int i);
int				is_pipe(const char *str, int i);
int				is_pipe_redirection(const char *str, int i);
void			check_quotes(t_split_quotes *states, const char *str, int i);
int				count_strs(const char *str, int (*f)(const char *, int));
int     		count_from(char *str, int *i, int (*f)(const char *, int));
char			**trim_tab(char **res);
void    		fill_from(char **res, int j, char *str, int *i, int (*f)(const char *, int));
char    		**ft_split_quotes(char *str, int (*f)(const char *, int));
void			*free_tab_str(char **res);

#endif