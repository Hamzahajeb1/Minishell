/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:27:32 by hel-haji          #+#    #+#             */
/*   Updated: 2023/12/07 08:04:51 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*k;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	k = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (k == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		k[i] = (*f)(i, s[i]);
		i++;
	}
	k[i] = '\0';
	return (k);
}
