/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:16:26 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/12 20:16:40 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t			get_heap_size(size_t size)
{
	if (size < TYNY_MAX_ALLOC)
		return (TINY_SIZE);
	if (size < SMALL_MAX_ALLOC)
		return (SMALL_SIZE);
	return (PAGE_SIZE * ((LARGE_SIZE(size) / PAGE_SIZE) + 1));
}

t_heap_type		get_heap_type(size_t size)
{
	if (size < TYNY_MAX_ALLOC)
		return (TYNY);
	if (size < SMALL_MAX_ALLOC)
		return (SMALL);
	return (LARGE);
}
