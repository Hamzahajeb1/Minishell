/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:15:57 by hel-haji          #+#    #+#             */
/*   Updated: 2023/12/07 07:57:12 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memo;

	if (size && nmemb >= SIZE_MAX / size)
		return (NULL);
	memo = malloc(nmemb * size);
	if (memo)
		ft_bzero(memo, nmemb * size);
	return (memo);
}
