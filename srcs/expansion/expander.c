/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:25:41 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/21 13:36:22 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_out_dollar(t_token *token, int i)
{
	char	*pre;
	char	*post;
	char	*new;

	pre = ft_substr(token->content, 0, i);
	post = ft_substr(token->content, i + 1, ft_strlen(token->content));
	new = ft_strjoin(pre, post);
	free_str(pre);
	free_str(post);
	free(token->content);
	token->content = new;
}

void	remove_dollar_before_single(t_token *token, int i)
{
	char	*new;

	if (i == 0)
	{
		new = ft_substr(token->content, 1, ft_strlen(token->content));
		free(token->content);
		token->content = new;
	}
	else
	{
		while (token->content[i])
		{
			if (token->content[i] == '$')
			{
				trim_out_dollar(token, i);
				break ;
			}
			i++;
		}
	}
}

void	check_paramexp(t_token *token, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '$' && !token->content[i + 1])
			token->dollar = 1;
		if ((i == 0))
		{
			if ((token->content[i] == '$' && token->content[i + 1] == '\'')
				|| (token->content[i] == '$' && token->content[i + 1] == '\"'))
				remove_dollar_before_single(token, i);
		}
		if (token->content[i] == '$' && token->content[i + 1]
			&& token->dollar == 0)
			exp_dollar(token, i, minishell);
		if (token->content[i] == 0)
			break ;
		i++;
	}
}

void	expand_token(t_minishell *minishell)
{
	t_token	*tok;

	tok = minishell->token;
	while (tok)
	{
		if (tok->flag_type == TOKEN_WORD)
		{
			define_quote_type(tok);
			check_paramexp(tok, minishell);
			remove_quotes(tok);
		}
		tok = tok->next;
	}
}

/*
Handle ’ (single quote) which should prevent the 
shell from interpreting the meta-
characters in the quoted sequence.
EX : 
********** CAS 0
echo 'hello'
output : hello
> return str, remove ' 

********** CAS 1
input : echo '$HOME'
ouput : $HOME
----- Avec un metachar
> return as it is, remove '

********* CAS 2
input : echo 'I live at "$HOME"'
output : I live at "$HOME"
---- metachar + quotes
> return as it is, remove '

******** CAS 3
gerer ''
> remove quotes


• Handle " (double quote) which should prevent the shell 
from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
Ex: 
input : echo "$HOME"
output : home/lo

input : echo "I live at '$HOME'"
output : I live at '/home/lo'

""



*/