/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:14:39 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 14:55:08 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int		ft_atoi_base(const char *str, int base)
{
	long long		over;
	int				cast;

	over = ft_atoll_base(str, base);
	cast = (int)over;
	return (cast);
}
