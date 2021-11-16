/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:37:19 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:26:13 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int infile, char **argv, char **envp, int *end)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		error("Dup2(infile, STDIN_FILENO)");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error("Dup2(end[1], STDOUT_FILENO)");
	close(end[0]);
	close(infile);
	parsing(argv[2], envp);
}

void	parent_process(int outfile, char **argv, char **envp, int *end)
{
	int	status;

	waitpid(-1, &status, 0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error("Dup2(outfile, STDOUT_FILENO)");
	if (dup2(end[0], STDIN_FILENO) == -1)
		error("Dup2(end[0], STDIN_FILENO)");
	close(end[1]);
	close(outfile);
	parsing(argv[3], envp);
}

void	pipex(int infile, int outfile, char **argv, char **envp)
{
	int		end[2];
	pid_t	pid;

	pipe(end);
	if (pipe(end) == -1)
		error("Pipe");
	pid = fork();
	if (pid < 0)
		error("Fork");
	if (!pid)
		child_process(infile, argv, envp, end);
	else
		parent_process(outfile, argv, envp, end);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (infile < 0)
			error("Open file1");
		if (outfile < 0)
			error("Open file2");
		pipex(infile, outfile, argv, envp);
	}
	else
		error("Error: bad arguments\nEx: ./pipex file1 \"cmd1\" \"cmd2\" file2\n");
	return (0);
}
