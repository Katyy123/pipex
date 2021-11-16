/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:29:59 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:40:01 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define EXIT_FAILURE -1
# define EXIT_SUCCESS 0

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"

/* pipex.c */
int		main(int argc, char **argv, char **envp);
void	pipex(int infile, int outfile, char **argv, char **envp);
void	child_process(int infile, char **argv, char **envp, int *end);
void	parent_process(int outfile, char **argv, char **envp, int *end);

/* execute.c */
void	parsing(char *argv, char **envp);
void	execute(char *paths, char **cmd_args, char **envp);

/* error.c */
void	error(const char *str);

#endif
