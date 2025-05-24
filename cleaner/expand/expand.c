#include "../headers/lexer.h"

// int main(void)
// {
// 	char *input = "Salut_$USER$SHLVL$USER";
// 	char **parsed = split_and_expand(input);
// 	char	*expended = join_chars(parsed);

// 	for (int i = 0; parsed[i]; i++)
// 		printf("'%s'\n", parsed[i]);

// 	for (int i = 0; parsed[i]; i++)
// 		free(parsed[i]);
// 	printf("la chaine finale: %s\n", expended);
// 	free(parsed);
// 	free(expended);
// 	return 0;
// }

t_token	*new_token_append(t_token *head, char *str, t_token_type type)
{
	t_token *new_node;
	t_token *last;

	new_node = create_token(str);
	if (!new_node)
		return (NULL);
	new_node->type = type;

	if (!head)
		return new_node;

	last = head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return head;
}

void	insert_new_nodes(t_token *token, char **splitted)
{
	int	i;
	t_token	*tmp;
	
	i = 1;
	tmp = token;
	token->next = NULL;
	ft_strlcpy(token->value, splitted[0], ft_strlen(splitted[0]));
	while (splitted[i])
	{
		if(new_token_append(token, splitted[i], tmp->type))
			//malloc error
		i++;
	}
	while (token->next != NULL)
		token = token->next;
	token->next = tmp->next;
}

void	replace_token_with_nodes(t_shell *shell, t_token *prev, t_token *current, char **splitted)
{
	t_token	*new_head;
	t_token	*new_tail;
	t_token	*new_node;
	int		i;

	i = 0;
	new_head = NULL;
	new_tail = NULL;
	while (splitted[i])
	{
		new_node = new_token_append(NULL, splitted[i], current->type); // your helper
		if (!new_node)
		{
			return;
			//malloc error
		}
		if (!new_head)
			new_head = new_tail = new_node;
		else
		{
			new_tail->next = new_node;
			new_tail = new_node;
		}
		i++;
	}	
	if (new_tail)
		new_tail->next = current->next;
	if (prev)
		prev->next = new_head;
	else
		shell->token = new_head;
	free(current->value);
	free(current);
}

void	expand(t_shell *shell)
{
	t_token	*tmp;
	t_token	*prev;
	char	*expanded;
	char	**splitted;

	prev = NULL;
	tmp = shell->token;
	while (tmp)
	{
		if (ft_strchr(tmp->value, '$'))
		{
			printf("Before expansion: %s\n", tmp->value);
			expanded = join_chars(split_and_expand(tmp->value));
			printf("After expansion: %s\n", expanded);
			splitted = ft_split2(expanded, ' ');
			if (tmp->type == FILEN && count_strings(splitted) > 1)
			{
				fprintf(stderr, "Ambiguous redirect: %s\n", expanded);
				ft_free_str_array(splitted);
				free(expanded);
				return;
			}
			replace_token_with_nodes(shell, prev, tmp, splitted);
			if (prev != NULL)
				tmp = prev->next;
			else
				tmp = shell->token;
			ft_free_str_array(splitted);
			free(expanded);
			continue;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

// char *expand (t_shell *shell)
// {
// 	t_token	tmp;


// }

// token->value = join_chars(split_and_expand(token->value))