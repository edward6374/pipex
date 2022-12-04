/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:07:09 by vduchi            #+#    #+#             */
/*   Updated: 2022/12/04 21:11:00 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	free_pointers(char **split, char *exec, int i, int out)
{
	if (split)
	{
		if (split[i])
			while (split[i])
				i++;
		while (--i >= 0)
			free(split[i]);
		free(split);
	}
	if (exec)
		free(exec);
	return (out);
}

char	*just_the_command(char *argv)
{
	int		i;
	int		count;
	char	*cmd;

	i = 0;
	count = 0;
	while (argv[i] != ' ' && argv[i] != '\0')
		i++;
	count = i;
	cmd = (char *)malloc(sizeof(char) * (i + 1));
	if (!cmd)
		return (NULL);
	i = -1;
	while (++i < count)
		cmd[i] = argv[i];
	return (cmd);
}

char	*take_path(char **split, char *argv, int i)
{
	char	*exec;
	char	*path;

	if (argv[0] != '/')
	{
		path = ft_strjoin(split[i], "/");
		if (!path)
			return (NULL);
		exec = ft_strjoin(path, argv);
		if (!exec)
			return (NULL);
		free(path);
		path = NULL;
	}
	else
	{
		exec = ft_strjoin(split[i], argv);
		if (!exec)
			return (NULL);
	}
	return (exec);
}

int	execute_path(char **split, char *argv, t_token *token)
{
	int		i;
	char	*exec;

	i = -1;
	exec = NULL;
	while (split[++i])
	{
		exec = take_path(split, argv, i);
		if (!exec)
			return (-4);
		if (access(exec, F_OK) == -1)
		{
			free(exec);
			exec = NULL;
			continue ;
		}
		else
			break ;
	}
	if (!split[i])
		return (free_pointers(split, exec, i, -3));
	token->cmd = ft_strdup(exec); 
	return (free_pointers(split, exec, i, 0));
}

int	check_command(char *argv, char *env[], t_token *token)
{
//	if (fork() != 0)
//	{
//		char	*test[] = {argv[2], argv[1], NULL};
//		if (execve(argv[2], test, NULL) == -1)
//			strerror(errno);
//	}
//	else
//	{
//		char	*test[] = {argv[2], argv[3], NULL};
//		if (execve(argv[2], test, NULL) == -1)
//			strerror(errno);
//	}
//	return (1);
	int		i;
	char	*path;
	char	**split;

	i = -1;
	path = NULL;
	split = NULL;
	while (env[++i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' &&  env[i][3] == 'H')
		{
			split = ft_split(ft_substr(env[i], 5, ft_strlen(env[i]) - 5), ':');
			break;
		}
	}
	if (!split)
		return (-4);
	i = -1;
	path = just_the_command(argv);
	if (!path)
		return (-4);
	return (execute_path(split, path, token));
}
