/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:24:20 by hel-haji          #+#    #+#             */
/*   Updated: 2023/12/08 19:04:47 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	search(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*substr;
	size_t	j;

	start = 0;
	end = 0;
	j = 1;
	substr = NULL;
	if (!s1)
		return (NULL);
	if (!*s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	end = ft_strlen(s1);
	while (s1[start] && search(s1[start], set) == 0)
		start++;
	while (s1[end - j] && search(s1[end - j], set) == 0)
		j++;
	end -= j - 1;
	len = end - start;
	substr = ft_substr(s1, start, len);
	return (substr);
}
