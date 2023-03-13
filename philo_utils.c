/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserrouk <mserrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:27:02 by mserrouk          #+#    #+#             */
/*   Updated: 2023/03/13 10:25:09 by mserrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

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
	s->act = 0;
	s->waiting = 1;
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

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
	}
	if (n <= 9)
		ft_putchar(n + 48);
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
}

