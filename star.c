/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/17 13:41:08 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


int death(t_list *philo)
{
	t_list *tmp;
	tmp = philo;

	while( tmp->num <= philo->philo_num)
	{
		if(tmp->last_eat >= philo->t_die)
			{
			printf("philo %d is death\n",tmp->num);
			// 	exit(0);
				return 1;
			}
		if( tmp->num == philo->philo_num)
			break;
		tmp = tmp->next;
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

void unlock_check_life_data(void *philo)
{
	t_list *tmp;
	int j;

	tmp = (t_list*) philo;
	j = 0;
	while ((j < tmp->philo_num))
	{
		pthread_mutex_unlock(&tmp->death_p); 
		tmp = tmp->next;
		j++;
	}
}

int lock_check_life_data(t_list *tmp)
{
	int j;

	j = 0;
	tmp = tmp->head;
	while ((j < tmp->philo_num))
	{
		pthread_mutex_lock(&tmp->death_p); 
		tmp = tmp->next;
		j++;
	}
	tmp = tmp->head;
	if(death(tmp) || ((max_eat(tmp) && tmp->max_eat != -1)))
		{
			unlock_check_life_data(tmp);
			return 0;
		}
	return 1;
}


int	think(t_list *philo)
{
	if(!lock_check_life_data(philo))
		return 0;
	unlock_check_life_data(philo);
	printf("%d philo %d is thinking!\n" ,philo->now, philo->num);
	return 1;
}

int	ft_sleep(t_list *philo)
{
	if(!lock_check_life_data(philo))
		return 0;
	unlock_check_life_data(philo);
	printf("%d philo %d is sleeping!\n" ,philo->now,philo->num);
	usleep(philo->t_sleep);
	philo->now += philo->t_sleep;
	philo->last_eat += philo->t_sleep;
		return 1;
}

int  eat(t_list *philo)
{
	int i;
	if(philo->num % 2 == 0 && philo->num != 1)
		usleep(300);
	philo->waiting = 1;
	pthread_mutex_lock( &philo->fork_m); 
	pthread_mutex_lock( &philo->next->fork_m);
	philo->waiting = 0;
	if(!lock_check_life_data(philo))
			return 0;
	printf("%d philo %d take fork!\n%d philo %d take fork!\n",philo->now,philo->num ,philo->now,philo->num);
	printf("%d philo %d is eating\n" ,philo->now,philo->num);
	usleep(philo->t_eat);
	philo->last_eat = 0;
	philo->now += philo->t_eat;
	if(philo->next->waiting == 1)
	{
		philo->next->now = philo->now;
		philo->next->last_eat = philo->t_eat;
	}
	philo->num_eat += 1;
	philo->last_eat = philo->t_eat;
	unlock_check_life_data(philo);
	usleep(300);
	pthread_mutex_unlock(&philo->fork_m);
	pthread_mutex_unlock(&philo->next->fork_m);
	usleep(300);
	return 1;
}

void *rotine(void *tmp)
{
	t_list *philo;

	philo = (t_list*) tmp;
	while(1)
	{
		if(!eat(philo))
			break;
		if(!ft_sleep(philo))
			break;
		if(!think(philo))
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
		pthread_create(&tmp->eat_time, NULL,&rotine,tmp);
		tmp = tmp->next;
		i++;
	}
		i = 0;
	while(i <= tmp->philo_num)
	{
		pthread_join(tmp->eat_time,NULL);
		pthread_mutex_destroy(&tmp->fork_m);
		pthread_mutex_destroy(&tmp->death_p);
		tmp = tmp->next;
		i++;
	}
}


void	star(t_list *philo)
{
	// pthread_create(&philo->c_run, NULL,&check_life,philo);
		int_rotine(philo);
}