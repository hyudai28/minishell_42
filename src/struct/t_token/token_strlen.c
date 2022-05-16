#include "t_token.h"

void ft_strlen_sq_dq(char *str, char quotation, t_token *new, t_flag *flag)
{
	size_t len;
	size_t i;
	size_t count;

	count = 0;
	len = 0;
	i = 0;

	while (count != 2)
	{
		if (str[i++] == quotation)
			count++;
		if (str[i] == '\0')
		{
			new->word_len = WORD_LEN_ERROR;
			break ;
		}
		else
			len++;
	}
	if (new->word_len != WORD_LEN_ERROR)
		new->word_len = len;
	else
		printf("ERROR  \"quotation has no pair\"\n");
	if (quotation == '"')
		new->type = EXPANDABLE_DQ;
	else
		new->type = NONEXPANDABLE_SQ;
	flag->dq_flag = FALSE;
	flag->sq_flag = FALSE;
}

//void ft_strlen_others(char *str, t_token *new)
//{
//	size_t len;
//	int i;

//	len = 0;
//	i = -1;
//	while (!ft_strchr("|>< \0", str[++i]))
//		len++;
//	new->word_len = len;
//	new->type = EXPANDABLE;
//}

size_t	is_separate_char(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == ' ')
		return(3);
	else if (c == '<')
		return(4);
	else if (c == '>')
		return(5);
	else if (c == '|')
		return(6);
	return (0);
}

void ft_strlen_others(char *str, t_token *new)
{
	size_t	len;
	size_t	c_status;
	size_t	str_len;

	len = 0;
	c_status = 0;
	str_len = ft_strlen(str);
	while (len < str_len && is_separate_char(str[len]) == 0)
		len++;
	if (len == str_len)
		new->word_len = str_len;
	while (len < str_len && !ft_isspace(str[len]))
	{
		while (len < str_len && is_separate_char(str[len]) == 0)
			len++;
		c_status = is_separate_char(str[len++]);
		while (len < str_len && is_separate_char(str[len]) != c_status)
			len++;
		new->word_len = ++len;
	}
	new->type = EXPANDABLE;
}

void ft_strlen_redirect(char *str, t_token *new, t_flag *flag)
{
	if (!ft_strncmp(str, ">>", 2))
	{
		new->word_len = 2;
		new->type = REDIRECT;
	}
	else if (!ft_strncmp(str, ">", 1))
	{
		new->word_len = 1;
		new->type = REDIRECT;
	}
	else if (!ft_strncmp(str, "<<", 2))
	{
		new->word_len = 2;
		new->type = R_STDIN;
	}
	else if (!ft_strncmp(str, "<", 1))
	{
		new->word_len = 1;
		new->type = R_STDIN;
	}
	flag->redirect = FALSE;
}

void ft_strlen_pipe(t_token *new, t_flag *flag)
{
	new->word_len = 1;
	new->type = PIPE;
	flag->pipe = FALSE;
}
