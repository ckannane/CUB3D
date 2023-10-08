/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:52:51 by ckannane          #+#    #+#             */
/*   Updated: 2023/10/07 12:28:21 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char	*c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

int	ft_strchro(const char *s, int c)
{
	char	find;
	int		i;

	find = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == find)
			return (1);
		i++;
	}
	if (s[i] == find)
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	s;
	size_t	i;
	char	*ptr;

	i = 0;
	s = count * size;
	ptr = malloc(s);
	if (!ptr)
		return (0);
	while (i < s)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL )
		return ((char *)s2);
	if (s2 == NULL )
		return ((char *)s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*d;
	size_t		s_len;

	s_len = ft_strlen(s);
	if (s == NULL || s_len < start)
		return ("");
	if (start + len < s_len)
		d = (char *)malloc((len + 1) * sizeof(char));
	else
		d = (char *)malloc((s_len - start + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (i < (start + len) && s[i])
		d[j++] = s[i++];
	d[j] = '\0';
	return (d);
}
