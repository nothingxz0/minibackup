/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:30:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/17 15:27:02 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACT_TOKENS_H
# define EXTRACT_TOKENS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "exit_utils.h"

typedef enum e_type
{
	OR, // implemented
	AND, // implemented
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

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_token
{
	t_type			type;
	struct s_token	*next;
	char			*value;
}	t_token;

// tokens_utils.c
void		free_tokens(t_token *tokens);
void		add_token(t_token **tokens, t_token *new_token);
t_token		*new_token(t_type type, char *value, t_token *tokens);
t_token		*last_token(t_token *lst);
char		*str_join(char *s1, char *s2);
int		str_cmp(char *s1, char *s2);

#endif
