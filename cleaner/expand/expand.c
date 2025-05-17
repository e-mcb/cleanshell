#include "expand.h"

int main(void)
{
	char *input = "sach$4a le$4  user $USER $";
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
