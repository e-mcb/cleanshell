#include "lexer.h"

// pwd placeholder

// char *get_pwd(char **env)
// {
// 	int	i;
// 	char *pwd;

// 	i = 0;
// 	while (ft_strnstr(env[i], "PWD=", 4) == NULL)
// 		i++;
// 	return (env[i] + 4);
// }

//give the prompt back to 
//the user and sends the input back to the main
char *prompt(char **env)
{
	char *input;

		input = readline("minishell>");
		if (input == NULL)
		{
			// READLINE ERROR PLACEHOLDER
		}
		if (input[0] != '\0')
			add_history(input);		
		if (ft_has_invalid_quotes(input))
		{
			ft_putstr_fd(OPEN_QUOTES, 2);
			free(input);
			return (NULL);
		}
		return (input);
}

//function list to add to header

// ft_has_invalid_quotes(const char *str);
