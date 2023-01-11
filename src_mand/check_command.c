/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:07:09 by vduchi            #+#    #+#             */
/*   Updated: 2023/01/09 20:12:35 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**update_args(char *exec, char **args)
{
	int		i;
	char	**res;

	i = 0;
	while(args[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		if (i == 0)
			res[i] = ft_strdup(exec);
		else
			res[i] = ft_strdup(args[i]);
		if (!res[i])
			return (free_double_ret_char(res, i));
	}
	res[i] = NULL;
	return (res);
}

int	take_path(char *split, char *input, char **args, t_token *token)
{
	char	*exec;

	if (input[0] != '/')
		exec = ft_strjoin(ft_strjoin(split, "/"), input);
	else
		exec = ft_strjoin(split, input);
	if (!exec)
		return (-1);
	if (access(exec, F_OK) == -1)
	{
		free(exec);
		exec = NULL;
		return (0);
	}
	token->cmd = exec; 
	token->args = update_args(exec, args);
	if (!token->args)
		return (free_double_ret_int(args, 0, 3));
	free_double_ret_char(args, 0);
	exec = NULL;
	return (1);
}

int	execute_path(char **split, char *argv, t_token *token)
{
	int		i;
	int		res;
	char	**args;

	i = -1;
	args = ft_split(argv, ' ');
	if (!args)
		return (free_double_ret_int(split, 0, 4));
	while (split[++i])
	{
		res = take_path(split[i], args[0], args, token);
		if (res == -1)
			return (free_double_ret_int(split, i, 4));
		else if (res == 0)
			continue ;
		else
			break;
	}
	if (!split[i])
		return (free_double_ret_int(split, i, 3));
	return (free_double_ret_int(split, i, 0));
}

int	check_command(char *argv, char *env[], t_token *token)
{
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
		return (4);
	return (execute_path(split, argv, token));
}
