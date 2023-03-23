/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:08:05 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/20 19:09:23 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void exit_error(char *str)
{
	write(1,str,ft_strlen(str));
	exit(1);
}


void data_make(int arc, char ** argv, t_list **philo)
{
	int i;
	
	t_list *tmp;
	t_list *tmp2;
	i = 1;
	(*philo) = ft_lstnew(1);
	(*philo)->philo_num = ft_atoi(argv[1]);
	(*philo)->t_die = (useconds_t )ft_atoi(argv[2]);
	(*philo)->t_eat = (useconds_t ) ft_atoi(argv[3]);
	(*philo)->t_sleep = (useconds_t )ft_atoi(argv[4]);
	if( arc == 6)
		(*philo)->max_eat = ft_atoi(argv[5]);
	tmp = *philo;
	while(++i <= (*philo)->philo_num)
	{
		tmp2 = tmp;
		tmp->next = ft_lstnew(i);
		tmp = tmp->next;
		tmp->t_die = (*philo)->t_die ;
		tmp->t_eat = (*philo)->t_eat ;
		tmp->t_sleep = (*philo)->t_sleep;
		tmp->max_eat = (*philo)->max_eat; 
		tmp->philo_num = (*philo)->philo_num ;
		tmp->head = (*philo);
	}
	tmp->next = *philo;
	(*philo)->death_satus = 0;
	(*philo)->head = (*philo);
}

void check_arg(int arc, char **argv)
{
	int i;
	int j;

	i = 1;
	while(i < arc)
	{
		j = 0;
		while(argv[i][j])
		{
			if(ft_isdigit(argv[i][j]) == 0)
				exit_error("error\n");
			j++;
		}
		i++;
	}
}


int main (int arc , char ** argv)
{
	// int fd = open("txt", O_CREAT | O_WRONLY | O_TRUNC ,0777 );
	// dup2(fd,1);
	// close(fd);
	t_list	*philo;
	t_list *tmp;
	int i;

	i = 0;
	if(arc != 5 && arc != 6)
		exit_error("error\n");
	check_arg(arc, argv);
	data_make(arc , argv, &philo);
	tmp = philo;
	star(philo);
}




