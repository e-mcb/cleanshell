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

void	init_shell(t_shell *shell)
{
	shell->env = NULL; //environment array
	shell->splitted = NULL; // array gotten from splitting the input
	shell->token = NULL; // list of token created from the input
}

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell *shell;

	(void)argc;
	(void)argv;

	shell = malloc(sizeof(t_shell)); // structure holding the variables needed all around the parser
	init_shell(shell); // initializes the shell structure that holds multiple variables needed all around the parser
	shell->env = ft_strdup_array(envp); // duplicates the env from envp to be used as our own (Need to look into minishell being launched with no env)
	while (1) // loop to have a lasting minishell
	{

		input = prompt(shell->env); //readline and history manager
		if (input == NULL)
			continue;
		if (ft_strnstr(input, "exit", 4)) //temporary function to cleanly exit the shell with no valgrind error, will probably be kept in order to cleanly exit the program in case of a malloc error
			ft_exit(input, shell);
		ft_parsing(input, shell); //splits the input gotten from readline then creates token in order to make the execution easier
		// Exec around here
		free_list(&(shell->token));//frees the list of token in order to get ready for the next input
	}
	return (0);
}

