#include "lexer.h"

int	ft_strsize(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_free_str_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_strdup_array(char **src)
{
	int		size;
	int		i;
	char	**dst;

	size = ft_strsize(src);
	dst = malloc(sizeof(char *) * (size + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (--i >= 0)
				free(dst[i]);
			free(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	ft_print_array(char **str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return ;
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_starts_or_ends_with_pipe(const char *str)
{
	const char	*end;

	if (!str)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '|')
		return (1);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;
	if (*end == '|')
		return (1);
	return (0);
}

int	ft_has_invalid_quotes(const char *str)
{
	int		i;
	bool	in_quotes;
	char	opening_quote;

	i = 0;
	in_quotes = false;
	opening_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (!in_quotes)
			{
				in_quotes = true;
				opening_quote = str[i];
			}
			else if (str[i] == opening_quote)
				in_quotes = false;
		}
		i++;
	}
	return (in_quotes);
}

char *ft_remove_wrapping_quotes(const char *str)
{
	int		i;
	int		j;
	bool	in_quotes;
	char	quote;
	char	*result;

	i = 0;
	j = 0;
	in_quotes = false;
	quote = 0;
	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote = str[i];
			}
			else if (str[i] == quote)
			{
				in_quotes = false;
				quote = 0;
			}
			else
				result[j++] = str[i];
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char *ft_getenv(char *var, char **env_copy)
{
    size_t len;
    int i = 0;
    char *entry;

    if (!var)
        return NULL;
    len = ft_strlen(var);
    while (env_copy[i])
    {
        entry = env_copy[i];
        if (ft_strncmp(entry, var, len) == 0 && entry[len] == '=')
            return entry + len + 1;
        i++;
    }
    return NULL;
}