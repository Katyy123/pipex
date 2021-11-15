/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:28:31 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/15 19:34:17 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    execute(char *argv, char **envp)
{
    char **paths;
    char **cmd_args;
    char *path;
    char *cmd;
    int i;

    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;
    paths = ft_split(envp[i] + 5, ':');//proteggere split, mettendo perror e exit
    cmd_args = ft_split(argv, ' ');
    i = 0;
    while (paths[i])
{
    path = ft_strjoin(paths[i], "/");
    cmd = ft_strjoin(path, cmd_args);
    free(path);
    //vedere se e dove aggiungere access
    //aggiungere cose scritte sul quad dopo while nella pag della funzione parsing, a partire da execve
    i++;
}
