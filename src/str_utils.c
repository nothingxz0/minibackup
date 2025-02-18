/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:56:36 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 10:08:39 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i += 1;
	return (i);
}

int	str_in(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			return (true);
		i += 1;
	}
	return (false);
}

int	str_cmp(char *str_1, char *str_2)
{
	int	i;

	i = 0;
	while (str_1[i] != 0 && str_2[i] != 0 && str_1[i] == str_2[i])
		i += 1;
	if (str_1[i] == str_2[i])
		return (true);
	return (false);
}

char	*str_join(char *str_1, char *str_2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(str_len(str_1) + str_len(str_2) + 1);
	if (str == NULL)
		return (free(str_1), free(str_2), NULL);
	while (str_1[i] != 0)
	{
		str[i] = str_1[i];
		i += 1;
	}
	while (str_2[j])
		str[i++] = str_2[j++];
	str[i] = 0;
	return (free(str_1), free(str_2), str);
}

void	str_cpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i += 1;
	}
}
