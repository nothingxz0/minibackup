/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:41:58 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 09:43:10 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_type	get_quote_type(char c)
{
	if (c == '\'')
		return (WORD_SQUOTES);
	if (c == '\"')
		return (WORD_DQUOTES);
	return (-1);
}

t_type	get_double_type(char *ptr)
{
	if (str_len(ptr) >= 2 && ptr[0] == '|' && ptr[1] == '|')
		return (OR);
	if (str_len(ptr) >= 2 && ptr[0] == '&' && ptr[1] == '&')
		return (AND);
	if (str_len(ptr) >= 2 && ptr[0] == '>' && ptr[1] == '>')
		return (APPEND);
	if (str_len(ptr) >= 2 && ptr[0] == '<' && ptr[1] == '<')
		return (HEREDOC);
	return (-1);
}

t_type	get_single_type(char *ptr)
{
	if (*ptr == '|')
		return (PIPE);
	if (*ptr == '<')
		return (REDIR_IN);
	if (*ptr == '>')
		return (REDIR_OUT);
	if (*ptr == '(')
		return (LEFT_P);
	if (*ptr == ')')
		return (RIGHT_P);
	return (-1);
}
