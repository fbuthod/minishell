/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 02:52:52 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/16 11:48:15 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    simple_exec(t_command *cmd)
{
    ft_printf("EXEC [%s]\n", cmd->cmd);
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
    char *tmp;

    if (!(tmp = ft_calloc(ft_strlen(arg) - 1, 1)))
    {
        free(arg);
        return (NULL);
    }
    ft_memcpy(tmp, &arg[1], ft_strlen(arg) - 2);
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
        i++;
    }
}

int         fill_args(t_command *cmd_s, char *cmd, int i)
{
    char **args;

    if (!(args = ft_split_quotes(&cmd[i], is_spaceredirection)))
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
        {
            j++;
            setup_input(args[j]);
        }
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
    if (!(fill_args(command, cmd, 0)))
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
        ft_printf("%s : command introuvale\n", cmd->cmd);
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
        ft_cd(cmd_struct);
    else if (!ft_strncmp(cmd_struct->cmd, "pwd", 4))
        ft_pwd();
    else if (!ft_strncmp(cmd_struct->cmd, "export", 7))
        ft_export(cmd_struct);
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
                free(g_cmd);
                ft_free_strs_tab(g_cmd_lexer);
                ft_free_strs_tab(g_cmd_split);
                exit(g_last_state);
            }
            else
            {
                waitpid(pid, &status, 0);
                g_last_state = 0;
                if (WEXITSTATUS(status))
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
