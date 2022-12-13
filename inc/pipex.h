/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2022/12/11 19:44:57 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "../ft_printf/include/ft_printf.h"

typedef struct s_token
{
	int		len;
	char	*cmd;
	char	*file;
	char	**args;
}		t_token;

/* ---		Check_command.c		--- */
//char	*just_the_command(char *argv);
int		check_command(char *argv, char *env[], t_token *token);

/* ---		Run_command.c		--- */
int		run_commands(int *fd, t_token *token);

#endif
