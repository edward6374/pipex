/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 01:21:50 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/19 17:11:40 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		count;
	char	*str;

	i = 0;
	j = 0;
	count = -1;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	str = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	while (++count < (i + j))
	{
		if (count < i)
			str[count] = s1[count];
		else
			str[count] = s2[count - i];
	}
	str[count] = '\0';
	return (str);
}
