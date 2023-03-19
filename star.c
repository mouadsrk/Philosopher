/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/19 01:37:27 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int death(t_list *philo)
{

	philo = philo->head;
	if(philo->head->death_satus == 1)
		return 1;
	while( philo->num <= philo->philo_num)
	{
		if(philo->now - philo->last_eat >= philo->t_die)
			{
				philo->now = time_init() - philo->beging;
				printf("%ld philo %d is death\n",philo->now,philo->num);
				philo->head->death_satus = 1;
				return 1;
			}
		if( philo->num == philo->philo_num)
			break;
		philo = philo->next;
	}
	return 0;
}

int max_eat(t_list *philo)
{
	int i;

	i = 0;
	while(i < philo->philo_num)
	{
		if(philo->num_eat < philo->max_eat)
			return 0;
		philo = philo->next;
		i++;
	}
	return 1;
}


int lock_check_life_data(t_list *tmp)
{
	pthread_mutex_lock(&tmp->head->death_p);
	if(death(tmp) || ((max_eat(tmp) && tmp->max_eat != -1)))
		{
			pthread_mutex_unlock(&tmp->head->death_p);
			return 0;
		}
	return 1;
}

int	think(t_list *philo)
{
	if(!lock_check_life_data(philo))
		return 0;
	pthread_mutex_unlock(&philo->head->death_p);
	philo->now = time_init() - philo->beging;
	printf("%ld philo %d is thinking!\n" ,philo->now, philo->num);
	return 1;
}

int	ft_sleep(t_list *philo)
{
	if(!lock_check_life_data(philo))
		return 0;
	pthread_mutex_unlock(&philo->head->death_p);
	philo->now = time_init() - philo->beging;
	printf("%ld philo %d is sleeping!\n" ,philo->now,philo->num);
	usleep(philo->t_sleep * 1000);
		return 1;
}

int  eat(t_list *philo)
{
	if(philo->num % 2 == 0 && philo->num != 1 && philo->num_eat == 0)
		usleep(philo->t_eat);
	pthread_mutex_lock( &philo->fork_m); 
	pthread_mutex_lock( &philo->next->fork_m);
	if(!lock_check_life_data(philo) || philo->num_eat == philo->max_eat)
	{
		pthread_mutex_unlock(&philo->fork_m);
		pthread_mutex_unlock(&philo->next->fork_m);
			return 0;
	}
	philo->now = time_init() - philo->beging;
	printf("%ld philo %d take fork!\n%ld philo %d take fork!\n",philo->now,philo->num ,philo->now,philo->num);
	printf("%ld philo %d is eating\n" ,philo->now,philo->num);
	philo->last_eat = time_init();
	usleep(philo->t_eat * 1000);
	philo->num_eat += 1;
	pthread_mutex_unlock(&philo->head->death_p);
	pthread_mutex_unlock(&philo->fork_m);
	pthread_mutex_unlock(&philo->next->fork_m);
	return 1;
}

void *rotine(void *tmp)
{
	while(1)
	{
		if(!eat((t_list*) tmp))
			break;
		if(!ft_sleep((t_list*) tmp))
			break;
		if(!think((t_list*) tmp))
			break;
	}
	return NULL;
}
void    int_rotine(t_list *tmp)
{
	int i;

	i = 0;
	while(i < tmp->philo_num)
	{
		pthread_mutex_init(&tmp->fork_m, NULL);
		pthread_mutex_init(&tmp->death_p, NULL);
		tmp->beging = time_init();
		pthread_create(&tmp->eat_time, NULL,&rotine,tmp);
		tmp = tmp->next;
		i++;
	}
		i = 1;
	while(i <= tmp->philo_num + 1)
	{
		pthread_join(tmp->eat_time,NULL);
		pthread_mutex_destroy(&tmp->fork_m);
		tmp = tmp->next;
		i++;
	}
	pthread_mutex_destroy(&tmp->death_p);
}

void	star(t_list *philo)
{
		int_rotine(philo);
		
}