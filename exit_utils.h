/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:40:08 by slasfar           #+#    #+#             */
/*   Updated: 2025/02/17 10:43:38 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_UTILS_H
# define EXIT_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// exit_utils.c
int		str_len(char *str);
void	pexit(char *msg, int status);
void	wexit(char *msg, int status);

#endif
