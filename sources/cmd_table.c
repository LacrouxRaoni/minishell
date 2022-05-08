#include "minishell.h"

void cmd_table(char **parsed_line, t_cmd *cmd)
{
	int i;

	i = 0;
	while (parsed_line[i])
	{
		if (ft_strncmp(parsed_line[i], "|", 1) == 0)
			cmd->pipe = ft_strdup(parsed_line[i]);
		else if (ft_strncmp(parsed_line[i], "<\0", 2) == 0)
			cmd->less = ft_strdup(parsed_line[i]);
		else if (ft_strncmp(parsed_line[i], "<<\0", 3) == 0)
			cmd->dless = ft_strdup(parsed_line[i]);
		else if (ft_strncmp(parsed_line[i], "<<<\0", 4) == 0)
			cmd->gless = ft_strdup(parsed_line[i]);
		else if (ft_strncmp(parsed_line[i], ">\0", 2) == 0)
			cmd->great = ft_strdup(parsed_line[i]);
		else if (ft_strncmp(parsed_line[i], ">>\0", 3) == 0)
			cmd->dgreat = ft_strdup(parsed_line[i]);
		else if (ft_strncmp(parsed_line[i], ">|\0", 3) == 0)
			cmd->clooper = ft_strdup(parsed_line[i]);
		else
			cmd->word = ft_strdup(parsed_line[i]);
		i++;
	}
	printf("$ %s\n", cmd->pipe);
	printf("$ %s\n", cmd->less);
	printf("$ %s\n", cmd->dless);
	printf("$ %s\n", cmd->gless);
	printf("$ %s\n", cmd->great);
	printf("$ %s\n", cmd->dgreat);
	printf("$ %s\n", cmd->clooper);
	printf("$ %s\n", cmd->word);
}
