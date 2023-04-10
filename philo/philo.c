/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:08:05 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/10 20:27:44 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	data_make(int arc, char **argv, t_list **philo)
{
	int		i;
	t_list	*tmp;

	i = 1;
	(*philo) = ft_lstnew(i, arc, argv);
	tmp = *philo;
	while (++i <= (*philo)->philo_num)
	{
		tmp->next = ft_lstnew(i, arc, argv);
		tmp = tmp->next;
		tmp->head = (*philo);
	}
	tmp->next = *philo;
	(*philo)->death_satus = 0;
	(*philo)->head = (*philo);
	return (1);
}

int	digit(int arc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < arc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	arg(int arc, char **argv)
{
	int	i;

	i = 1;
	while (i < arc)
	{
		if (argv[i][0] == '\0' || argv[i] == NULL)
			return (0);
		if (ft_atoi(argv[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	main(int arc, char **argv)
{
	t_list	*philo;
	int		i;

	i = 0;
	if ((arc != 5 && arc != 6) || !digit(arc, argv) || arg(arc, argv) == 0)
	{
		printf("error \n");
		return (0);
	}
	if (ft_atoi(argv[1]) == 0)
		return (0);
	data_make(arc, argv, &philo);
	star(philo);
	ft_lstclear(&philo);
}
