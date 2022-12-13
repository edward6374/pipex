/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:24 by vduchi            #+#    #+#             */
/*   Updated: 2022/12/13 14:59:57 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*get_output(void)
{
	int		bits;
	char	*line;
	char	*res;

	bits = 1;
	res = (char *)malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	line = (char *)malloc(sizeof(char) * 51);
	if (!line)
	{
		free(res);
		return (NULL);
	}
	line[0] = '\0';
	while (bits)
	{
		bits = read(0, line, 50);
		if (bits == -1)
		{
			free(line);
			free(res);
			return (NULL);
		}
		line[bits] = '\0';
		res = ft_strjoin(res, line);
		if (!res)
		{
			free(line);
			return (NULL);
		}
	}
	free(line);
	return (res);
}

int	run_commands(int *fd, t_token *token)
{
	int		i;
	int		p[2];
	int		pid;
	char	**argv;

	i = fd[0];
	if (pipe(p) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid != 0)
	{
		argv = (char **)malloc(sizeof(char *) * 3);
		argv[0] = token[0].cmd;
		argv[1] = token[0].file;
		argv[2] = NULL;
		ft_printf("First fork:\nCmd: %s\nFile: %s\nNULL: %s\n\n", argv[0], argv[1], argv[2]);
		close(p[0]);
		dup2(p[1], 1);
		close(p[1]);
//		ft_printf("Input: %d\n", p[1]);
		execve(argv[0], argv, NULL);
	}
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid != 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		free(argv);
		argv = (char **)malloc(sizeof(char *) * 5);
		argv[0] = token[1].cmd;
//		argv[1] = get_output();
//		ft_printf("Argv 1: %s\n", argv[1]);
//		argv[2] = ft_strdup(">");
//		argv[3] = token[1].file;
//		argv[4] = NULL;
		argv[1] = ft_strdup(">");
		argv[2] = token[1].file;
		argv[3] = NULL;
//		ft_printf("Second fork:\nCmd: %s\nSeparator: %s\nFile: %s\nNULL: %s\n", argv[0], argv[1], argv[2], argv[3]);
//		ft_printf("Cmd: %s\nInput: %s\nSeparator: %s\nFile: %s\nNULL: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
		execve(argv[0], argv, NULL);
	}
	free(argv);
	argv = NULL;
	ft_printf("Command executed\n");
	return (1);
}
