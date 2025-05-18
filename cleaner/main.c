#include "headers/lexer.h"

void	ft_parsing(char *input, t_shell *shell)
{
	int	i;

	i = 0;
	shell->splitted = ft_split2(input, ' '); //whitespace a gerer (une fonction qui remplace un groupe de whitespace par des espaces)
	if (shell->splitted == NULL)
		ft_exit(NULL, shell);
	free (input);
	while (shell->splitted[i])
	{
		tokenizer(shell, i);
		i++;
	}
	ft_free_str_array(shell->splitted); //no longer need that once the tokens have been created
	refine_token_type(shell->token);
	//expand here
	//refine for cmds and args
	shell->splitted = NULL;
}

t_shell	*init_shell(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		ft_exit(NULL, NULL);
	shell->env = NULL; //environment array
	shell->splitted = NULL; // array gotten from splitting the input
	shell->token = NULL; // list of token created from the input
	shell->env = ft_strdup_array(envp);
	if (shell->env == NULL)
		ft_exit(NULL, shell);
	return (shell);
}

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell *shell;

	(void)argc;
	(void)argv;
	shell = NULL;
	 // structure holding the variables needed all around the parser
	shell = init_shell(shell, envp); // initializes the shell structure that holds multiple variables needed all around the parser
 // duplicates the env from envp to be used as our own (Need to look into minishell being launched with no env)
	//dans le cas de minishell dans minishell, pas besoin de faire cette copie
	while (1) // loop to have a lasting minishell
	{
		input = prompt(shell); //readline and history manager
		if (input == NULL)
			continue;
		ft_parsing(input, shell); //splits the input gotten from readline then creates token in order to make the execution easier
		// Exec around here
		free_list(&(shell->token));//frees the list of token in order to get ready for the next input
	}
	return (0);
}

