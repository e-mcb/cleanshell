/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:12:13 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/11 18:55:35 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static bool	is_redir(t_token *t)
{
	return (t && (t->type == IN || t->type == OUT || t->type == APPEND));
}

static bool	is_fd_case(t_token *t)
{
	return (t->next && (t->next->type == IN || t->next->type == OUT
			|| t->next->type == APPEND || t->next->type == HDOC)
		&& t->rank == t->next->rank && is_digit(t->value));
}

// void	set_word_type(t_token *t, t_token *p, bool *is_cmd)
// {
// 	if (p && is_redir(p))
// 		t->type = FILEN;
// 	else if (p && p->type == HDOC)
// 		t->type = LIMITER;
// 	else if (is_fd_case(t))
// 		t->type = FD;
// 	else if (!(*is_cmd))
// 	{
// 		t->type = CMD;
// 		*is_cmd = true;
// 	}
// 	else
// 		t->type = ARG;
// }

void	set_word_type(t_token *t, t_token *p, bool *is_cmd)
{
	if (p && is_redir(p))
		t->type = FILEN;
	else if (p && p->type == HDOC)
		t->type = LIMITER;
	else if (is_fd_case(t))
		t->type = FD;
	else
		t->type = WORD;
}

void	refine_token_type(t_token *token)
{
	t_token	*t;
	t_token	*p;
	bool	is_cmd;

	t = token;
	p = NULL;
	is_cmd = false;
	while (t)
	{
		if (t->type == PIPE)
			is_cmd = false;
		else if (t->type == WORD)
			set_word_type(t, p, &is_cmd);
		p = t;
		t = t->next;
	}
}
