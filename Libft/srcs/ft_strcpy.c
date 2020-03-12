/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:46:22 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 15:05:25 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_mem.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t		len;

	len = ft_strlen(src);
	ft_memcpy(dst, src, len);
	dst[len] = 0;
	return (dst);
}
