/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:27:04 by mserrouk          #+#    #+#             */
/*   Updated: 2023/04/01 23:49:12 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include<fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct s_sem
{
	sem_t *forks;
	sem_t *print;


}	t_sem;




typedef struct s_list
{
	pthread_mutex_t	death_p;
	pthread_mutex_t check_last_eat;
	pthread_mutex_t check_max_eat;
	pthread_t		death_check;
	pid_t			philo_rotine;
	int				status;
	int				death_satus;
	int				num;
	int				max_eat;
	int 			philo_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	long			beging;
	long			last_eat;
	struct s_list	*next;
	struct s_list	*head;
	t_sem  			*sema;
}	t_list;

long time_init(void);
int	ft_isdigit(int c);
void	ft_usleep(long int time_in_ms) ;
void	exit_error(char *str);
void	ft_lstclear(t_list	**lst);
t_list	*ft_lstnew(int content);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	star(t_list *philo);
void	ft_putnbr(int n);

# endif
