/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:47:56 by aprado            #+#    #+#             */
/*   Updated: 2024/08/14 17:38:26 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	finish_forks(t_main *bag)
{
	int	i;

	i = 0;
	while (i < bag->arr[0])
	{
		pthread_mutex_destroy(&bag->forks[i].fork);
		i++;
	}
}

void	start_forks(t_main *bag)
{
	int	forks;
	int	i;

	if (!bag)
		return ;
	forks = 1;
	i = 0;
	bag->forks = malloc(sizeof(t_fork) * (bag->arr[0]));
	if (!bag->forks)
		return ;
	while (i < bag->arr[0])
	{
		pthread_mutex_init(&bag->forks[i].fork, NULL);
		bag->forks[i].fork_id = forks;
		bag->forks[i].fork_status = 1;
		forks++;
		i++;
	}
}

long	ft_atol(const char *nptr)
{
	long	nbr;
	int		i;
	int		sign;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_puterror(int error)
{
	if (error == NO_PARAMS)
		ft_putstr_fd("Philo: Missing parameters.\n", 2);
	else if (error == BAD_PARAMS)
	{
		ft_putstr_fd("Philo: Not more than 5 ", 2);
		ft_putstr_fd("and less than 4 parameters.\n", 2);
	}
	else if (error == WRONG_PARAMS)
		ft_putstr_fd("Philo: Must be a positive integer number.\n", 2);
	else
		ft_putstr_fd("Philo: Error.\n", 2);
	ft_putstr_fd("Philo: Try inputs like this: ", 2);
	ft_putstr_fd("./philo 80 200 300 400 5\n", 2);
}
