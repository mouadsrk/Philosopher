/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/09 21:39:31 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	death(t_list *philo, long begin)
{
	long	now;

	now = time_init() - begin;
	philo = philo->head;
	while (philo->num <= philo->philo_num)
	{
		pthread_mutex_lock(&philo->check_last_eat);
		if (now - philo->last_eat >= philo->t_die)
		{
			pthread_mutex_lock(&philo->head->death_p);
			pthread_mutex_unlock(&philo->check_last_eat);
			ft_usleep(2);
			ft_printf(philo, "died", begin);
			philo->head->death_satus = 1;
			pthread_mutex_unlock(&philo->head->death_p);
			return (1);
		}
		pthread_mutex_unlock(&philo->check_last_eat);
		if (philo->num == philo->philo_num)
			break ;
		philo = philo->next;
	}
	return (0);
}

int	check_life_norm(t_list *tmp)
{
	int	i;

	i = 1;
	while (tmp->max_eat == -2 && i <= tmp->philo_num)
	{
		pthread_mutex_unlock(&(tmp)->check_max_eat);
		tmp = tmp->next;
		pthread_mutex_lock(&(tmp)->check_max_eat);
				i++;
	}
	if (i == tmp->philo_num + 1)
	{
		pthread_mutex_unlock(&(tmp)->check_max_eat);
		return (0);
	}
	else
		pthread_mutex_unlock(&(tmp)->check_max_eat);
	return (1);
}

void	check_life_(t_list *tmp, long begin)
{
	ft_usleep(tmp->t_die - 1);
	while (1)
	{
		if (death(tmp, begin))
			return ;
		tmp = tmp->head;
		pthread_mutex_lock(&(tmp)->check_max_eat);
		if (tmp->max_eat != -1)
		{
			if (!check_life_norm(tmp))
				return ;
		}
		else
			pthread_mutex_unlock(&(tmp)->check_max_eat);
	}
}

void	star_norm(t_list *tmp)
{
	int		i;
	long	time;

	time = tmp->head->beging;
	check_life_(tmp->head, time);
	i = 0;
	while (i < tmp->philo_num)
	{
		pthread_mutex_destroy(&tmp->fork_m);
		pthread_mutex_destroy(&tmp->check_last_eat);
		pthread_mutex_destroy(&tmp->check_max_eat);
		tmp = tmp->next;
		i++;
	}
	pthread_mutex_destroy(&tmp->head->print);
	pthread_mutex_destroy(&tmp->head->death_p);
}

void	star(t_list *tmp)
{
	int		i;

	i = 0;
	pthread_mutex_init(&tmp->death_p, NULL);
	pthread_mutex_init(&tmp->print, NULL);
	while (i < tmp->philo_num)
	{
		pthread_mutex_init(&tmp->fork_m, NULL);
		pthread_mutex_init(&tmp->check_last_eat, NULL);
		pthread_mutex_init(&tmp->check_max_eat, NULL);
		tmp->beging = time_init();
		pthread_create(&tmp->eat_time, NULL, &rotine, tmp);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < tmp->philo_num)
	{
		pthread_detach(tmp->eat_time);
		tmp = tmp->next;
		i++;
	}
	star_norm(tmp);
}
