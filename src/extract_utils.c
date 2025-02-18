/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:13:26 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 10:01:50 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_token	*extract_word(char **ptr)
{
	t_token	*new;
	int		len;
	char	*value;

	len = 0;
	while ((*ptr)[len] != 0 && !is_space((*ptr)[len])
		&& !is_single(*ptr + len) && !is_double(*ptr + len)
		&& !is_quote((*ptr)[len]))
		len += 1;
	value = malloc(len + 1);
	if (value == NULL)
		exit(1); // we need to handle this error later
	str_cpy(value, *ptr, len);
	value[len] = 0;
	new = new_token(WORD, value, NULL);
	*ptr += len;
	return (new);
}

t_token	*extract_quote(char **ptr)
{
	int		len;
	char	quote;
	char	*value;
	t_token	*token;

	len = 0;
	quote = **ptr;
	*ptr += 1;
	while ((*ptr)[len] != 0 && ((*ptr)[len] != quote))
		len += 1;
	if ((*ptr)[len] == 0)
		wexit("Error: quote not closed", 1); // we need to handle this error later
	value = malloc(len + 1);
	if (value == NULL)
		wexit("Error: malloc(1) failled", 1); // we need to handle this error later
	str_cpy(value, *ptr, len);
	value[len] = 0;
	token = new_token(get_quote_type(quote), value, NULL);
	*ptr += len + 1;
	return (token);
}

t_token	*extract_single(char **ptr)
{
	t_type	type;
	char	*value;
	t_token	*token;

	value = malloc(2);
	if (value == NULL)
		wexit("Error: malloc(1) failled", 1); // we need to handle this error later
	value[0] = **ptr;
	value[1] = 0;
	type = get_single_type(*ptr);
	token = new_token(type, value, NULL);
	*ptr += 1;
	return (token);
}

t_token	*extract_double(char **ptr)
{
	char	*value;
	t_token	*token;

	value = malloc(3);
	if (value == NULL)
		wexit("Error: malloc(1) failled", 1); // we need to handle this error later
	value[0] = (*ptr)[0];
	value[1] = (*ptr)[1];
	value[2] = 0;
	token = new_token(get_double_type(*ptr), value, NULL);
	*ptr += 2;
	return (token);
}
