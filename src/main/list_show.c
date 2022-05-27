#include "minishell.h"

void	print_token_type(enum e_token_type	type)
{
	printf("token type	: ");
	if (type == HEAD)
		printf("HEAD");
	else if (type == TAIL)
		printf("TAIL");
	else if (type == EXPANDABLE)
		printf("EXPANDABLE");
	else if (type == PIPE)
		printf("PIPE");
	else if (type == APPEND_REDIRECT)
		printf("APPEND REDIRECT");
	else if (type == REDIRECT)
		printf("REDIRECT");
	else if (type == R_STDIN)
		printf("R_STDIN");
	else if (type == HEREDOC)
		printf("HEREDOC");
	printf("\n");
}

void	debug1(t_token *tmp)
{
	printf("token	: %s[%p]\n", tmp->word, &tmp->word);
	// if (tmp->type != HEAD)
		// printf("prev token : %s\n", tmp->prev->word);
	printf("token_len	: %d\n", (int)tmp->word_len);
	// printf("<token type> HEAD=0,TAIL=1,DQ=2,SQ=3,EXPANDABLE=4,PIPE=5,REDIRECT=6,R_STDIN=7\n");
	print_token_type(tmp->type);
	// printf("token type	: %d\n", tmp->type);
	printf("--------------------------\n");
}

void	debug_all(t_token *tmp)
{
	while (tmp->type != TAIL)
	{
		debug1(tmp);
		// debug2(tmp);
		tmp = tmp->next;
	}
	debug1(tmp);
}

void	debug_cmds(t_cmds *tmp)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (tmp->head != 1)
	{
		printf("\n------cmds[%d]------\n", i);
		j = 0;
		while (tmp->cmd[j])
		{
			printf("-cmd[%d] = [%s][%p]\n", j, tmp->cmd[j], &tmp->cmd[j]);
			printf("-outfd[%d] = [%d]\n", j, tmp->outfd_type);
			j++;
		}
		tmp = tmp->next;
		i++;
	}
}

void	debug_read(void)
{
	char	*buf;

	buf = NULL;
	read(0, buf, 1);
}

void	debug2(t_token *tmp)
{
	printf("token : %s\n", tmp->word);
	/*
	printf("token_len : %d\n", (int)tmp->word_len);
	printf("<token type> HEAD=0,TAIL=1,DQ=2,\
	SQ=3,EXPANDABLE=4,PIPE=5,REDIRECT=6\n");
	printf("token type: %d\n", tmp->type);
	printf("--------------------------\n");
	*/
}
