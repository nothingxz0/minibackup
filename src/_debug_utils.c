/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:38:43 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 09:39:51 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	_print_tokens(t_token *token)
{
	while (token != NULL)
	{
		printf("type: %d, value: %s\n", token->type, token->value);
		token = token->next;
	}
}
