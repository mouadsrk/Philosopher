/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:27:04 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/17 13:19:39 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef PHILO_H
# define PHILO_H



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

struct timeval tv ,mv;


typedef struct s_list
{
	// pthread_mutex_t print;
	// pthread_t		c_run;
	pthread_mutex_t fork_m;
	pthread_mutex_t wait;
	pthread_mutex_t death_p;
	pthread_t		eat_time;
	int				num;
	int				num_eat;
	int				max_eat;
	int 			philo_num;
	int				waiting;
	useconds_t 		t_die;
	useconds_t 		t_eat;
	useconds_t		t_sleep;
	useconds_t		now;
	useconds_t		last_eat;
	struct s_list	*next;
	struct s_list	*head;
}	t_list;

int	ft_isdigit(int c);
void	exit_error(char *str);
void	ft_lstclear(t_list	**lst);
t_list	*ft_lstnew(int content);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	star(t_list *philo);
void	ft_putnbr(int n);

# endif
