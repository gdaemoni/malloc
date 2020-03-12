/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avl_api_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 06:59:16 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/05 14:55:22 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_avl_bltn.h"

int				ft_avl_tree_free(t_avl_tree *tree)
{
	if (tree == 0)
		return (-1);
	avlb_stree_destroy(tree->root, tree->rm_func);
	free(tree);
	return (0);
}

t_avln			*ft_avl_cut(t_avl_tree *tree, const char *key)
{
	t_avln		*cutten;

	if (tree == 0)
		return (0);
	tree->root = avlb_cut(tree->root, key, &cutten);
	return (cutten);
}

int				ft_avl_del(t_avl_tree *tree, const char *key)
{
	t_avln		*cutten;

	if (tree == 0)
		return (-1);
	tree->root = avlb_cut(tree->root, key, &cutten);
	avlb_rmnode(cutten, tree->rm_func);
	return (0);
}
