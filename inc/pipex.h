/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/17 11:36:02 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include "../libft/libft.h"

# define BASH "bash: "
# define PIPEX "pipex: "
# define CNTOPEN ": Cannot open"
# define CMDNOTFOUND ": command not found"
# define CNTCLOSE ": Fd can not be closed"
# define PERMDEN ": Permission denied"
# define BADFD ": Bad file descriptor"
# define ERRPIPE ": error creating pipe"
# define ERRFORK ": error creating fork"
# define NOTFILEDIR ": No such file or directory"
# define INVARGS ": Invalid number of arguments"
# define MALLOCERR ": error trying to allocate memory"
# define EXECVERR ": error on execve"

char	*check_access(char *cmd);
void	exit_error(int status, char *str1, char *str2, char *str3);
void	execute_child(char *file, char *cmd, char *env[], int p[2]);
void	execute_father(char *file, char *cmd, char *env[], int p[2]);

#endif
