/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:24:45 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/09 21:37:39 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	think(t_list *philo,	long beging)
{
	pthread_mutex_lock(&philo->head->death_p);
	if (philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		return (0);
	}
	pthread_mutex_unlock(&philo->head->death_p);
	ft_printf(philo, "is thinking", beging);
	return (1);
}

int	ft_sleep(t_list *philo, long beging)
{
	pthread_mutex_lock(&philo->head->death_p);
	if (philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		return (0);
	}
	pthread_mutex_unlock(&philo->head->death_p);
	ft_printf(philo, "is sleeping", beging);
	ft_usleep(philo->t_sleep);
	return (1);
}

int	eat(t_list *philo, long beging, int i)
{
	if (philo->num % 2 == 0 && philo->num != 1 && i == 2)
		ft_usleep(philo->t_eat);
	pthread_mutex_lock(&philo->fork_m);
	ft_printf(philo, "has taken a fork", beging);
	pthread_mutex_lock(&philo->next->fork_m);
	ft_printf(philo, "has taken a fork", beging);
	pthread_mutex_lock(&philo->check_last_eat);
	philo->last_eat = time_init() - beging;
	pthread_mutex_unlock(&philo->check_last_eat);
	pthread_mutex_lock(&philo->head->death_p);
	if (philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		pthread_mutex_unlock(&philo->fork_m);
		pthread_mutex_unlock(&philo->next->fork_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->head->death_p);
	ft_printf(philo, "is eating", beging);
	ft_usleep(philo->t_eat);
	pthread_mutex_unlock(&philo->fork_m);
	pthread_mutex_unlock(&philo->next->fork_m);
	return (1);
}

void	*rotine(void *tmp)
{
	int		i;
	int		j;
	long	beging;

	i = 1;
	pthread_mutex_lock(&((t_list *)tmp)->check_max_eat);
	beging = ((t_list *)tmp)->beging;
	j = ((t_list *)tmp)->max_eat;
	pthread_mutex_unlock(&((t_list *)tmp)->check_max_eat);
	while ((i++ <= j && j != -1) || (j == -1))
	{
		if (!eat((t_list *)tmp, beging, i) || (i > j && j != -1))
			break ;
		if (!ft_sleep((t_list *)tmp, beging))
			break ;
		if (!think((t_list *) tmp, beging))
			break ;
	}
	if (i > j)
	{
		pthread_mutex_lock(&((t_list *)tmp)->check_max_eat);
		((t_list *)tmp)->max_eat = -2;
		pthread_mutex_unlock(&((t_list *)tmp)->check_max_eat);
	}
	return (NULL);
}
