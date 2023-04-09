/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:42:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/09 01:43:31 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(t_list *p, char *str)
{
	long	now;

	if (time_init() - p->last_eat >= p->t_die)
	{
		sem_wait(p->sema->print);
		printf("%ld philo %d is dead\n", time_init() - p->beging, p->num);
		exit(1);
	}
	sem_wait(p->sema->print);
	now = time_init() - p->beging;
	printf("%ld philo %d %s\n", now, p->num, str);
	sem_post(p->sema->print);
}

int	eat_sleep_think(t_list *philo, int i)
{
	if (philo->num % 2 == 0 && i == 1)
		ft_usleep(60, philo);
	sem_wait(philo->sema->forks);
	ft_printf(philo, "take fork");
	if ((philo->t_eat * 2 >= philo->t_die && philo->num % 2 == 0 && i == 1)
		|| philo->philo_num == 1)
	{
		ft_usleep(philo->t_die + 1, philo);
		exit(1);
	}
	if (philo->philo_num == 1)
		exit(1);
	sem_wait(philo->sema->forks);
	ft_printf(philo, "take fork");
	sem_wait(philo->sema->death_p);
	philo->last_eat = time_init();
	sem_post(philo->sema->death_p);
	ft_printf(philo, "is eating");
	ft_usleep(philo->t_eat, philo);
	sem_post(philo->sema->forks);
	sem_post(philo->sema->forks);
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->t_sleep, philo);
	ft_printf(philo, "is thinking");
	return (1);
}

void	rotine(t_list *tmp )
{
	int	i;
	int	j;

	i = 1;
	sem_wait(tmp->sema->death_p);
	tmp->last_eat = time_init();
	sem_post(tmp->sema->death_p);
	j = tmp->max_eat;
	while ((i <= j && j != -1) || (j == -1))
	{
		eat_sleep_think(tmp, i);
		i++;
	}
	exit(0);
}

void	star_norm(t_list *tmp)
{
	int	i;

	i = 0;
	while (i < tmp->philo_num)
	{
		waitpid(-1, &tmp->status, 0);
		if (WEXITSTATUS(tmp->status) == 1)
		{
			tmp = tmp->head;
			i = 0;
			while (i < tmp->philo_num)
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

void	star(t_list *tmp)
{
	int		i;
	t_sem	var;

	i = 0;
	sem_unlink("fork");
	var.forks = sem_open("fork", O_CREAT | O_EXCL, 777, tmp->philo_num);
	sem_unlink("print");
	var.print = sem_open("print", O_CREAT | O_EXCL, 777, 1);
	sem_unlink("die");
	var.death_p = sem_open("die", O_CREAT | O_EXCL, 777, 1);
	tmp->beging = time_init();
	while (i < tmp->philo_num)
	{
		tmp->sema = &var;
		tmp->beging = tmp->head->beging;
		tmp->philo_rotine = fork();
		if (tmp->philo_rotine == 0)
			rotine(tmp);
		tmp = tmp->next;
		i++;
	}
	star_norm(tmp);
}
