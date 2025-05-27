#include "../headers/lexer.h"

// int main(void)
// {
// 	char *input = "Salut_$USER,$SHLVL$USER";
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
	return (head);
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

void	ft_print_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return ;
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
			// ft_print_array(split_and_expand(tmp->value));
			expanded = join_chars(split_and_expand(tmp->value));
			printf("After expansion: %s\n", expanded);
			splitted = split_keep_separators(expanded, is_whitespace);
			ft_print_array(splitted);
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

// void *ft_realloc_array(void *ptr, size_t old_count, size_t new_count, size_t elem_size)
// {
//     void *new_ptr = malloc(new_count * elem_size);
//     if (!new_ptr)
//         return (NULL);
//     if (ptr)
//     {
//         ft_memcpy(new_ptr, ptr, old_count * elem_size);
//         free(ptr);
//     }
//     return (new_ptr);
// }


char **split_keep_separators(const char *s, bool (*is_sep)(char))
{
    char    **res;
    size_t  i;
    size_t  start;
    size_t  count;
    size_t  capacity;
    char    *chunk;

	i = 0;
	start = 0;
	count = 0;
	capacity = 4;
    res = malloc(sizeof(char *) * capacity);
    if (!res)
        return (NULL);
    while (s[i])
    {
        while (s[i] && is_sep(s[i]))
            i++;
        while (s[i] && !is_sep(s[i]))
            i++;
        while (s[i] && is_sep(s[i]))
            i++;
        chunk = ft_substr(s, start, i - start);
        if (!chunk)
            return (NULL);
        if (count + 1 >= capacity)
        {
            capacity *= 2;
            char **new_res = malloc(sizeof(char *) * capacity);
            if (!new_res)
                return NULL;
            ft_memcpy(new_res, res, sizeof(char *) * count);
            free(res);
            res = new_res;
        }
        res[count++] = chunk;
        start = i;
    }
    if (res)
        res[count] = NULL;
    return (res);
}


