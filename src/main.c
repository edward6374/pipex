/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/17 11:23:55 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*check_access(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	else if (access(cmd, F_OK) == 0)
		exit (126);
	return (NULL);
}

void	exit_error(int status, char *str1, char *str2, char *str3)
{
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	exit(status);
}

int	main(int argc, char *argv[], char *env[])
{
	int	f1;
	int	p[2];

	if (argc != 5)
		exit_error(2, "bash", INVARGS, NULL);
	if (pipe(p) == -1)
		exit_error(2, "bash", ERRPIPE, NULL);
	f1 = fork();
	if (f1 == -1)
		exit_error(2, "bash", ERRFORK, NULL);
	if (f1 == 0)
		execute_child(argv[1], argv[2], env, p);
	execute_father(argv[4], argv[3], env, p);
	return (0);
}
