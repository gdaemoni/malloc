/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstrget.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:33:53 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 14:59:26 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

t_dlist		*ft_dlstrget(t_dlist *cdlst, size_t ind)
{
	while (ind-- && cdlst)
		cdlst = cdlst->prev;
	return (cdlst);
}
