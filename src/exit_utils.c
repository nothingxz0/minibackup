/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:40:10 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 09:17:14 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

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
