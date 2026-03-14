/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucsanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 10:02:39 by lucsanto          #+#    #+#             */
/*   Updated: 2026/03/14 10:02:40 by lucsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_total_len(int size, char **strs, char *sep)
{
	int	i;
	int	total;
	int	sep_len;

	i = 0;
	total = 0;
	sep_len = ft_strlen(sep);
	while (i < size)
	{
		total = total + ft_strlen(strs[i]);
		i++;
	}
	if (size > 1)
		total = total + (size - 1) * sep_len;
	return (total);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	char	*str_cats;

	i = 0;
	if (size == 0)
	{
		str_cats = (char *) malloc(1);
		if (str_cats == NULL)
			return (NULL);
		str_cats[0] = '\0';
		return (str_cats);
	}
	str_cats = (char *) malloc(ft_total_len(size, strs, sep) + 1);
	str_cats[0] = '\0';
	while (i < size)
	{
		ft_strcat(str_cats, strs[i]);
		if (i < size - 1)
		{
			ft_strcat(str_cats, sep);
		}
		i++;
	}
	return (str_cats);
}
