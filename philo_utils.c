/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:27:02 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/19 23:17:44 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = time_init();
	while ((time_init() - start_time) < time_in_ms)
		usleep(100);
}

int ft_strlen(char *str)
{
	int i;

	i =0;
	while(str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					s;
	unsigned long long	r;

	r = 0;
	s = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + *str - 48;
		if ((r > 2147483647 && s == 1) || (r > 2147483648 && s == -1))
			exit_error("Error\n");
		str++;
	}
	return ((int)(r * s));
}

t_list	*ft_lstnew(int content)
{
	t_list	*s;

	s = malloc (sizeof(t_list));
	if (s == NULL)
		return (NULL);
	s->max_eat = -1; 
	s->num_eat = 0;
	s->now = 0;
	s->num = content;
	s->next = NULL;
	return (s);
}

void	ft_lstclear(t_list	**lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
	}
}

void ft_putchar(char c)
{
	write(1, &c, 1 );
}

long time_init(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}



