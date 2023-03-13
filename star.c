/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/13 11:32:47 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int Death(t_list *philo)
{
	t_list *tmp;
	tmp = philo;

	while( tmp->num <= philo->philo_num)
	{
		if(tmp->last_eat >= philo->t_die)
			{
			printf("philo %d is death",tmp->num);
				exit(0);
			}
		if( tmp->num == philo->philo_num)
			break;
		tmp = tmp->next;
	}
	return 0;
}


void	think(t_list *philo)
{
	// gettimeofday(&mv, NULL);
	// printf("%d philo %d  is thinking!\n",mv.tv_usec - tv.tv_usec, philo->num);
	philo->act += 1;
	printf("%d philo %d is thinking!\n" ,philo->now, philo->num);
}

void	ft_sleep(t_list *philo)
{
	philo->act += 1;
	printf("%d philo %d is sleeping!\n" ,philo->now,philo->num);
	usleep(philo->t_sleep);
	philo->now += philo->t_sleep;
	philo->last_eat += philo->t_sleep;
	philo->waiting = 1;
}

void*  eat(void *tmp)
{
	t_list *philo ;

	philo = (t_list *) tmp;
	if(philo->num % 2 == 0 && philo->num != 1)
		usleep(400);
	pthread_mutex_lock( &philo->fork_m);
	pthread_mutex_lock( &philo->next->fork_m);
	philo->waiting = 0;
	philo->act += 1;
	printf("%d philo %d take fork!\n%d philo %d take fork!\n",philo->now,philo->num ,philo->now,philo->num);
	printf("%d philo %d is eating\n" ,philo->now,philo->num);
	usleep(philo->t_eat);
	philo->now += philo->t_eat;
	if(philo->next->waiting == 1)
		philo->next->now = philo->now;
	philo->num_eat += 1;
	pthread_mutex_unlock(&philo->fork_m);
	pthread_mutex_unlock(&philo->next->fork_m);
	philo->last_eat = 0;
	ft_sleep(philo);
	think(philo);
	return NULL;
}

void    star_rotine(void *philo)
{
	int i;
	t_list *tmp;

	tmp = (t_list*) philo;
	// gettimeofday(&tv, NULL);
	i = 0;
	while(i < tmp->philo_num)
	{
		pthread_mutex_init(&tmp->fork_m, NULL);
		pthread_create(&tmp->eat_time, NULL,&eat,tmp);
		tmp = tmp->next;
		i++;
	}
		i = 0;
	while(i <= tmp->philo_num)
	{
		pthread_join(tmp->eat_time,NULL);
		pthread_mutex_destroy(&tmp->fork_m);
		tmp = tmp->next;
		i++;
	}
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


void *check_rotine(void *philo)
{
	t_list *tmp;

	tmp = (t_list*) philo;
	while(!Death(philo) && ((!max_eat(philo) && tmp->max_eat != -1) || tmp->max_eat == -1 ) )
		star_rotine(philo);
	exit(0);
	return NULL;
}


void	star(t_list *philo)
{
	pthread_create(&philo->c_run, NULL,&check_rotine,philo);
	pthread_join(philo->c_run,NULL);
	exit(0);
}