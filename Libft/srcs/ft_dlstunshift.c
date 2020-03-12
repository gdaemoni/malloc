/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstunshift.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:13:29 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 14:59:50 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlstunshift(t_dlist **dlst, t_dlist *nlst)
{
	if (!nlst || !dlst)
		return ;
	nlst->next = *dlst;
	if (*dlst)
		(*dlst)->prev = nlst;
	*dlst = nlst;
}
