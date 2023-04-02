/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/02 00:47:48 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_printf(t_list *philo,char *str)
{
	long now;

	// pthread_mutex_lock(&philo->death_p);
	// if(philo->death_satus == 1)
	// {
	// 	ft_usleep(1);
	// 	pthread_mutex_unlock(&philo->death_p);
	// 	exit(1);
	// }
	// pthread_mutex_unlock(&philo->death_p);

	sem_wait(philo->sema->print);
	now = time_init() - philo->beging;
	printf("%ld philo %d %s\n" ,now, philo->num,str);
	sem_post(philo->sema->print);
}

int death(t_list *philo )
{
	long now;

	
	pthread_mutex_lock(&philo->death_p);
	now = time_init();
	if(now - philo->last_eat >= philo->t_die)
	{
		sem_wait(philo->sema->print);
		
		printf("%ld philo %d  is dead\n" ,now - philo->beging , philo->num);
		// sem_post(philo->sema->print);
		exit(1);
	}
	pthread_mutex_unlock(&philo->death_p);
	return 0;
}

void *check_life(void * tmp )
{

	ft_usleep(((t_list *)tmp)->t_die - 1);
	// usleep(100);
	while(1)
	{
		if(death(tmp ))
			return NULL;
		pthread_mutex_lock(&((t_list*)tmp)->check_max_eat);
		if (((t_list *)tmp)->max_eat == -2)
		{
			pthread_mutex_unlock(&((t_list*)tmp)->check_max_eat);
			
			return NULL;
		}
			pthread_mutex_unlock(&((t_list*)tmp)->check_max_eat);
	}
	return NULL;
}

int	think(t_list *philo )
{
	long now;
	
	// pthread_mutex_lock(&philo->death_p);
	// if(philo->death_satus == 1)
	// {
	// 	ft_usleep(1);
	// 	pthread_mutex_unlock(&philo->death_p);
	// 	exit(1);
	// }
	// pthread_mutex_unlock(&philo->death_p);
	ft_printf(philo, "is sleeping");
	return 1;
}

int	ft_sleep(t_list *philo)
{
	long now;

	// pthread_mutex_lock(&philo->death_p);
	// if(philo->death_satus == 1)
	// {
	// 	ft_usleep(1);
	// 	pthread_mutex_unlock(&philo->death_p);
	// 	exit(1);
	// }
	// pthread_mutex_unlock(&philo->death_p);
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->t_sleep );
		return 1;
}

int  eat(t_list *philo)
{

	sem_wait(philo->sema->forks);
	ft_printf(philo, "take fork");
	sem_wait(philo->sema->forks);
	ft_printf(philo, "take fork");
	pthread_mutex_lock(&philo->death_p);
	philo->last_eat = time_init();
	pthread_mutex_unlock(&philo->death_p);
	ft_printf(philo, "is eating");
	ft_usleep(philo->t_eat);
	sem_post(philo->sema->forks);
	sem_post(philo->sema->forks);
	return 1;
}

void rotine(t_list *tmp )
{
	int i;
	int j;

	i = 1;

	// pthread_mutex_init(&tmp->check_max_eat, NULL);
	pthread_mutex_init(&tmp->death_p, NULL);
	pthread_create(&tmp->death_check, NULL,&check_life,tmp);
	pthread_mutex_lock(&tmp->death_p);
	tmp->last_eat = time_init();
	pthread_mutex_unlock(&tmp->death_p);
	j = tmp->max_eat;
	while((i <= j && j != -1) || (j == -1))
	{
		// if (tmp->max_eat == tmp.)
		eat(tmp);
		i++;
		if (i > j && j != -1)
			exit(0);
		ft_sleep( tmp);
		think(tmp);
	}
	// if(i > j)
	// {

	// 	pthread_mutex_lock(&((t_list*)tmp)->check_max_eat);
	// 	(tmp)->max_eat = -2;
	// 	pthread_mutex_unlock(&((t_list*)tmp)->check_max_eat);
	// }
	return ;
	// exit(0);
}

void    int_rotine(t_list *tmp)
{
	int i;
	long time;
	t_sem var;
	i = 0;
	sem_unlink("fork");
	var.forks = sem_open("fork",O_CREAT | O_EXCL , 777,tmp->philo_num);
	sem_unlink("print");
	var.print = sem_open("print",O_CREAT | O_EXCL , 777,1);
	tmp->beging = time_init();
	while(i < tmp->philo_num)
	{
		tmp->sema = &var;
		tmp->beging = tmp->head->beging;

		tmp->philo_rotine = fork();

		if(tmp->philo_rotine == 0)
		{
			rotine(tmp);
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while(i < tmp->philo_num)
	{
		waitpid(-1 ,&tmp->status, 0);
		if(WEXITSTATUS(tmp->status) == 1)
		{
			tmp = tmp->head;
			i = 0;
			while(i < tmp->philo_num)
			{
				kill(tmp->philo_rotine, SIGKILL);
				i++;
				tmp = tmp->next;
			}
			exit(0);
		}
		tmp = tmp->next;
		i++;
	}
}

void	star(t_list *philo)
{
	int_rotine(philo);
}