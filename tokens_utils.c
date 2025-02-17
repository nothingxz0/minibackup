/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:28:58 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/17 15:28:59 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extract_tokens.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (*tokens == NULL)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
}

t_token	*new_token(t_type type, char *value, t_token *tokens)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
	{
		free_tokens(tokens);
		exit(1);
	}
	new->type = type;
	new->next = NULL;
	new->value = value;
	return (new);
}

t_token	*last_token(t_token *lst)
{
	t_token	*pr;

	pr = NULL;
	while (lst)
	{
		pr = lst;
		lst = lst->next;
	}
	return (pr);
}

char	*str_join(char *s1, char *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc((str_len(s1) + str_len(s2) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	return (free(s1), s);
}

int	str_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] - s2[i] == 0)
		return (1);
	return (0);
}
