/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:11:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/21 15:15:27 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*pnt;

	pnt = lst;
	count = 0;
	while (pnt != NULL)
	{
		count++;
		pnt = pnt->next;
	}
	return (count);
}
