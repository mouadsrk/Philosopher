/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/13 05:17:47 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void Death(t_list *philo)
{
	t_list *tmp;
	tmp = philo;

	while( tmp->num <= philo->philo_num)
	{
		if(tmp->last_eat == philo->t_die)
			printf("philo %d is death",tmp->num);
		if( tmp->num == philo->philo_num)
			break;
		tmp = tmp->next;
	}
}


void	think(t_list *philo)
{
	// gettimeofday(&mv, NULL);
	// printf("%d philo %d  is thinking!\n",mv.tv_usec - tv.tv_usec, philo->num);
	printf("philo %d is thinking!\n" ,philo->num);
}

void	ft_sleep(t_list *philo)
{
	usleep(philo->t_sleep);
}

void*  eat(void *tmp)
{
	t_list *philo ;

	philo = (t_list *) tmp; 
	pthread_mutex_lock( &philo->fork_m);
	pthread_mutex_lock( &philo->next->fork_m);
	// gettimeofday(&mv, NULL);
	// printf("%d philo %d take fork!\n%d philo %d take fork!\n", mv.tv_usec - tv.tv_usec,philo->num, mv.tv_usec - tv.tv_usec, philo->num);
	// printf("%d philo %d is eating\n", mv.tv_usec - tv.tv_usec, philo->num);
	printf(" philo %d take fork!\n philo %d take fork!\n",philo->num ,philo->num);
	printf("philo %d is eating\n" ,philo->num);
	philo->num_eat += 1;
	usleep(philo->t_eat);
	// gettimeofday(&mv, NULL);
	// printf("%d philo %d  is sleeping!\n",mv.tv_usec - tv.tv_usec ,philo->num);
	printf(" philo %d is sleeping!\n" ,philo->num);
	pthread_mutex_unlock(&philo->fork_m);
	pthread_mutex_unlock(&philo->next->fork_m);
	philo->last_eat = 0;
	ft_sleep(philo);
	think(philo);
	return NULL;
}

void    take_fork(void *philo)
{
	int i;
	t_list *tmp;

	tmp = (t_list*) philo;
	i = 0;
	// gettimeofday(&tv, NULL);
	while(i < tmp->philo_num )
	{
			pthread_mutex_init(&tmp->fork_m, NULL);
			pthread_create(&tmp->eat_time, NULL,&eat,tmp);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = (t_list*) philo;
	while(i <= tmp->philo_num)
	{
		pthread_join(tmp->eat_time,NULL);
		pthread_mutex_destroy(&tmp->fork_m);
		tmp = tmp->next;
		i++;
	}
}

void	star(t_list *philo)
{

	take_fork(philo);
	
}



