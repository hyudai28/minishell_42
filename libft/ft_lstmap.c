/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 04:58:45 by tarata            #+#    #+#             */
/*   Updated: 2021/04/24 02:47:00 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*new_element;

	if (!lst || !f)
		return (NULL);
	lst_new = NULL;
	while (lst)
	{
		new_element = ft_lstnew(f(lst->content));
		if (new_element == NULL)
		{
			ft_lstclear(&lst_new, del);
			break ;
		}
		ft_lstadd_back(&lst_new, new_element);
		lst = lst->next;
	}
	return (lst_new);
}
