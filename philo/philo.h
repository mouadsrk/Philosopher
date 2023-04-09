/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:27:04 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/09 21:47:43 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_list
{
	pthread_mutex_t		check_max_eat;
	pthread_mutex_t		check_last_eat;
	pthread_mutex_t		fork_m;
	pthread_mutex_t		death_p;
	pthread_mutex_t		print;
	pthread_t			eat_time;
	int					death_satus;
	int					num;
	int					max_eat;
	int					philo_num;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	long				beging;
	long				last_eat;
	struct s_list		*next;
	struct s_list		*head;
}	t_list;

void	ft_printf(t_list *p, char *str, long beging);
long	time_init(void);
int		ft_isdigit(int c);
void	ft_usleep(long int time_in_ms);
void	ft_lstclear(t_list	**lst);
void	*rotine(void *tmp);
t_list	*ft_lstnew(int content, int arc, char **argv);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	star(t_list *philo);
void	ft_putnbr(int n);

#endif
