/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:24:45 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/07 01:26:35 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	think(t_list *philo,	long beging)
{
	long	now;

	pthread_mutex_lock(&philo->head->death_p);
	if (philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		return (0);
	}
	pthread_mutex_unlock(&philo->head->death_p);
	now = time_init() - beging;
	printf("%ld philo %d is thinking!\n", now, philo->num);
	return (1);
}

int	ft_sleep(t_list *philo, long beging)
{
	long	now;

	pthread_mutex_lock(&philo->head->death_p);
	if (philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		return (0);
	}
	pthread_mutex_unlock(&philo->head->death_p);
	now = time_init() - beging;
	printf("%ld philo %d is sleeping!\n", now, philo->num);
	ft_usleep(philo->t_sleep);
	return (1);
}

int	eat(t_list *philo, long beging, int i)
{
	if (philo->num % 2 == 0 && philo->num != 1 && i == 2)
		ft_usleep(philo->t_eat);
	pthread_mutex_lock(&philo->fork_m);
	printf("%ld philo %d take fork!\n", time_init() - beging, philo->num);
	pthread_mutex_lock(&philo->next->fork_m);
	printf("%ld philo %d take fork!\n", time_init() - beging, philo->num);
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
	printf("%ld philo %d is eating\n", time_init() - beging, philo->num);
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
