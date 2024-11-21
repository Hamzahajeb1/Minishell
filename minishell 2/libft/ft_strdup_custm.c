/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_custm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:28:49 by hel-haji          #+#    #+#             */
/*   Updated: 2024/11/21 13:28:50 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_1(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)malloc(n + 1); // to fix ft_malloc
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_2(const char *s)
{
	size_t	i;
	char	*str;

	str = (char *)malloc(ft_strlen(s) * sizeof(char) + 1); //to fix ft_malloc
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}