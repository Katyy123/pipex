/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:37:19 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/15 19:34:15 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    child_process(int infile, char **argv, char **envp, int *end)
{
    if (dup2(infile, STDIN_FILENO) == -1)
    {
        perror("Dup2(infile, STDIN_FILENO): ");
        exit(EXIT_FAILURE);
    }
    if (dup2(end[1], STDOUT_FILENO) == -1)
    {
        perror("Dup2(end[1], STDOUT_FILENO): ");
        exit(EXIT_FAILURE);
    }
    close(end[0]);
    close(infile);
    execute(argv[2], envp);
}

void    parent_process(int outfile, char **argv, char **envp, int *end)
{
    int status;

    waitpid(-1, &status, 0);
    if (dup2(outfile, STDOUT_FILENO) == -1)
    {
        perror("Dup2(outfile, STDOUT_FILENO): ");
        exit(EXIT_FAILURE);
    }
    if (dup2(end[0], STDIN_FILENO) == -1)
    {
        perror("Dup2(end[0], STDIN_FILENO): ");
        exit(EXIT_FAILURE);
    }
    close(end[1]);
    close(outfile);
    execute(argv[3], envp);
}

void    pipex(int infile, int outfile, char **argv, char **envp)
{
    int     end[2];
    pid_t   pid;
    
    pipe(end);
    if (pipe(end) == -1)
        return (perror("Pipe: "));
    pid = fork();
    if (pid < 0)
        return (perror("Fork: "));
    if (!pid)
        child_process(infile, argv, envp, end);
    else
        parent_process(outfile, argv, envp, end);
}

int main(int argc, char **argv, char **envp)
{
	int infile;
    int outfile;

    if (argc == 5)
    {
        infile = open(argv[1], O_RDONLY);
        outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (infile < 0 || outfile < 0)
        {
            perror("Open: ");
            return (EXIT_FAILURE);
        }
        pipex(infile, outfile, argv, envp);
    }
    else
        perror("Error: bad arguments\nEx: ./pipex file1 \"cmd1\" \"cmd2\" file2\n");
    return (0);
}