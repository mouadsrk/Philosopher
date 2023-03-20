/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/20 01:00:33 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int death(t_list *philo , long begin)
{
	long now;

	now = time_init() - begin;
	philo = philo->head;
	while( philo->num <= philo->philo_num)
	{
		pthread_mutex_lock(&philo->check_last_eat);
		if(now - philo->last_eat >= philo->t_die)
			{
				pthread_mutex_unlock(&philo->check_last_eat);
				// printf("now %ld  begin%ld \n",now,begin);
				ft_usleep(2);	
				printf("%ld philo %d is death\n",now,philo->num);
				pthread_mutex_lock(&philo->head->death_p);
				philo->head->death_satus = 1;
				pthread_mutex_unlock(&philo->head->death_p);
				// return 1;
				exit(0);
			}
		pthread_mutex_unlock(&philo->check_last_eat);
		if( philo->num == philo->philo_num)
			break;
		philo = philo->next;
	}
	return 0;
}

// int max_eat(t_list *philo)
// {
// 	int i;

// 	i = 0;
// 	while(i < philo->philo_num)
// 	{
// 		pthread_mutex_lock(&philo->check_num_eat);
// 		if(philo->num_eat < philo->max_eat)
// 		{
// 			pthread_mutex_unlock(&philo->check_num_eat);
// 			pthread_mutex_unlock(&philo->head->death_p);
// 			return 0;
// 		}
// 		pthread_mutex_unlock(&philo->check_num_eat);
// 		philo = philo->next;
// 		i++;
// 	}
// 	return 1;
// }



int	think(t_list *philo , long beging)
{
	long now;

	pthread_mutex_lock(&philo->head->death_p);
	if(philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		return 0;
	}
	pthread_mutex_unlock(&philo->head->death_p);
	now = time_init() - beging;
	printf("%ld philo %d is thinking!\n" ,now, philo->num);
	return 1;
}

int	ft_sleep(t_list *philo , long beging)
{
	long now;

	pthread_mutex_lock(&philo->head->death_p);
	if(philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		return 0;
	}
	pthread_mutex_unlock(&philo->head->death_p);
	now = time_init() - beging;
	printf("%ld philo %d is sleeping!\n" ,now,philo->num);
	ft_usleep(philo->t_sleep);
		return 1;
}

int  eat(t_list *philo , long beging , int i)
{
	long now;

	if(philo->num % 2 == 0 && philo->num != 1 && i == 0)
		ft_usleep(philo->t_eat);
	pthread_mutex_lock( &philo->fork_m); 
	pthread_mutex_lock( &philo->next->fork_m);
	pthread_mutex_lock(&philo->check_last_eat);
	now = time_init() - beging;
	philo->last_eat = now;
	pthread_mutex_unlock(&philo->check_last_eat);
	pthread_mutex_lock(&philo->head->death_p);
	if(philo->head->death_satus == 1)
	{
		pthread_mutex_unlock(&philo->head->death_p);
		pthread_mutex_unlock(&philo->fork_m);
		pthread_mutex_unlock(&philo->next->fork_m);
		return 0;
	}
	pthread_mutex_unlock(&philo->head->death_p);
	printf("%ld philo %d take fork!\n%ld philo %d take fork!\n",now,philo->num ,now,philo->num);
	printf("%ld philo %d is eating\n" ,now,philo->num);
	ft_usleep(philo->t_eat);
	pthread_mutex_unlock(&philo->fork_m);
	pthread_mutex_unlock(&philo->next->fork_m);
	return 1;
}

void *rotine(void *tmp)
{
	int i;
	int j;
	long beging;

	i = 0;
	pthread_mutex_lock(&((t_list *)tmp)->check_max_eat);
	beging = ((t_list *)tmp)->beging;
	// printf("%ld\n",beging);
	j = ((t_list *)tmp)->max_eat;
	pthread_mutex_unlock(&((t_list *)tmp)->check_max_eat);
	while((i <= j && j != -1) || (i <= 2147483647 && j == -1))
	{
		if(!eat((t_list*) tmp , beging , i))
			break;
		i++;
		if (i == j)
			break;
		if(!ft_sleep((t_list*) tmp , beging))
			break;
		if(!think((t_list*) tmp, beging))
			break;
	}
	if(i == j)
	{
		// printf("done\n");
		pthread_mutex_lock(&((t_list *)tmp)->check_max_eat);
		((t_list *)tmp)->max_eat = -2;
		pthread_mutex_unlock(&((t_list *)tmp)->check_max_eat);
	}
	return NULL;
}

void check_life_(t_list * tmp, long begin)
{
	int i;
	ft_usleep(tmp->t_die);

	while(1)
	{
		// printf(">>>>>%ld\n",begin);
		if(death(tmp, begin))
			return;
		i = 1;
		tmp = tmp->head;
		pthread_mutex_lock(&(tmp)->check_max_eat);
		if (tmp->max_eat != -1)
		{
			while(tmp->max_eat == -2 && i <= tmp->philo_num)
				{
					pthread_mutex_unlock(&(tmp)->check_max_eat);
					tmp = tmp->next;
					pthread_mutex_lock(&(tmp)->check_max_eat);
					i++;
				}
			if (i == tmp->philo_num + 1)
			{
				pthread_mutex_unlock(&(tmp)->check_max_eat);
				return;
			}
			else
				pthread_mutex_unlock(&(tmp)->check_max_eat);
		}
		else
		pthread_mutex_unlock(&(tmp)->check_max_eat);
	}
}

void    int_rotine(t_list *tmp)
{
	int i;
	long time;
	i = 0;
	pthread_mutex_init(&tmp->death_p, NULL);
	while(i < tmp->philo_num)
	{
		pthread_mutex_init(&tmp->fork_m, NULL);
		pthread_mutex_init(&tmp->check_last_eat, NULL);
		pthread_mutex_init(&tmp->check_max_eat, NULL);
		tmp->beging = time_init();
		pthread_create(&tmp->eat_time, NULL,&rotine,tmp);
		tmp = tmp->next;
		i++;
	}
	time = tmp->head->beging;
	check_life_(tmp->head, time);
	// usleep(1000 * 1000 * 4);
	i = 0;
	while(i < tmp->philo_num)
	{
		pthread_mutex_destroy(&tmp->fork_m);
		pthread_mutex_destroy(&tmp->check_last_eat);
		pthread_mutex_destroy(&tmp->check_max_eat);
		tmp = tmp->next;
		i++;
	}

	// usleep(1000 * 1000 * 10);
	// tf_thead_datach();
	// while(1)
	pthread_mutex_destroy(&tmp->death_p);
}

void	star(t_list *philo)
{
	int_rotine(philo);	
}