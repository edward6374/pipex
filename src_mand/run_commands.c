/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/01/09 20:12:38 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	run_command(t_token *token)
{
	int		i;
	int		pid;

	i = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid != 0)
	{
		if (token->idx == 0)
		{
			close(token->pipe[0]);
			dup2(token->pipe[1], 1);
			close(token->pipe[1]);
			dup2(token->fd, 0);
			close(token->fd);
		}
		else if (token->next == NULL)
		{
			close(token->pipe[1]);
			dup2(token->pipe[0], 0);
			close(token->pipe[1]);
			dup2(token->fd, 1);
			close(token->fd);
		}
		else
		{
			dup2(token->pipe[1], 1);
			close(token->pipe[1]);
			dup2(token->fd, 0);
			close(token->fd);
		}
		if (execve(token[0].cmd, token[0].args, NULL) == -1)
		{
			perror(token[0].cmd);
			exit (127);
		}
	}
	waitpid(-1, &i, 0);
	return (0);
}

/*
int	run_command(t_token *token)
{
	int		i;
	int		p[2];
	int		pid;

	i = 0;
	if (pipe(p) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid != 0)
	{
//		argv = (char **)malloc(sizeof(char *) * 3);
//		argv[0] = token[0].cmd;
//		argv[1] = token[0].file;
//		argv[2] = NULL;
//		ft_printf("First fork:\nCmd: %s\nFile: %s\nNULL: %s\n\n", argv[0], argv[1], argv[2]);
		close(p[0]);
		dup2(p[1], 1);
		close(p[1]);
		dup2(token[0].fd, 0);
		close(token[0].fd);
		close(token[1].fd);
		if (execve(token[0].cmd, token[0].args, NULL) == -1)
		{
			perror(token[0].cmd);
			exit (127);
		}
	}
	waitpid(-1, &i, 0);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid != 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		dup2(token[1].fd, 1);
		close(token[1].fd);
		close(token[0].fd);
//		free(argv);
//		argv = (char **)malloc(sizeof(char *) * 2);
//		argv[0] = token[1].cmd;
//		argv[1] = get_output();
//		ft_printf("Argv 1: %s\n", argv[1]);
//		argv[2] = ft_strdup(">");
//		argv[3] = token[1].file;
//		argv[4] = NULL;
//		argv[1] = ft_strdup(">");
//		argv[1] = token[1].file;
//		argv[1] = NULL;
//		ft_printf("Second fork:\nCmd: %s\nFile: %s\nNULL: %s\n", argv[0], argv[1], argv[2]);
//		ft_printf("Cmd: %s\nInput: %s\nSeparator: %s\nFile: %s\nNULL: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
		if (execve(token[1].cmd, token[1].args, NULL) == -1)
		{
			perror(token[1].cmd);
			exit (127);
		}
	}
	waitpid(-1, &i, 0);
//	free(argv);
//	argv = NULL;
//	ft_printf("Command executed\n");
	return (0);
}
*/
