/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:07:09 by vduchi            #+#    #+#             */
/*   Updated: 2022/12/11 17:45:48 by vduchi           ###   ########.fr       */
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
	cmd[i] = '\0';
	return (cmd);
}

char	*take_path(char *split, char *argv)
{
	char	*cmd;
	char	*exec;
	char	*path;

	cmd = just_the_command(argv);
	if (!cmd)
		return (NULL);
	if (argv[0] != '/')
	{
		path = ft_strjoin(split, "/");
		if (!path)
			return (NULL);
		exec = ft_strjoin(path, cmd);
		if (!exec)
			return (NULL);
		free(path);
		path = NULL;
	}
	else
	{
		exec = ft_strjoin(split, cmd);
		if (!exec)
			return (NULL);
	}
	free(cmd);
	cmd = NULL;
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
		exec = take_path(split[i], argv);
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
	if (!token->cmd)
		return (free_pointers(split, exec, i, -4));
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
	char	**split;

	i = -1;
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
	return (execute_path(split, argv, token));
}
