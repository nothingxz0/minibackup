/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:40:10 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/17 10:43:44 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_utils.h"

int str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i += 1;
	return (i);
}

void	pexit(char *msg, int status)
{
	perror(msg);
	exit(status);
}

void	wexit(char *msg, int status)
{
	write(2, msg, str_len(msg));
	exit(status);
}
