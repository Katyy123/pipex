/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:37:19 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/18 14:44:57 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(int infile, char **argv, char **envp, int *end)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		error("Dup2(infile, STDIN_FILENO)");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error("Dup2(end[1], STDOUT_FILENO)");
	close(end[0]);
	close(infile);
	parsing_1(argv[2], envp);
}

void	child_two(int outfile, char **argv, char **envp, int *end)
{
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error("Dup2(outfile, STDOUT_FILENO)");
	if (dup2(end[0], STDIN_FILENO) == -1)
		error("Dup2(end[0], STDIN_FILENO)");
	close(end[1]);
	close(outfile);
	parsing_2(argv[3], envp);
}

void	pipex(int infile, int outfile, char **argv, char **envp)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(end) == -1)
		error("Pipe");
	child1 = fork();
	if (child1 < 0)
		error("Fork child1");
	if (child1 == 0)
		child_one(infile, argv, envp, end);
	child2 = fork();
	if (child2 < 0)
		error("Fork child2");
	if (child2 == 0)
		child_two(outfile, argv, envp, end);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (infile < 0)
			error("Open file1");
		if (outfile < 0)
			error("Open file2");
		pipex(infile, outfile, argv, envp);
	}
	else
		error("Error: bad arguments\nusage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n");
	return (0);
}
