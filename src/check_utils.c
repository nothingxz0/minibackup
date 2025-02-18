/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:08:13 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 09:17:09 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_single(char *ptr)
{
	return (str_in(*ptr, "|<>()"));
}

int	is_double(char *ptr)
{
	return ((str_len(ptr) >= 2 && ptr[0] == '|' && ptr[1] == '|')
		|| (str_len(ptr) >= 2 && ptr[0] == '&' && ptr[1] == '&')
		|| (str_len(ptr) >= 2 && ptr[0] == '>' && ptr[1] == '>')
		|| (str_len(ptr) >= 2 && ptr[0] == '<' && ptr[1] == '<'));
}
