/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:11:19 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 15:02:20 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_mem.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*mem;

	if (!size)
		return (0);
	mem = (unsigned char *)malloc(size);
	if (mem)
	{
		ft_bzero(mem, size);
		return ((void *)mem);
	}
	else
		return (0);
}
