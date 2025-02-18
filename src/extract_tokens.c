/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:49:04 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 10:07:04 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishel.h"

int	is_word(char c)
{
	return (!is_space(c) && !is_single(&c)
		&& !is_double(&c) && !is_quote(c));
}

void	check_parenthese(t_token *ftoken)
{
	t_token	*token;
	int		parenthesis;

	token = ftoken;
	parenthesis = 0;
	while (token != NULL)
	{
		if (token->type == LEFT_P)
			parenthesis += 1;
		else if (token->type == RIGHT_P)
			parenthesis -= 1;
		token = token->next;
	}
	if (parenthesis != 0)
	{
		free_tokens(ftoken);
		printf("syntax error: unclosed parenthesis\n");
		exit(1);
	}
}

int	check_type(char *value)
{
	return (str_cmp(value, "||") || str_cmp(value, "&&")
		|| str_cmp(value, "|") || str_cmp(value, "<")
		|| str_cmp(value, ">") || str_cmp(value, ">>")
		|| str_cmp(value, "<<") || str_cmp(value, "(")
		|| str_cmp(value, ")"));
}

void	check_for_error(t_token *ftoken)
{
	check_parenthese(ftoken);
	//two_consecutive_op(ftoken);
}

t_token	*extract_tokens(char *str)
{
	t_token	*ftoken;
	char	*start;

	start = str;
	ftoken = NULL;
	while (*str != 0)
	{
		if (is_space(*str))
			str += 1;
		else if (is_double(str))
			add_token(&ftoken, extract_double(&str));
		else if (is_single(str))
			add_token(&ftoken, extract_single(&str));
		else if (start != str && is_word(*(str - 1)) && is_quote(*str))
			last_token(ftoken)->value = str_join(last_token(ftoken)->value, extract_quote(&str)->value);
		else if (is_quote(*str))
			add_token(&ftoken, extract_quote(&str));
		else if (is_word(*str) && is_quote(*(str - 1)))
		{
			last_token(ftoken)->value = str_join(last_token(ftoken)->value, extract_word(&str)->value);
		}
		else
			add_token(&ftoken, extract_word(&str));
	}
	check_for_error(ftoken);
	return (ftoken);
}


#include <readline/readline.h>
int main()
{
	while (1)
	{
		char *buffer = readline("Enter a command: ");
		t_token *ftoken = extract_tokens(buffer);
		_print_tokens(ftoken);
		printf("\n");
	}
	return (0);
}