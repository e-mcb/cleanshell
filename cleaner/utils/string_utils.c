/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:30:41 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/18 13:43:44 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

char	*ft_substrword(char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	*trim_quotes(char *str)
{
	int		start;
	int		end;
	char	*trimmed;

	start = 0;
	end = ft_strlen(str) - 1;
	if (str[start] == '"' || str[start] == '\'')
		start++;
	if (str[end] == '"' || str[end] == '\'')
		end--;
	trimmed = malloc(end - start + 2);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, &str[start], end - start + 2);
	return (trimmed);
}

static int	ft_strsize(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
