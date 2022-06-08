#include "minishell.h"

static size_t	get_exit_status_digit(t_envlist *env)
{
	int		exit_status;
	size_t	digit;

	digit = 0;
	exit_status = env->doller_ret;
	if (exit_status == 0)
		return (1);
	while (exit_status != 0)
	{
		exit_status = exit_status / 10;
		digit++;
	}
	return (digit);
}

static size_t	get_next_sq(char *word)
{
	size_t	len;

	len = 0;
	while (word[len] != '\0' && word[len] != '\'')
	{
		len++;
	}
	return (len + 1);
}

static size_t	get_env_length(char *word, t_envlist *env)
{
	size_t	tr_len;
	size_t	value_len;

	if (env->head)
		env = env->next;
	tr_len = 0;
	while (ft_isalnum(word[tr_len]) || word[tr_len] == '_')
		tr_len++;
	while (!env->head)
	{
		if (!ft_strncmp(word, env->key, tr_len))
		{
			if (env->value == NULL)
				return (0);
			value_len = ft_strlen(env->value);
			return (value_len);
		}
		env = env->next;
	}
	return (0);
}

static char	*get_env_value(char *word, t_envlist *env)
{
	size_t	tr_len;

	if (env->head)
		env = env->next;
	tr_len = 0;
	while (ft_isalnum(word[tr_len]) || word[tr_len] == '_')
		tr_len++;
	while (!env->head)
	{
		if (!ft_strncmp(word, env->key, tr_len))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

static size_t	get_env_less_length(char *word, t_envlist *env)
{
	size_t	env_less_len;
	size_t	env_len;

	env_less_len = 0;
	env_len = 0;
	while (word[env_less_len + env_len] != '\0')
	{
		if (word[env_less_len + env_len] == '$')
		{
			env_len++;
			if (word[env_less_len + env_len] == '?')
				env_len++;
			else
			{
				while (ft_isalnum(word[env_less_len + env_len]) || \
						word[env_less_len + env_len] == '_')
					env_len++;
			}
		}
		else
			env_less_len++;
	}
	return (env_less_len);
}

static size_t	get_env_only_length(char *word, t_envlist *env)
{
	size_t	length;
	size_t	exit_status_digit;

	length = 0;
	exit_status_digit = get_exit_status_digit(env);
	while (*word != '\0')
	{
		if (*word == '$')
		{
			word++;
			if (*word == '?')
			{
				word++;
				length += exit_status_digit;
			}
			else
			{
				length += get_env_length(word, env);
				while (ft_isalnum(*word) || *word == '_')
					word++;
			}
		}
		else
			word++;
	}
	return (length);
}

static size_t	exit_status_cat(char *expand_word, t_envlist *env, size_t stat_len)
{
	size_t	i;
	int		exit_status;
	size_t	temp;

	i = ft_strlen(expand_word);
	temp = stat_len;
	exit_status = env->doller_ret;
	if (exit_status == 0)
	{
		expand_word[i] = '0';
		expand_word[i + 1] = '\0';
		return (1);
	}
	expand_word[i + stat_len] = '\0';
	stat_len--;
	while (exit_status != 0)
	{
		expand_word[i + stat_len] = exit_status % 10 + '0';
		exit_status = exit_status / 10;
		stat_len--;
	}
	return (temp);
}

static char	*expansion_line(\
	char *expand_word, char *word, t_envlist *env, size_t total_length)
{
	char	*env_word;
	size_t	expand_word_index;
	size_t	env_word_index;
	size_t	word_index;
	size_t	exit_status_length;

	expand_word_index = 0;
	word_index = 0;
	exit_status_length = get_exit_status_digit(env);
	while (word[word_index] != '\0')
	{
		if (word[word_index] != '$')
		{
			// write(1, "a\n", 2);
			expand_word[expand_word_index] = word[word_index];
			expand_word_index++;
			word_index++;
		}
		else
		{
			// write(1, "b\n", 2);
			expand_word[expand_word_index] = word[word_index];
			word_index++;
			if (word[word_index] == '?')
			{
				exit_status_cat(expand_word, env, exit_status_length);
				expand_word_index += exit_status_length;
				word_index++;
			}
			else
			{
				env_word = get_env_value(word + word_index, env);
				env_word_index = 0;
				while (ft_isalnum(word[word_index]) || word[word_index] == '_')
					word_index++;
				if (env_word != NULL)
					while (env_word[env_word_index] != '\0')
					{
						expand_word[expand_word_index] = env_word[env_word_index];
						expand_word_index++;
						env_word_index++;
					}
			}
		}
	}
	return (expand_word);
}

int	heredoc_expansion(t_token *token, t_envlist *env)
{
	char	*expand_word;
	size_t	env_length;
	size_t	env_less_length;
	size_t	total_length;

	env_length = get_env_only_length(token->word, env);
	env_less_length = get_env_less_length(token->word, env);
	total_length = env_length + env_less_length;
	expand_word = (char *)malloc(sizeof(char) * (total_length + 1));
	if (expand_word == NULL)
		return (1);
	return (1);
	expand_word[total_length] = '\0';
	expand_word = expansion_line(expand_word, token->word, env, total_length);
	free(token->word);
	token->word = expand_word;
	token->word_len = ft_strlen(expand_word);
	return (0);
}
