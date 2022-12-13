/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2022/12/11 17:53:26 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	print_error(int i, char *arg)
{
	if (!i)
		return (0);
	if (i == -1)
	{
		if (ft_printf("Number of arguments not correct!\n") == -1)
			write(2, "Error\n", 6);
	}
	else if (i == -2)
	{
		if (ft_printf("pipex: %s: %s\n", arg, strerror(errno)) == -1)
			write(2, "Error\n", 6);
		return (1);
	}
	else if (i == -3)
	{
		if (ft_printf("pipex: %s: command not found\n", arg) == -1)
			write(2, "Error\n", 6);
		return (127);
	}
	else if (i == -4)
	{
		if (ft_printf("Malloc error!\n") == -1)
			write(2, "Error\n", 6);
		return (127);
	}
//	else if (i == 3)
//	{
//		if (ft_printf("zsh: permission denied: %s\n", arg) == -1)
//			write(2, "Error\n", 6);
//		return (1);
//	}
	return (127);
}

int	check_input(int *fd, char **argv, char **env, t_token *token)
{
	int	res;
	fd[0] = open(argv[1], O_RDWR);
	if (fd[0] == -1)
		return (print_error(-2, argv[1]));
	token[0].file  = argv[1];
	res = print_error(check_command(argv[2], env, &token[0]), argv[2]);
	if (res != 0)
		return (res);
	res = print_error(check_command(argv[3], env, &token[1]), argv[3]);
	if (res != 0)
		return (res);
	fd[1] = open(argv[4], O_RDWR | O_CREAT, 0644);
	if (fd[1] == -1)
		return (print_error(-2, argv[4]));
	token[1].file  = ft_strdup(argv[4]);
//	ft_printf("Token 0:\n\tFile: %s\n\tCmd: %s\nToken 1:\n\tFile: %s\n\tCmd: %s\n",
//			token[0].file, token[0].cmd, token[1].file, token[1].cmd);
	if (access(token[0].file, R_OK | W_OK) == -1)
		return (print_error(-2, token[0].file));
	if (access(token[1].file, R_OK | W_OK) == -1)
		return (print_error(-2, token[1].file));
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	int		fd[2];
	t_token	token[2];

	if (argc != 5)
		return (print_error(-1, NULL));
	if (check_input(fd, argv, env, token) == 0)
		return (0);
	if (run_commands(fd, token) == 0)
		return (0);
}
