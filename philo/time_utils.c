/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:30:28 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/09 21:38:58 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	time_init(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = time_init();
	while ((time_init() - start_time) < time_in_ms)
		usleep(100);
}

void	ft_printf(t_list *p, char *str, long beging)
{
	pthread_mutex_lock(&p->head->print);
	printf("%ld %d %s\n", time_init() - beging, p->num, str);
	pthread_mutex_unlock(&p->head->print);
}
