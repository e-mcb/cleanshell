/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:27:35 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/18 14:16:37 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lexer.h"

//gives the prompt back to 
//the user and sends the input back to the main
char *prompt(t_shell *shell)
{
	char *input;

		input = readline("minishell>"); //writes minishell everytime the prompt is given (could maybe do something with pwd in the future)
		if (input == NULL)
		{
			ft_putstr_fd("Goodbye\n", 2);
			ft_exit(NULL, shell);
		}
		if (input[0] != '\0')//empty string does not get added to the history
			add_history(input);		
		if (ft_has_invalid_quotes(input))//look for any unclosed quotes and displays an error message if one is found
		{
			ft_putstr_fd(OPEN_QUOTES, 2);
			free(input);
			return (NULL);
		}
		return (input);
}

//function list to add to header

