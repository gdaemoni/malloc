/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstrmelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:45:42 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 14:59:31 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"
#include <stdlib.h>

void	ft_dlstrmelem(t_dlist **deldlst)
{
	t_dlist		*removed;

	if (!deldlst || !(*deldlst))
		return ;
	removed = ft_dlstcut(deldlst);
	if (removed->size && removed->content)
		free(removed->content);
	free(removed);
}

void	ft_dlst_delcut(t_dlist **deldlst, void (*rmfunc)(void *, size_t))
{
	t_dlist		*removed;

	if (!deldlst || !(*deldlst))
		return ;
	removed = ft_dlstcut(deldlst);
	if (rmfunc)
		rmfunc(removed->content, removed->size);
	free(removed);
}
