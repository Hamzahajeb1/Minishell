/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:20:52 by hel-haji          #+#    #+#             */
/*   Updated: 2023/12/07 08:05:13 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;

	j = 0;
	if (s == NULL)
		return (0);
	i = ft_strlen(s);
	while (j + start < i && j < len)
		j++;
	p = malloc(j + 1);
	if (!p)
		return (0);
	i = 0;
	while (j > 0)
	{
		p[i++] = s[start++];
		j--;
	}
	p[i] = '\0';
	return (p);
}
