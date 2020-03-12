/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:30:04 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 15:05:36 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*str;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	str = ft_strsub(s1, 0, len);
	return (str);
}
