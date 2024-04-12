/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:52:36 by elmaleuv          #+#    #+#             */
/*   Updated: 2023/04/17 14:22:23 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	word;

	word = 0;
	while (s && *s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && !(*s == c))
		{
			word++;
			while (*s && !(*s == c))
				s++;
		}
	}
	return (word);
}

static int	ft_strlen_c(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == c))
		i++;
	return (i);
}

static char	*malloc_word(char const *s, char c)
{
	char	*word;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen_c(s, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (s[i] && !(s[i] == c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (s && *s)
	{
		while (*s && (*s == c))
			s++;
		if (*s && !(*s == c))
		{
			tab[i] = malloc_word(s, c);
			i++;
			while (*s && !(*s == c))
				s++;
		}
	}			
	tab[i] = NULL;
	return (tab);
}
