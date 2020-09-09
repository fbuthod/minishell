# include "minishell.h"

void	ft_apply_signals(void (*signal_func)(int))
{
	signal(SIGINT, signal_func);
	signal(SIGQUIT, signal_func);
}

void	ft_shell_mode(int code)
{
	int pid;

	pid = code;
	if (code == 2)
		ft_printf("\nminishell : ");
	else if (code == 3)
		kill(pid, code);
}