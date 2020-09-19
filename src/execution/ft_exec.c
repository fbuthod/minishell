/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 02:52:52 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 02:14:16 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char        *apply_escape(char *str)
{
    int i;
    int j;
    int count;
    char *res;

    i = -1;
    count = 0;
    while (str[++i])
        if (str[i] == '\\' && i++)
            count++;
    if (!(res = ft_calloc(ft_strlen(str) - count + 1, 1)))
        return (NULL);
    i = -1;
    j = -1;
    while (str[++i])
        if (str[i] == '\\' && i++)
            res[++j] = str[i];
        else
            res[++j] = str[i];
    free(str);
    return (res);
}

int         fill_command(t_command *cmd_s, char *cmd)
{
    int i;

    i = 0;
    while (cmd[i] && cmd[i] != ' ')
        i++;
    if (!(cmd_s->cmd = ft_calloc(i + 1, 1)))
        return (-1);
    ft_memcpy(cmd_s->cmd, cmd, i);
    return (i);
}

char        **ft_remove_void_elem(char **args)
{
    char **res;
    int count;
    int i;
    int j;

    i = -1;
    count = 0;
    while (args[++i])
        if (!is_str(args[i], ""))
            count++;
    if (!(res = ft_calloc(count + 1, sizeof(char *))))
    {
        free_tab_str(args);
        return (NULL);
    }
    i = -1;
    j = 0;
    while (args[++i])
        if (!is_str(args[i], ""))
        {
            res[j] = ft_strdup(args[i]);
            j++;
        }
    ft_free_strs_tab(args);
    return (res);
}

t_boolean   check_valid_command(char **cmd)
{
    int i;

    i = 0;
    if (cmd && is_redirection(cmd[0], 0))
        return (FALSE);
    if (cmd)
        while (cmd[i + 1])
        {
            if (is_redirection(cmd[i], 0) && is_redirection(cmd[i + 1], 0))
                return (FALSE);
            i++;
        }
    if (cmd && is_redirection(cmd[i], 0))
        return (FALSE);
    return (TRUE);
}

char        *ft_remove_quotes(char *arg)
{
    t_split_quotes state;
    char *tmp;
    int i;

    i = -1;
    state.d_quote = 0;
    state.s_quote = 0;
    state.escaped = 0;
    while (((arg[++i] == '\"' && arg[ft_strlen(arg) - i - 1] == '\"') || (!state.d_quote && arg[i] == '\'' && arg[ft_strlen(arg) - i - 1] == '\'')))
        check_quotes(&state, arg, i);
    if ((i >= (int)ft_strlen(arg) - i - 1))
        tmp = ft_strdup("");
    else
    {
        if (!(tmp = ft_calloc(ft_strlen(arg) - i, 1)))
        {
            free(arg);
            return (NULL);
        }
        ft_memcpy(tmp, &arg[i], ft_strlen(arg) - i * 2);
    }
    free(arg);
    return (tmp);
}

void        trim_quotes(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        if ((args[i][0] == '\"' && args[i][ft_strlen(args[i]) - 1] == '\"') ||
            (args[i][0] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\''))
            args[i] = ft_remove_quotes(args[i]);
        args[i] = apply_escape(args[i]);
        i++;
    }
}

int         fill_args(t_command *cmd_s, char *cmd)
{
    char **args;

    if (!(args = ft_split_quotes(cmd, is_spaceredirection)))
        return (FALSE);
    trim_tab(args);
    args = ft_remove_void_elem(args);
    if (!check_valid_command(args))
    {
        ft_printf("Parsing error\n");
        return (FALSE);
    }
    trim_quotes(args);
    cmd_s->args = args;
    return (TRUE);
}

char        **fd_parser(char **args)
{
    int i;
    int j;
    int count;
    char **res;

    i = -1;
    count = 0;
    while (args[++i])
        if (is_str(args[i], ">") || is_str(args[i], ">>") || is_str(args[i], "<"))    
            count += 2;
    i -= count;
    if (!(res = ft_calloc(i + 1, sizeof(char *))))
        return (NULL);
    j = -1;
    i = -1;
    while (args[++j])
        if (is_str(args[j], ">") || is_str(args[j], ">>"))
        {
            setup_output(args[j], args[j + 1]);
            j++;
        }
        else if (is_str(args[j], "<"))
            setup_input(args[++j]);
        else
            res[++i] = ft_strdup(args[j]);
    ft_free_strs_tab(args);
    return (res);
}

