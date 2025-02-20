/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:17:15 by pchapuis          #+#    #+#             */
/*   Updated: 2022/12/20 16:26:29 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	nb_sep(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
	{
		i ++;
		if (s[i] == '\0')
			return (0);
	}
	len = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			len ++;
		i ++;
	}
	return (len);
}

static int	size_sep(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i ++;
	return (i);
}

static char	**ft_free_split(char **result, int x)
{
	while (--x >= 0)
		free(result[x]);
	free(result);
	return (NULL);
}

static char	**fill(char const *s, char c, char **result, int nb)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	while (s[i] && x < nb - 1)
	{
		while (s[i] == c && s[i])
			i ++;
		result[x] = malloc(sizeof(char) * (size_sep(s + i, c) + 1));
		if (!result[x])
			return (ft_free_split(result, x));
		y = 0;
		while (s[i] != c && s[i])
			result[x][y ++] = s[i ++];
		if (y != 0)
			result[x ++][y] = '\0';
	}
	result[x] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (nb_sep(s, c) + 1));
	if (!result)
		return (NULL);
	if (nb_sep(s, c) == 0)
		result[0] = NULL;
	else
		fill(s, c, result, nb_sep(s, c) + 1);
	return (result);
}
