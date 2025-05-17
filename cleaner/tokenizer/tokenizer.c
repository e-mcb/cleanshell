/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:14:08 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/18 00:02:28 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

static void	quote_handler(const char *str, int i, t_quote_state *state)
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

static void handle_word_boundaries(int i, t_quote_state *state, t_shell *shell, t_input_context *ctx)
{
	char *tmp;

	if (ctx->str[i] != '|' && ctx->str[i] != '<'
		&& ctx->str[i] != '>' && state->w_start < 0)
		state->w_start = i;
	else if (((ctx->str[i] == '|' || ctx->str[i] == '<' || ctx->str[i] == '>')
			|| (size_t)i == ft_strlen(ctx->str))
		&& state->w_start >= 0 && state->in_quotes == false)
	{
		tmp = ft_substrword(ctx->str, state->w_start, i);
		add_token(shell, tmp, WORD, ctx->rank);
		state->w_start = -1;
		free(tmp);
	}
}


static void handle_single_operator(int i, t_shell *shell, t_input_context *ctx)
{
	char *tmp;

	tmp = ft_substrword(ctx->str, i, i + 1);
	if (ctx->str[i] == '<')
		add_token(shell, tmp, IN, ctx->rank);
	else if (ctx->str[i] == '>')
		add_token(shell, tmp, OUT, ctx->rank);
	else if (ctx->str[i] == '|')
		add_token(shell, tmp, PIPE, ctx->rank);
	free(tmp);
}


//handles the token making in case of a heredoc or append operator
//bool in order to skip an extra space in the initial string
static bool handle_double_operator(int i, t_shell *shell, t_input_context *ctx)
{
	char *tmp;

	if (ctx->str[i + 1] && ((ctx->str[i] == '<' && ctx->str[i + 1] == '<')
			|| (ctx->str[i] == '>' && ctx->str[i + 1] == '>')))
	{
		tmp = ft_substrword(ctx->str, i, i + 2);
		if (ctx->str[i] == '<')
			add_token(shell, tmp, HDOC, ctx->rank);
		else
			add_token(shell, tmp, APPEND, ctx->rank);
		free(tmp);
		return (true);
	}
	return (false);
}


void	tokenizer(t_shell *shell, int rank)
{
	int				i;
	t_quote_state	state;
	t_input_context	ctx;

	i = 0;
	ctx.str = shell->splitted[rank];
	ctx.rank = rank;
	state.w_start = -1;
	state.in_quotes = false;
	while ((size_t)i <= ft_strlen(shell->splitted[rank]))
	{
		quote_handler(shell->splitted[rank], i, &state);
		handle_word_boundaries(i, &state, shell, &ctx);
		if ((shell->splitted[rank][i] == '<' || shell->splitted[rank][i] == '>' || shell->splitted[rank][i] == '|')
			&& state.in_quotes == false)
		{
			if (handle_double_operator(i, shell, &ctx))
				i++;
			else if (shell->splitted[rank][i] == '<' || shell->splitted[rank][i] == '>' || shell->splitted[rank][i] == '|')
				handle_single_operator(i, shell, &ctx);
		}
		i++;
	}
}
