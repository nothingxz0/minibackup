/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:49:04 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/17 15:31:12 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extract_tokens.h"

t_bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

t_bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

t_bool	in(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}

t_bool	is_double(char *ptr)
{
	return ((str_len(ptr) >= 2 && ptr[0] == '|' && ptr[1] == '|')
		|| (str_len(ptr) >= 2 && ptr[0] == '&' && ptr[1] == '&')
		|| (str_len(ptr) >= 2 && ptr[0] == '>' && ptr[1] == '>')
		|| (str_len(ptr) >= 2 && ptr[0] == '<' && ptr[1] == '<'));
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
	return (0);
}

t_type get_single_type(char *ptr)
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
	return (0);
}

t_token	*extract_double(char **ptr)
{
	t_token	*new;
	char	*value;

	value = malloc(3);
	if (value == NULL)
		exit(1); // we need to handle this error later
	value[0] = (*ptr)[0];
	value[1] = (*ptr)[1];
	value[2] = 0;
	new = new_token(get_double_type(*ptr), value, NULL);
	*ptr += 2;
	return (new);
}

t_token *extract_single(char **ptr)
{
	t_token	*new;
	char	*value;
	t_type	type;

	value = malloc(2);
	if (value == NULL)
		exit(1); // we need to handle this error later
	value[0] = **ptr;
	value[1] = 0;
	type = get_single_type(*ptr);
	new = new_token(type, value, NULL);
	*ptr += 1;
	return (new);
}

t_bool	is_single(char *ptr)
{
	return (in(*ptr, "|<>()"));
}

t_bool	is_word(char c)
{
	return (!is_space(c) && !is_single(&c)
		&& !is_double(&c) && !is_quote(c));
}

t_type	quote_type(char c)
{
	if (c == '\'')
		return (WORD_SQUOTES);
	if (c == '\"')
		return (WORD_DQUOTES);
	return (0);
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

t_token	*extract_quote(char **ptr)
{
	t_token	*new;
	int		len;
	char	*value;
	char	quote;

	quote = **ptr;
	len = 0;
	*ptr += 1;
	while ((*ptr)[len] != 0 && ((*ptr)[len] != quote))
		len += 1;
	if ((*ptr)[len] == 0)
		exit(1); // we need to handle this error later
	value = malloc(len + 1);
	if (value == NULL)
		exit(1); // we need to handle this error later
	str_cpy(value, *ptr, len);
	value[len] = 0;
	new = new_token(quote_type(quote), value, NULL);
	*ptr += len + 1;
	return (new);
}

t_token	*extract_word(char **ptr)
{
	t_token	*new;
	int		len;
	char	*value;

	len = 0;
	while ((*ptr)[len] != 0 && !is_space((*ptr)[len])
		&& !is_single(*ptr + len) && !is_double(*ptr + len)
		&& !quote_type((*ptr)[len]))
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

void	two_consecutive_op(t_token *ftoken)
{
	t_token	*token;

	token = ftoken;
	while (token)
	{
		if (token && check_type(token->value) && token->next && check_type(token->next->value))
		{
			printf("minishell: syntax error near unexpected token \'%s\'\n", token->next->value);
			free_tokens(ftoken);
			exit(1);
		}
		else if (token && check_type(token->value) && token->next == NULL)
		{
			printf("minishell: syntax error near unexpected token \'%s\'\n", token->value);
			free_tokens(ftoken);
			exit(1);
		}
		token = token->next;
	}
}

void	check_for_error(t_token *ftoken)
{
	check_parenthese(ftoken);
	two_consecutive_op(ftoken);
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
		else if (quote_type(*str))
			add_token(&ftoken, extract_quote(&str));
		else if (is_word(*str) && is_quote(*(str - 1)))
			last_token(ftoken)->value = str_join(last_token(ftoken)->value, extract_word(&str)->value);
		else
			add_token(&ftoken, extract_word(&str));
	}
	check_for_error(ftoken);
	return (ftoken);
}


void	print_tokens(t_token *ftoken)
{
	t_token	*token;

	token = ftoken;
	while (token != NULL)
	{
		printf("type: %d, value: %s\n", token->type, token->value);
		token = token->next;
	}
}

#include <readline/readline.h>
int main()
{
	while (1)
	{
		char *buffer = readline("Enter a command: ");
		t_token *ftoken = extract_tokens(buffer);
		print_tokens(ftoken);
		printf("\n");
	}
	return (0);
}