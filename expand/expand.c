#include "expand.h"

int main(void)
{
	char *input = "Salut_$USER$SHLVL$USER";
	char **parsed = split_and_expand(input);
	char	*expended = join_chars(parsed);

	for (int i = 0; parsed[i]; i++)
		printf("'%s'\n", parsed[i]);

	for (int i = 0; parsed[i]; i++)
		free(parsed[i]);
	printf("la chaine finale: %s\n", expended);
	free(parsed);
	free(expended);
	return 0;
}

// char *expand (t_shell *shell)
// {
// 	t_token	tmp;


// }

// token->value = join_chars(split_and_expand(token->value))