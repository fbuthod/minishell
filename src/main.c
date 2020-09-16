/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 22:55:41 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/16 03:26:07 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int ac, char **av, char *envp[])
{
    char    *cmd;
    char    **cmd_split;
    char    **cmd_lexer;
    int     i;
    int     ret;

    ac = 0;
    av = 0;
    init_env(envp);
    g_last_state = 0;
    g_in = -1;
    g_out = -1;
    while(1)
    {
        ft_apply_signals(&ft_shell_mode);
        ft_printf("%sminishell : \033[0m", g_last_state ? "\033[1;31m" : "\033[1;32m");
        if (get_next_line(0, &cmd) == 0)
        {
            ft_printf("exit\n");
            free(cmd);
            exit(0);
        }

        i = -1;
        ret = 0;
        cmd = replace_env_var(cmd);
        cmd_split = ft_split_quotes(cmd, is_separator);
        while (cmd_split[++i])
            if (ft_strncmp(cmd_split[i], ";", 2) != 0)
            {
                cmd_lexer = ft_lexer(cmd_split[i], is_pipe);
                if (cmd_lexer)
                {
                    ret = exec_command_list(cmd_lexer);
                    free_tab_str(cmd_lexer);
                }
                if (ret)
                    break ;
            }
        free_tab_str(cmd_split);
        free(cmd);
        if (ret)
            break ;
    }
    exit(g_last_state);
}
