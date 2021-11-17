/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:28:31 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/17 16:14:19 by cfiliber         ###   ########.fr       */
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
	//perror("sleep");//togli
	//sleep(60);//togli
	if (access(path, X_OK) == 0)
		execve(path, cmd_args, envp);
	free(path);
	//perror("sleep");//togli
	//sleep(10);//togli
}

/*
void	execute_parent(char *paths, char **cmd_args, char **envp)
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

void	parsing_child(char *argv, char **envp)
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
		execute_child(paths[i], cmd_args, envp);
		i++;
	}
	error("Execve child");
}
*/

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
	//sleep(10);//togli
	i = 0;//togli
	while (paths && paths[i])//togli
	{//togli
		free(paths[i]);//togli
		i++;//togli
	}//togli
	free(paths);//togli
	i = 0;//togli
	while (cmd_args && cmd_args[i])//togli
	{//togli
		free(cmd_args[i]);//togli
		i++;//togli
	}//togli
	free(cmd_args);//togli
	sleep(20);//togli
	error("Access cmd");//if execve succeeds, program does not do this
}
