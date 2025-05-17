#ifndef EXPAND_H
# define EXPAND_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_expand
{
	int i;
	int	j;
	int count;
	int start; 
	bool in_single_quote;
	bool in_double_quote;
	char    **result;
}	t_expand;

//EXPAND
int 	ft_count_segments(const char *input);
char **	split_and_expand(const char *input);
char    *join_chars(char ** str);
void    case_double_dollar(t_expand *ex);
void    case_only_dollar(t_expand *ex);
void    case_question_mark(t_expand *ex, char *value);
void    case_env_var(t_expand *ex, char *value, const char *input);

//UTILS
int		ft_isalnum(int c);
char	*strndup_custom(const char *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);

#endif