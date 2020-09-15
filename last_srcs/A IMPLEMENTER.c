/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A IMPLEMENTER.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 21:06:55 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/12 02:36:29 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>

void    loop_pipe(char ***cmd) 
{
    int   p[2];
    pid_t pid;
    int   fd_in = 0;

    while (*cmd != NULL)
    {
        pipe(p);
        if ((pid = fork()) == -1)
        {
          exit(1);
        }
        else if (pid == 0)
        {
            dup2(fd_in, 0); //change the input according to the old one 
            if (*(cmd + 1) != NULL)
                dup2(p[1], 1);
            close(p[0]);
            execvp((*cmd)[0], *cmd);
            exit(1);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            fd_in = p[0]; //save the input for the next command
            cmd++;
        }
    }
}

int main()
{
    /*

    {cat < test | grep toto | grep t}

    [cat main.c > test < test]
    [|]
    { [grep pipe], [|], [wc -l], [|], [wc -l], [|], [wc -l], [|], [wc -l], [|], [wc -l] }
    [|]
    [cat main.c > test < test]
    [|]
    { [grep pipe], [|], [wc -l] }

    echo "test" | grep "test"

    */
/*

    int echo(char *name, char **args)
    {
        (void)name;
    }

    ls[0], ls
    "ls", {"ls", "-l", "-a"}

    /bin/cat

*/
  char *ls[] = {"cat", "main.c", NULL};
  char *grep[] = {"grep", "pipe", NULL};
  char *wc[] = {"wc", "-l", NULL};
  char **cmd[] = {ls, grep, wc, NULL};

  loop_pipe(cmd);
  return (0);
}

