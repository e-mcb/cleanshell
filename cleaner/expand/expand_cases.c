/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:29:55 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/24 20:43:55 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char	*get_env_value(const char *name)
{
	char	*value;

	value = getenv(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

void	case_double_dollar(void)
{
	ft_putstr_fd(DOUBLE_DOLLARS, 2);
	//renvoyer ce qu'il faut etc...
}

void	case_only_dollar(t_expand *ex)
{
	ex->result[ex->j++] = ft_strdup("$");
	ex->i++;
	ex->start = ex->i;
}

// void	case_question_mark(t_expand *ex, char *value)
// {
// 	value = ft_strdup("--code retour derniere commande--");//ici fonction à implémenter
// 	ex->result[ex->j++] = value;
// 	ex->i += 2;
// 	ex->start = ex->i;
// }

void	case_question_mark(t_expand *ex)
{
	char	*value;
	
	value = ft_strdup("--code retour derniere commande--");//ici fonction à implémenter
	ex->result[ex->j++] = value;
	ex->i += 2;
	ex->start = ex->i;
}

void	case_env_var(t_expand *ex, const char *input)
{
	char	*varname;
	char	*value;
	
	ex->i++;
	ex->start = ex->i;
	while (input[ex->i] && !ft_isspace(input[ex->i])
		&& input[ex->i] != '"' && input[ex->i] != '\'' && input[ex->i] != '$')
		ex->i++;
	varname = strndup_custom(input + ex->start, ex->i - ex->start);
	value = get_env_value(varname);
	ex->result[ex->j++] = value;
	free(varname);
	ex->start = ex->i;
}
