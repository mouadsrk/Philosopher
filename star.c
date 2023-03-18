/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/18 21:56:55 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int death(t_list *philo)
{
	t_list *tmp;
	tmp = philo;

	if(philo->head->death_satus == 1)
		return 1;
	while( tmp->num <= philo->philo_num)
	{
		if(tmp->last_eat >= philo->t_die)
			{
				if(philo->head->death_satus == 0)
				{
					printf("philo %d is death\n",tmp->num);
					philo->head->death_satus = 1;
				}
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


int lock_check_life_data(t_list *tmp)
{
	pthread_mutex_lock(&tmp->head->death_p);
	if(death(tmp) || ((max_eat(tmp) && tmp->max_eat != -1)))
		{
			pthread_mutex_unlock(&tmp->head->death_p);
			return 0;
		}
	pthread_mutex_unlock(&tmp->head->death_p);
	return 1;
}

int	think(t_list *philo)
{
	// if(!lock_check_life_data(philo))
	// 	return 0;
	printf("%d philo %d is thinking!\n" ,philo->now, philo->num);
	return 1;
}

int	ft_sleep(t_list *philo)
{
	// if(!lock_check_life_data(philo))
	// 	return 0;
	printf("%d philo %d is sleeping!\n" ,philo->now,philo->num);
	usleep(philo->t_sleep);
	// philo->now += philo->t_sleep;
	// philo->last_eat += philo->t_sleep;
		return 1;
}

int  eat(t_list *philo)
{
	// int i;
	// if(philo->num % 2 == 0 && philo->num != 1 && philo->head->eat_time == 0)
	// 	usleep(philo->t_eat);
	// // philo->waiting = 1;
	pthread_mutex_lock( &philo->fork_m); 
	printf("%d take fork \n", philo->num );
	pthread_mutex_lock( &philo->next->fork_m);
	// // philo->waiting = 0;
	// if(!lock_check_life_data(philo) || philo->num_eat == philo->max_eat)
	// {
	// 	pthread_mutex_unlock(&philo->fork_m);
	// 	pthread_mutex_unlock(&philo->next->fork_m);
	// 		return 0;
	// }
	// pthread_mutex_unlock(&philo->head->death_p);
	// printf("%d philo %d take fork!\n%d philo %d take fork!\n",philo->now,philo->num ,philo->now,philo->num);
	// printf("%d philo %d is eating\n" ,philo->now,philo->num);
	usleep(philo->t_eat);
	// philo->last_eat = 0;
	// // philo->now += philo->t_eat;
	// // if(philo->next->waiting == 1)
	// // {
	// // 	philo->next->now = philo->now;
	// // 	philo->next->last_eat = philo->t_eat;
	// // }
	// philo->num_eat += 1;
	// philo->last_eat = philo->t_eat;
	pthread_mutex_unlock(&philo->fork_m);
	pthread_mutex_unlock(&philo->next->fork_m);
	return 1;
}

void *rotine(void *tmp)
{
	t_list *philo;
	int i = 0;
	philo = (t_list*) tmp;
	while(i < 10)
	{
		if(!eat(philo))
		{
			// pthread_mutex_destroy(&philo->head->death_p);
			break;
		}
		if(!ft_sleep(philo))
		{
			// pthread_mutex_destroy(&philo->head->death_p);
			break;
		}
		if(!think(philo))
		{
			// pthread_mutex_destroy(&philo->head->death_p);
			break;
			i++;
			printf("iiiiiii>>>>>>===%d",i);
		}
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
		i = 1;
	while(i <= tmp->philo_num + 1)
	{
		pthread_join(tmp->eat_time,NULL);
		death(tmp);
		pthread_mutex_destroy(&tmp->fork_m);
		tmp = tmp->next;
		i++;
	}
}

void	star(t_list *philo)
{
		int_rotine(philo);
}