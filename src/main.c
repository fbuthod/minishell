/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 22:55:41 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/18 05:40:52 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int ac, char **av, char *envp[])
{
    int     i;
    int     ret;

    ac = 0;
    av = 0;
    init_env(envp);
    g_last_state = 0;
    g_in = -1;
    g_out = -1;
    ft_apply_signals(&ft_shell_mode);
    while(1)
    {
        ft_printf("%sminishell : \033[0m", g_last_state ? "\033[1;31m" : "\033[1;32m");
        if (get_next_line(0, &g_cmd) == 0)
        {
            ft_printf("exit\n");
            free(g_cmd);
            exit(0);
        }

        i = -1;
        ret = 0;
        if (quotes_are_valid(g_cmd))
        {
            g_cmd = replace_env_var(g_cmd);
            g_cmd_split = ft_split_quotes(g_cmd, is_separator);
            while (g_cmd_split[++i])
                if (ft_strncmp(g_cmd_split[i], ";", 2) != 0)
                {
                    g_cmd_lexer = ft_lexer(g_cmd_split[i], is_pipe);
                    if (g_cmd_lexer)
                    {
                        ret = exec_command_list(g_cmd_lexer);
                        ft_free_strs_tab(g_cmd_lexer);
                    }
                    if (ret)
                        break ;
                }
            ft_free_strs_tab(g_cmd_split);
            if (ret)
                break ;
        }
        else
            ft_printf("minishell: parse error: quotes not completed\n");
        free(g_cmd);
    }
    exit(g_last_state);
}
