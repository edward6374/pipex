/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:07:09 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/17 11:31:51 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*take_string(char **split, char *cmd)
{
	int		i;
	char	*t1;
	char	*t2;

	i = -1;
	t1 = NULL;
	t2 = NULL;
	if (!split)
		exit_error(2, BASH, cmd, NOTFILEDIR);
	while (split[++i])
	{
		t1 = ft_strjoin(split[i], "/");
		if (!t1)
			exit_error(2, BASH, "malloc", MALLOCERR);
		t2 = ft_strjoin(t1, cmd);
		if (!t2)
			exit_error(2, BASH, "malloc", MALLOCERR);
		free(t1);
		if (check_access(t2))
			return (t2);
		free(t2);
	}
	exit_error(127, PIPEX, cmd, CMDNOTFOUND);
	return (NULL);
}

char	*get_full_command(char *cmd, char *env[])
{
	int		i;
	char	*tmp;
	char	**split;

	i = -1;
	split = NULL;
	if (cmd[0] == '/')
		return (check_access(cmd));
	else if (cmd[0] == '.' && cmd[1] == '/')
		return (check_access(cmd + 2));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
		{
			tmp = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			if (!tmp)
				exit_error(2, BASH, "malloc", MALLOCERR);
			split = ft_split(tmp, ':');
			free (tmp);
			break ;
		}
	}
	if (!split)
		exit_error(2, BASH, "malloc", MALLOCERR);
	return (take_string(split, cmd));
}

void	execute_child(char *file, char *cmd, char *env[], int p[2])
{
	int		fd;
	char	**all_args;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error(2, PIPEX, file, NOTFILEDIR);
	if (dup2(fd, 0) < 0 || dup2(p[1], 1) < 0)
		exit_error(2, BASH, "dup2", BADFD);
	if (close(p[0]) < 0 || close(p[1]) < 0)
		exit_error(2, BASH, "close", CNTCLOSE);
	all_args = ft_split(cmd, ' ');
	if (!all_args)
		exit_error(2, BASH, "malloc", MALLOCERR);
	if (execve(get_full_command(all_args[0], env), all_args, env) == -1)
		exit_error(2, "bash", EXECVERR, NULL);
}

void	execute_father(char *file, char *cmd, char *env[], int p[2])
{
	int		fd;
	char	**all_args;

	if (!access(file, X_OK))
		exit_error(1, PIPEX, file, PERMDEN);
	fd = open(file, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		exit_error(2, PIPEX, file, NOTFILEDIR);
	if (dup2(fd, 1) < 0 || dup2(p[0], 0) < 0)
		exit_error(2, BASH, "dup2", BADFD);
	if (close(p[0]) < 0 || close(p[1]) < 0)
		exit_error(2, BASH, "close", CNTCLOSE);
	all_args = ft_split(cmd, ' ');
	if (!all_args)
		exit_error(2, BASH, "malloc", MALLOCERR);
	if (execve(get_full_command(all_args[0], env), all_args, env) == -1)
		exit_error(2, "bash", EXECVERR, NULL);
}
