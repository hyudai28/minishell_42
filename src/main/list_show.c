#include "minishell.h"

void	debug1(t_token *tmp)
{
	printf("token : %s[%p]\n", tmp->word, &tmp->word);
	// if (tmp->type != HEAD)
		// printf("prev token : %s\n", tmp->prev->word);
	printf("token_len : %d\n", (int)tmp->word_len);
	printf("<token type> HEAD=0,TAIL=1,DQ=2,\
SQ=3,EXPANDABLE=4,PIPE=5,REDIRECT=6,R_STDIN=7\n");
	printf("token type: %d\n", tmp->type);
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
