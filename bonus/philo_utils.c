/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:27:02 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/07 15:17:36 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					s;
	unsigned long long	r;

	r = 0;
	s = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + *str - 48;
		if ((r > 2147483647 && s == 1) || (r > 2147483648 && s == -1))
			exit_error("Error\n");
		str++;
	}
	return ((int)(r * s));
}

t_list	*ft_lstnew(int content, int arc, char **argv)
{
	t_list	*s;

	s = malloc (sizeof(t_list));
	if (s == NULL)
		return (NULL);
	s->philo_num = ft_atoi(argv[1]);
	s->t_die = ft_atoi(argv[2]);
	s->t_eat = ft_atoi(argv[3]);
	s->t_sleep = ft_atoi(argv[4]);
	s->max_eat = -1;
	if (arc == 6)
		s->max_eat = ft_atoi(argv[5]);
	s->num = content;
	s->next = NULL;
	return (s);
}

void	ft_lstclear(t_list	**lst)
{
	t_list	*tmp;
	int		i;
	int		j;

	i = 1;
	j = (*lst)->philo_num;
	if (!lst)
		return ;
	while (*lst && i <= j)
	{
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
		i++;
	}
}
