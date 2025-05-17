/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:31:47 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/18 00:01:58 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define MAX_FD 1023
# define MAX_HEREDOC 16
# define OPEN_QUOTES "Minishell does not support open quotes, please escape them properly\n"


typedef enum e_token_type
{
	WORD, //0
	PIPE, //1
	IN, //2
	OUT, //3
	APPEND, //4
	HDOC, //5
	FD, // 6
	CMD, // 7
	ARG, // 8
	LIMITER, // 9
	FILEN, // 10
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				rank;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_quote_state
{
	int		w_start;
	bool	in_quotes;
	char	opening_quote;
}	t_quote_state;

typedef struct s_input_context
{
	char	*str;
	int		rank;
}	t_input_context;

typedef struct s_shell
{
	char **env;
	t_token *token;
	char **splitted;
} t_shell;

//booleans functions for split2
bool	is_quote(char c);
bool	is_closing_quote(char c, char opening_quote);
bool	handle_quotes(char c, bool *in_quotes, char *opening_quote);

//string_utils functions
char	*ft_substrword(char *str, int start, int end);
char	*trim_quotes(char *str);
char	**ft_strdup_array(char **src);


//parsing utils
int		ft_has_invalid_quotes(const char *str);

//main lexer functions
char	**ft_split2(char const *s, char c);
void	tokenizer(t_shell *shell, int rank);
void	refine_token_type(t_token *token);

//[PLACEHOLDER] quote counter
//[PLACEHOLDER] quote trimmer

//linked_list_utils functions
t_token	*create_token(char *str);
int		add_token(t_shell *shell, char *str, t_token_type type, int rank);

//clean exit
void	ft_free_str_array(char **arr);
void	free_list(t_token **head);
void	ft_exit(char *input, t_shell *shell);



char 	*prompt(char **env);

#endif