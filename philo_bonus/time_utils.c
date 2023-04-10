/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:13:12 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/10 01:48:26 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	time_init(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int time_in_ms, t_list *p)
{
	long int	start_time;

	start_time = 0;
	start_time = time_init();
	while (((time_init()) - start_time) < time_in_ms)
	{
		sem_wait(p->sema->death_p);
		if (time_init() - p->last_eat >= p->t_die)
		{
			sem_wait(p->sema->print);
			printf("%ld %d died\n", time_init() - p->beging, p->num);
			exit(1);
		}
		sem_post(p->sema->death_p);
		usleep(100);
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
