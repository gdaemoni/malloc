/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:43:42 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 15:03:04 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*buff;

	buff = (unsigned char *)malloc(sizeof(unsigned char) * n);
	if (buff)
	{
		ft_memcpy(buff, src, n);
		ft_memcpy(dst, buff, n);
	}
	return (dst);
}
