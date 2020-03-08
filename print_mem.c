/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:53:06 by gdaemoni          #+#    #+#             */
/*   Updated: 2020/03/07 19:16:20 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	hex_dump(const void *addr, size_t size)
{
	int				i;
	unsigned char	buff[17];
	unsigned char*	ptr;
	
	i = -1;
	ptr = (unsigned char*)addr;
	while (++i < size)
	{
		if ((i % 16) == 0)
		{
			if (i != 0)
				printf("  %s\n", buff);
			printf("%p ", &(ptr[i]));
		}
		if ((i % 2) && i > 0)
			printf("  %02x%02x", ptr[i - 1], ptr[i]);
		if (ptr[i] < 32 || ptr[i] > 126)
			buff[i % 16] = '.';
		else
			buff[i % 16] = ptr[i];
		buff[(i % 16) + 1] = 0;
	}
	printf("\n");
}