t_command   *make_command(char *cmd)
{
    t_command   *command;
    int         i;

    if (!(command = malloc(sizeof(t_command))))
        return (NULL);
    if ((i = fill_command(command, cmd)) < 0)
        return (ft_free_return(command) ? NULL : NULL);
    if (!(fill_args(command, cmd)))
    {
        free(command->cmd);
        free(command);
        return (NULL);
    }
    command->args = fd_parser(command->args);
    return (command);
}

char    *ft_isinpath(char *executable)
{
    struct stat buf;
    char **tmp_path;
    char *complete_path;
    int i;

    i = 0;
    if (stat(executable, &buf) >= 0)
        return (ft_strdup(executable));
    if (get_env_value("PATH"))
    {
        tmp_path = ft_split(get_env_value("PATH")->value, ':');
        while (tmp_path[i])
        {
            complete_path = ft_strjoin(tmp_path[i], "/");
            complete_path = ft_strfjoin(complete_path, executable, 1);
            if (stat(complete_path, &buf) >= 0)
            {
                free_tab_str(tmp_path);
                return (complete_path);
            }
            free(complete_path);
            i++;
        }
        free_tab_str(tmp_path);
    }
    return (NULL);
}

void    exec_system(t_command *cmd)
{
    char *path;
    char **tmp_env;

    if ((path = ft_isinpath(cmd->cmd)))
    {
        tmp_env = env_to_tab();
        if (execve(path, cmd->args, tmp_env) == -1)
        {
            free(path);
            ft_free_strs_tab(tmp_env);
            ft_printf("Execution error %s\n", path);
            g_last_state = 127;
            return ;
        }
        g_last_state = 0;
        free(path);
        ft_free_strs_tab(tmp_env);
    }
    else 
    {
        g_last_state = 127;
        ft_printf("%s : commande introuvale\n", cmd->cmd);
    }
}

void    exec_process(char *cmd)
{
    t_command *cmd_struct;

    if (!(cmd_struct = make_command(cmd)))
        return ;
    if (!ft_strncmp(cmd_struct->cmd, "echo", 5))
        ft_echo(cmd_struct);
    else if (!ft_strncmp(cmd_struct->cmd, "cd", 3))
        ;
    else if (!ft_strncmp(cmd_struct->cmd, "pwd", 4))
        ft_pwd();
    else if (!ft_strncmp(cmd_struct->cmd, "export", 7))
        ft_export(cmd_struct, TRUE);
    else if (!ft_strncmp(cmd_struct->cmd, "unset", 6))
        ft_unset(cmd_struct);
    else if (!ft_strncmp(cmd_struct->cmd, "env", 4))
        ft_env();
    else if (!ft_strncmp(cmd_struct->cmd, "exit", 5))
        ft_exit(cmd_struct);
    else
        exec_system(cmd_struct);
    ft_free_strs_tab(cmd_struct->args);
    free(cmd_struct->cmd);
    free(cmd_struct);
}

int     exec_command_list(char **cmd_list)
{
    pid_t   pid;
    int     p[2];
    int     status;
    int     fd_in = 0;
    t_command *cmd_struct;

    while (*cmd_list != NULL)
    {
        if (!is_str(*cmd_list, "|"))
        {
            pipe(p);
            if ((pid = fork()) == -1)
                exit(1);
            else if (pid == 0)
            {
                dup2(fd_in, 0);
                if (*(cmd_list + 1) != NULL)
                    dup2(p[1], 1);
                close(p[0]);
                exec_process((*cmd_list));
                if (g_in > 0)
                    close(g_in);
                if (g_out > 0)
                    close(g_out);
                exit(g_last_state);
            }
            else
            {
                waitpid(pid, &status, 0);
                if (!ft_strncmp(*cmd_list, "cd ", 3) ||
                    !ft_strncmp(*cmd_list, "export ", 7) ||
                    !ft_strncmp(*cmd_list, "unset ", 6))
                {
                    cmd_struct = make_command(*cmd_list);
                    if (!ft_strncmp(cmd_struct->cmd, "cd", 3))
                        ft_cd(cmd_struct);
                    else if (!ft_strncmp(cmd_struct->cmd, "export", 6))
                        ft_export(cmd_struct, FALSE);
                    else if (!ft_strncmp(cmd_struct->cmd, "unset", 5))
                        ft_unset(cmd_struct);
                    ft_free_strs_tab(cmd_struct->args);
                    free(cmd_struct->cmd);
                    free(cmd_struct);
                }
                else
                    g_last_state = WEXITSTATUS(status);
                if (check_exit(*cmd_list))
                    return (1);
                close(p[1]);
                fd_in = p[0];
            }
        }
        cmd_list++;
    }
    return (0);
}
