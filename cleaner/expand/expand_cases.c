#include "expand.h"

int ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char *get_env_value(const char *name)
{
	char *value = getenv(name);
	if (!value)
		return strdup("");
	return strdup(value);
}

void    case_double_dollar(t_expand *ex)
{
	//ICI AFFICHER ERREUR CAR && NON PRIS EN CHARGE CA SIMPLIFIE LA SUITE DE RENVOYER ERREUR
	ex-> i = ex->i; 
	ex->i++;
	ex->start = ex->i;
}

void    case_only_dollar(t_expand *ex)
{
	ex->result[ex->j++] = ft_strdup("$");
	ex->i++;
	ex->start = ex->i;
}

void    case_question_mark(t_expand *ex, char *value)
{
	value = ft_strdup("--code retour derniere commande--");//ici fonction à implémenter
	ex->result[ex->j++] = value;
	ex->i += 2;
	ex->start = ex->i;
}

void    case_env_var(t_expand *ex, char *value, const char *input)
{
	char	*varname;
	ex->i++;
	ex->start = ex->i;
	while (input[ex->i] && !ft_isspace(input[ex->i]) && input[ex->i] != '"' && input[ex->i] != '\'' && input[ex->i] != '$')
		ex->i++;
	varname = strndup_custom(input + ex->start, ex->i - ex->start);
	value = get_env_value(varname);
	ex->result[ex->j++] = value;
	free(varname);
	ex->start = ex->i;
}


