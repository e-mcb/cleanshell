/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:14:08 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/11 17:34:56 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	quote_handler(const char *str, int i, t_quote_state *state)
{
	if (state->w_start < 0 && (str[i] == '\'' || str[i] == '\"')
		&& state->in_quotes == false)
	{
		state->in_quotes = true;
		state->opening_quote = str[i];
		state->w_start = i;
	}
	else if (state->w_start >= 0 && (str[i] == '\'' || str[i] == '\"')
		&& state->in_quotes == false)
	{
		state->in_quotes = true;
		state->opening_quote = str[i];
	}
	else if (state->w_start >= 0 && state->in_quotes == true
		&& str[i] == state->opening_quote)
		state->in_quotes = false;
}

void	handle_word_boundaries(int i, t_quote_state *state, t_token **token,
		t_input_context *ctx)
{
	char	*tmp;

	if (ctx->str[i] != '|' && ctx->str[i] != '<'
		&& ctx->str[i] != '>' && state->w_start < 0)
		state->w_start = i;
	else if (((ctx->str[i] == '|' || ctx->str[i] == '<' || ctx->str[i] == '>')
			|| i == ft_strlen(ctx->str))
		&& state->w_start >= 0 && state->in_quotes == false)
	{
		tmp = ft_substrword(ctx->str, state->w_start, i);
		add_token(token, tmp, WORD, ctx->rank);
		state->w_start = -1;
		free(tmp);
	}
}

void	handle_single_operator(int i, t_token **token, t_input_context *ctx)
{
	char	*tmp;

	tmp = ft_substrword(ctx->str, i, i + 1);
	if (ctx->str[i] == '<')
		add_token(token, tmp, IN, ctx->rank);
	else if (ctx->str[i] == '>')
		add_token(token, tmp, OUT, ctx->rank);
	else if (ctx->str[i] == '|')
		add_token(token, tmp, PIPE, ctx->rank);
	free(tmp);
}

bool	handle_double_operator(int i, t_token **token, t_input_context *ctx)
{
	char	*tmp;

	if (ctx->str[i + 1] && ((ctx->str[i] == '<' && ctx->str[i + 1] == '<')
			|| (ctx->str[i] == '>' && ctx->str[i + 1] == '>')))
	{
		tmp = ft_substrword(ctx->str, i, i + 2);
		if (ctx->str[i] == '<')
			add_token(token, tmp, HDOC, ctx->rank);
		else
			add_token(token, tmp, APPEND, ctx->rank);
		free(tmp);
		return (true);
	}
	return (false);
}

void	tokenizer(char *str, t_token **token, int rank)
{
	int				i;
	char			*tmp;
	t_quote_state	state;
	t_input_context	ctx;

	i = 0;
	ctx.str = str;
	ctx.rank = rank;
	state.w_start = -1;
	state.in_quotes = false;
	while (i <= ft_strlen(str))
	{
		quote_handler(str, i, &state);
		handle_word_boundaries(i, &state, token, &ctx);
		if ((str[i] == '<' || str[i] == '>' || str[i] == '|')
			&& state.in_quotes == false)
		{
			if (handle_double_operator(i, token, &ctx))
				i++;
			else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				handle_single_operator(i, token, &ctx);
		}
		i++;
	}
}
