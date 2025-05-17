#include "lexer.h"

// int main(int argc, char **argv, char **envp)
// {
// 	char **my_env;
// 	char *input;

// 	// my_env = ft_strdup_array(envp);
// 	// if (my_env == NULL)
// 		//PLACEHOLDER
// 	while (1)
// 	{
// 		input = prompt(my_env);
// 		if (input == NULL)
// 			return 0;
// 		free(input);
// 	}
// }

void	free_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

void ft_exit(char *input, t_shell_parsing *shell)
{
	if (input)
		free(input);
	if (shell->env)
		ft_free_str_array(shell->env);
	if (shell->splitted)
		ft_free_str_array(shell->splitted);
	if (shell->token)
		free_list(&(shell->token));
	if (shell)
		free(shell);
	exit(0);
}

void	ft_parsing(char *input, t_shell_parsing *shell)
{
	int	i;

	i = 0;
	shell->splitted = ft_split2(input, ' '); //whitespace a gerer (une fonction qui remplace un groupe de whitespace par des espaces)
	if (shell->splitted == NULL)
		ft_exit(NULL, shell);
	free (input);
	while (shell->splitted[i])
	{
		tokenizer(shell->splitted[i], &(shell->token), i);
		i++;
	}
	refine_token_type(shell->token);

}

void	init_shell(t_shell_parsing *shell, char **envp)
{
	shell->env = NULL;
	shell->splitted = NULL;
	shell->token = NULL;
}

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell_parsing *shell;
	t_token *tmp;

	shell = malloc(sizeof(t_shell_parsing));
	init_shell(shell, envp);
	shell->env = ft_strdup_array(envp);
	while (1)
	{

		input = prompt(shell->env);
		if (input == NULL)
			continue;
		if (ft_strnstr(input, "exit", 4))
			ft_exit(input, shell);
		ft_parsing(input, shell);
		tmp = shell->token;
		while (tmp)
		{
			printf("Token: %s   token type: %d\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
		ft_free_str_array(shell->splitted);
		free_list(&(shell->token));
		shell->splitted = NULL;
	}
	ft_exit(input, shell);
	return (0);
}