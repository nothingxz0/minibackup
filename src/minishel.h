/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:14:32 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/18 09:44:26 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

// Librairies
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

// Enums
typedef enum e_type
{
	OR,
	AND,
	PIPE,
	WORD,
	SPACE,
	APPEND,
	LEFT_P,
	RIGHT_P,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	WORD_SQUOTES,
	WORD_DQUOTES,
}	t_type;

// Structures
typedef struct s_token
{
	t_type			type;
	struct s_token	*next;
	char			*value;
}	t_token;

// check_utils.c
int		is_quote(char c);
int		is_space(char c);
int		is_single(char *ptr);
int		is_double(char *ptr);

// exit_utils.c
void	pexit(char *msg, int status);
void	wexit(char *msg, int status);

// str_utils.c
int		str_len(char *str);
int		str_in(char c, char *str);
int		str_cmp(char *str_1, char *str_2);
char	*str_join(char *str_1, char *str_2);
void	str_cpy(char *dest, char *src, int len);

// extract_utils.c
t_token	*extract_word(char **ptr);
t_token	*extract_quote(char **ptr);
t_token	*extract_single(char **ptr);
t_token	*extract_double(char **ptr);

// tokens_utils.c
t_token	*last_token(t_token *token);
void	free_tokens(t_token *token);
void	add_token(t_token **token, t_token *new_token);
t_token	*new_token(t_type type, char *value, t_token *token);

// type_utils.c
t_type	get_quote_type(char c);
t_type	get_double_type(char *ptr);
t_type	get_single_type(char *ptr);

// _debug_utils.c
void	_print_tokens(t_token *token);

#endif
