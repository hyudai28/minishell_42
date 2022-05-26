#include "minishell.h"

char	*ft_strjoin3(char *a, char *b, char *c, int need_free)
{
	char	*ret1;
	char	*ret2;

	ret1 = ft_strjoin(a, b);
	ret2 = ft_strjoin(ret1, c);
	free(ret1);
	ret1 = NULL;
	if (need_free)
	{
		free(a);
		free(b);
		free(c);
		a = NULL;
		b = NULL;
		c = NULL;
	}
	return (ret2);
}

size_t	get_envlen(const char *line)
{
	size_t	envlen;

	envlen = 0;
	while (line[envlen])
	{
		if (ft_isalnum(line[envlen]) || line[envlen] == '_')
			envlen++;
		else
			break ;
	}
	return (envlen);
}

char	*get_envline(t_envlist *env, char *line)
{
	t_envlist	*target;

	target = envlist_search(line, env);
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (!target || !target->value)
		return (ft_strdup(""));
	return (ft_strdup(target->value));
}

size_t	assign_var(t_token *token, t_envlist *env, size_t tword_i, char *var)
{
	char	*before_var;
	char	*after_var;
	size_t	var_len;

	if (token->word[tword_i + 1] == '?')
		var_len = 2 + tword_i;
	else
	{
		var_len = ft_strlen(var) + tword_i + 1;
		var = get_envline(env, var);
		if (!var)
		{
			var = ft_strdup("");
			var_len -= 1;
		}
	}
	before_var = ft_substr(token->word, 0, tword_i);
	after_var = ft_substr(token->word, var_len, ft_strlen(token->word));
	tword_i = ft_strlen(before_var) + ft_strlen(var);
	var = ft_strjoin3(before_var, var, after_var, TRUE);
	free(token->word);
	token->word = var;
	token->word_len = ft_strlen(var);
	return (tword_i);
}

int	expansion_dq(t_token *token, t_envlist *env)
{
	size_t	tword_i;
	size_t	tword_len;
	size_t	envlen;
	int		single_quot;

	tword_i = 0;
	tword_len = ft_strlen(token->word);
	single_quot = 0;
	while (token->word && tword_i < tword_len)
	{
		if (token->word[tword_i] == '\'')
		{
			if (single_quot == 0)
				single_quot = 1;
			else if (single_quot == 1)
				single_quot = 0;
		}
		if (single_quot == 1)
		{
			tword_i++;
			continue ;
		}
		if (token->word[tword_i] == '$')
			if (token->word[tword_i + 1] == '?')
				tword_i = assign_var(token, env, tword_i, \
				ft_itoa(env->doller_ret));
		else
		{
				envlen = get_envlen(token->word + tword_i + 1);
				tword_i = assign_var(token, env, tword_i, \
				ft_substr(token->word, tword_i + 1, envlen));
				tword_i++;
		}
		else
			tword_i++;
		if (tword_i > tword_len)
			tword_len = ft_strlen(token->word);
	}
	return (0);
}
