#include "minishell.h"

void	lexical_analysis(char **parsed_line, t_mns *data)
{
	int	i;

	data->lexical_line = (char **)ft_calloc(sizeof(parsed_line), sizeof(char *) + 1);
	i = 0;
	while (parsed_line[i] != NULL)
	{
		if (ft_strncmp(parsed_line[i], "|", 1) == 0)
			data->lexical_line[i] = ft_strdup("PIPE");
		else if (ft_strncmp(parsed_line[i], "<\0", 2) == 0)
			data->lexical_line[i] = ft_strdup("LESS");
		else if ((ft_strncmp(parsed_line[i], "<<\0", 3) == 0))
			data->lexical_line[i] = ft_strdup("DLESS");
		else if ((ft_strncmp(parsed_line[i], "<<<\0", 4) == 0))
			data->lexical_line[i] = ft_strdup("GLESS");
		else if ((ft_strncmp(parsed_line[i], ">\0", 2) == 0))
			data->lexical_line[i] = ft_strdup("GREAT");
		else if ((ft_strncmp(parsed_line[i], ">>\0", 3) == 0))
			data->lexical_line[i] = ft_strdup("DGREAT");
		else if ((ft_strncmp(parsed_line[i], ">|\0", 3) == 0))
			data->lexical_line[i] = ft_strdup("CLOOPER");
		else
			data->lexical_line[i] = ft_strdup("WORD");
		printf ("%s ", data->lexical_line[i]);
		i++;
	}
	data->lexical_line[i] = NULL;

	i = -1;
	while (data->lexical_line[++i])
		free (data->lexical_line[i]);
	free(data->lexical_line);
	data->lexical_line = NULL;
}