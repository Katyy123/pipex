/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:29:59 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/17 15:24:06 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"

/* pipex.c */
int		main(int argc, char **argv, char **envp);
void	pipex(int infile, int outfile, char **argv, char **envp);
void	child_one(int infile, char **argv, char **envp, int *end);
void	child_two(int outfile, char **argv, char **envp, int *end);

/* execute.c */
void	parsing(char *argv, char **envp);
void	execute(char *paths, char **cmd_args, char **envp);

/* error.c */
void	error(const char *str);

#endif
