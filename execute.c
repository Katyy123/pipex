/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:28:31 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:23:10 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *paths, char **cmd_args, char **envp)
{
	char	*path;
	char	*part_path;

	part_path = ft_strjoin(paths, "/");
	if (!part_path)
		error("Strjoin part_path");
	path = ft_strjoin(part_path, cmd_args[0]);
	if (!path)
		error("Strjoin path");
	free(part_path);
	execve(path, cmd_args, envp);
	free(path);
}

void	parsing(char *argv, char **envp)
{
	char	**cmd_args;
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		error("Split paths");
	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)
		error("Split cmd_args");
	i = 0;
	while (paths[i])
	{
		execute(paths[i], cmd_args, envp);
		i++;
	}
	error("Execve");
}
