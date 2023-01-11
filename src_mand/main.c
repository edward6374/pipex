/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/01/09 20:12:35 by vduchi           ###   ########.fr       */
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

void	initialize_token(int idx, t_token *next, t_token *start)
{
	next->idx = idx;
	next->cmd = NULL;
	next->args = NULL;
	next->file = NULL;
	next->next = NULL;
	next->before = start;
}

t_token	*init_tokens(t_token *token)
{
	int		i;
	t_token	*temp;

	i = 0;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	initialize_token(0, token, NULL);
	if (pipe(token->pipe) == -1)
	{
		perror("pipe");
		free_tokens(token);
		exit(EXIT_FAILURE);
	}
	temp = token;
	while (i < 1)
	{
		temp->next = (t_token *)malloc(sizeof(t_token));
		if (!temp->next)
			return free_tokens(token);
		initialize_token(temp->idx + 1, temp->next, temp);
		temp = temp->next;
		i++;
	}
	return (token);
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

	if (access(input, F_OK | R_OK) == -1)
		return (print_error(2, input));
	token->fd = open(input, O_RDWR);
	token->file = input;
	res = print_error(check_command(command, env, token), command);
	if (res != 0)
		return (res);
	res = run_command(token);
	return (0);
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
	t_token	*token;

	if (argc != 5)
		return (print_error(1, NULL));
	token = NULL;
	token = init_tokens(token);
	res = execute_token(argv[1], argv[2], env, &token[0]);
	res = check_input(argv, env, token);
	if (res != 0)
		return (res);
//	res = run_commands(token);
//	if (res != 0)
//		return (res);
	return (0);
}
