/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:42:30 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/06 02:36:29 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(char *a, char *b, char *c, int need_free)
{
	char	*ret1;
	char	*ret2;

	ret1 = ft_strjoin(a, b); //malloc
	if (ret1 == NULL)
	{
		if (need_free)
		{
			free(a);
			free(b);
			free(c);
		}
		return (NULL);
	}
	ret2 = ft_strjoin(ret1, c); //malloc
	free(ret1);
	if (need_free)
	{
		free(a);
		free(b);
		free(c);
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

	//varはnullになりうるよ
	if (token->word[tword_i + 1] == '?')
		var_len = 2 + tword_i;
	else
	{
		var_len = ft_strlen(var) + tword_i + 1;
		var = get_envline(env, var);
		if (!var)
		{
			var = ft_strdup("");//malloc
			var_len -= 1;
		}
	}
	before_var = ft_substr(token->word, 0, tword_i);//malloc
	after_var = ft_substr(token->word, var_len, ft_strlen(token->word));//malloc
	tword_i = ft_strlen(before_var) + ft_strlen(var);
	var = ft_strjoin3(before_var, var, after_var, TRUE);//malloc
	free(token->word);
	token->word = var;
	token->word_len = ft_strlen(var);
	return (tword_i);
}

// static int	add_env_length(char *word, t_envlist *env, size_t *env_len)
// {
// 	t_envlist	*env_p;
// 	char		*env_key;
// 	size_t		envkey_len;

// 	envkey_len = 0;
// 	while (ft_isalnum(word[envkey_len]) || word[envkey_len] == '_')
// 	{
// 		envkey_len++;
// 	}
// 	env_key = ft_substr(word, 0, envkey_len);
// 	if (env_key == NULL)
// 		return (1);
// 	env_p = envlist_search(env_key, env);
// 	(*env_len) = (*env_len) + ft_strlen(env_p->value);
// 	return (0);
// }

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
	return (0);
}

static size_t	get_env_less_length(char *word, t_envlist *env)
{
	size_t	env_less_len;
	size_t	env_len;

	env_less_len = 0;
	env_len = 0;
	while (word[env_less_len + env_len] != '\0')
	{
		if (word[env_less_len + env_len] == '\'')
			env_less_len += get_next_sq(word + env_less_len + env_len + 1);
		else if (word[env_less_len + env_len] == '$')
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
		if (*word == '\'')
			word += get_next_sq(word + 1);
		else if (*word == '$')
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

static char	*expansion_env(\
	char *expand_word, char *word, t_envlist *env, size_t total_length)
{
	char	*env_word;
	size_t	expand_word_index;
	size_t	word_index;
	size_t	copy_length;

	expand_word_index = 0;
	word_index = 0;
	while (expand_word_index < total_length)
	{
		if (word[word_index] == '$')
		{
			env_word = get_env_value(word, env);
			copy_length = ft_strlen(env_word);
			copy_length = ft_strlcat(expand_word, env_word, copy_length);
			expand_word_index += copy_length;
		}
		expand_word[expand_word_index] = word[word_index];
		word_index++;
		expand_word_index++;
	}
	return (expand_word);
}

int	expansion_dq(t_token *token, t_envlist *env)
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
	expand_word[0] = '\0';
	expand_word = expansion_env(expand_word, token->word, env, total_length);
	free(token->word);
	token->word = expand_word;
	return (0);
}
