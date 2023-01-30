/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/01/30 17:35:24 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_error_out(int mode, char *arg)
{
	if (mode)
		write(2, "pipex: ", 7);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (mode == 2)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
}

void	init_tokens(t_token *token)
{
	token[0].idx = 0;
	token[0].cmd = NULL;
	token[0].args = NULL;
	token[0].file = NULL;
	token[0].before = NULL;
	token[0].next = &token[1];
	if (pipe(token[0].pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	token[1].idx = 1;
	token[1].cmd = NULL;
	token[1].args = NULL;
	token[1].file = NULL;
	token[1].before = &token[0];
	token[1].next = NULL;
	if (pipe(token[1].pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	print_error(int i, char *arg)
{
	if (!i)
		return (0);
	if (i == 1)
	{
		if (ft_printf("Number of arguments not correct!\n") == -1)
			write(2, "Error\n", 6);
	}
	else if (i == 2)
	{
		ft_error_out(2, arg);
		return (1);
	}
	else if (i == 3)
	{
		ft_error_out(1, arg);
		ft_error_out(0, "command not found");
	}
	else if (i == 4)
	{
		if (ft_printf("Malloc error!\n") == -1)
			write(2, "Error\n", 6);
	}
	return (127);
}

int	execute_token(char *input, char *command, char *env[], t_token *token)
{
	int	res;

	if (token->idx == 0)
	{
		if (access(input, F_OK | R_OK) == -1)
			return (print_error(2, input));
		token->fd = open(input, O_RDWR);
	}
	else
		token->fd = open(input, O_RDWR | O_CREAT, 0644);
	token->file = input;
	res = print_error(check_command(command, env, token), command);
	if (res != 0)
		return (res);
	res = run_command(token);
//	ft_printf("Res here: %d\n", res);
	return (res);
}

int	check_input(char **argv, char *env[], t_token *token)
{
	int	res;

	if (access(argv[1], F_OK) == -1)
		print_error(2, argv[1]);
	if (access(argv[1], R_OK) == -1)
		return (print_error(2, argv[1]));
	token[0].fd = open(argv[1], O_RDWR);
	token[0].file = argv[1];
	res = print_error(check_command(argv[2], env, &token[0]), argv[2]);
	if (res != 0)
		return (res);
	res = print_error(check_command(argv[3], env, &token[1]), argv[3]);
	if (res != 0)
		return (res);
	token[1].fd = open(argv[4], O_RDWR | O_CREAT, 0644);
	if (token[1].fd == -1)
		return (print_error(2, argv[4]));
	token[1].file = argv[4];
//	ft_printf("Token 0:\n\tFile: %s\n\tCmd: %s\nToken 1:\n\tFile: %s\n\tCmd: %s\n",
//			token[0].file, token[0].cmd, token[1].file, token[1].cmd);
//	if (access(token[0].file, R_OK | W_OK) == -1)
//		return (print_error(2, token[0].file));
//	if (access(token[1].file, R_OK | W_OK) == -1)
//		return (print_error(2, token[1].file));
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	int		res;
	t_token	token[2];

	if (argc != 5)
		return (print_error(1, NULL));
	init_tokens(token);
	res = execute_token(argv[1], argv[2], env, &token[0]);
	res = execute_token(argv[4], argv[3], env, &token[1]);
//	res = check_input(argv, env, token);
//	ft_printf("Res: %d\n", res);
	if (res != 0)
		return (res);
//	res = run_commands(token);
//	if (res != 0)
//		return (res);
	return (0);
}
