/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:28:58 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 09:43:28 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_token	*last_token(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	add_token(t_token **token, t_token *new_token)
{
	t_token	*tmp;

	if (*token == NULL)
	{
		*token = new_token;
		return ;
	}
	tmp = *token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
}

t_token	*new_token(t_type type, char *value, t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		free_tokens(token);
		wexit("Error: malloc(1) failled", 1); // we need to handle this error later
	}
	new_token->type = type;
	new_token->next = NULL;
	new_token->value = value;
	return (new_token);
}
