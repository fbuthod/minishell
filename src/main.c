/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 22:55:41 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/09 12:58:50 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int ac, char **av, char *envp[])
{
    char    *cmd;
    char    **cmd_split;
    //char    **cmd_lexer;
    int     i;
    //int     j;

    ac = 0;
    av = 0;
    init_env(envp);
    g_last_state = 0;
    while(1)
    {
        ft_apply_signals(&ft_shell_mode);
        ft_printf("minishell : ");
        if (get_next_line(0, &cmd) == 0)
        {
            ft_printf("exit\n");
            free(cmd);
            exit(0);
        }

        i = -1;
        cmd = replace_env_var(cmd);
        cmd_split = ft_split_quotes(cmd, is_separator);
        while (cmd_split[++i])
            if (ft_strncmp(cmd_split[i], ";", 2) != 0)
            {
                ft_printf("[%s]\n", cmd_split[i]);
                //cmd_lexer = get_command_list(cmd_split[i]);
                /*if (cmd_lexer)
                {
                    j = -1;
                    while (cmd_lexer[++j])
                        ;
                    free_tab_str(cmd_lexer);
                }*/
            }
        free_tab_str(cmd_split);
        free(cmd);
    }
}

/*
** TODO: Fonction pour check si > < >> dans une liste
** TODO: Fonction qui lexe et trie les commandes
** TODO: Add $? dans le replace
*/