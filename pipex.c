/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:37:19 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/17 16:18:08 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
void	child_process(int infile, char **argv, char **envp, int *end)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		error("Dup2(infile, STDIN_FILENO)");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error("Dup2(end[1], STDOUT_FILENO)");
	close(end[0]);
	close(infile);
	parsing_child(argv[2], envp);
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
	parsing_parent(argv[3], envp);
}
*/

void	child_one(int infile, char **argv, char **envp, int *end)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		error("Dup2(infile, STDIN_FILENO)");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error("Dup2(end[1], STDOUT_FILENO)");
	close(end[0]);
	close(infile);
	parsing(argv[2], envp);
}

void	child_two(int outfile, char **argv, char **envp, int *end)
{
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
    int		status;
    pid_t	child1;
    pid_t	child2;
    
	if (pipe(end) == -1)
		error("Pipe");
    child1 = fork();
	printf("child1 = %d\n", child1);//togli
    if (child1 < 0)
         error("Fork child1");
    if (child1 == 0)
        child_one(infile, argv, envp, end);
    child2 = fork();
	printf("child2 = %d\n", child2);//togli
    if (child2 < 0)
         error("Fork child2");
    if (child2 == 0)
        child_two(outfile, argv, envp, end);
    close(end[0]);         // this is the parent
    close(end[1]);         // doing nothing
    waitpid(child1, &status, 0);  // supervising the children
    waitpid(child2, &status, 0);  // while they finish their tasks
}

/*
void	pipex(int infile, int outfile, char **argv, char **envp)
{
	int		end[2];
	pid_t	pid;

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
*/

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc == 5)
	{
		//outfile = 0;
		//if (access(argv[1], R_OK) == -1)
			//error("Access file1");
		infile = open(argv[1], O_RDONLY);
		//if (access(argv[4], F_OK) == -1)
		outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		//else if (access(argv[4], W_OK) == -1)
			//error("Access file2");
		//else if (access(argv[4], W_OK) == 0)
			//outfile = open(argv[4], O_WRONLY | O_TRUNC);
		if (infile < 0)
			error("Open file1");
		if (outfile < 0)
			error("Open file2");
		pipex(infile, outfile, argv, envp);
	}
	else
		error("Error: bad arguments\nEx: ./pipex file1 \"cmd1\" \"cmd2\" file2\n");
	sleep(10);//togli
	return (0);
}
