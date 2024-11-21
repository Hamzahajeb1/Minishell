/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:11:25 by hel-haji          #+#    #+#             */
/*   Updated: 2023/12/08 18:40:10 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0' && little[j])
	{
		if (big[i] == little[j])
		{
			i++;
			j++;
			if (j == ft_strlen(little))
				return ((char *)big + i - j);
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	return (NULL);
}
