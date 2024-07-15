/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:48 by aprado            #+#    #+#             */
/*   Updated: 2024/07/15 15:50:22 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

/*
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
}
*/

/*
int	check_param(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if ('0' <= s[i] && s[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	validate_input(int ac, char **av, t_main *bag)
{
	int	i;
	long		nbr;

	i = 0;
	if (ac < 5)
		return (ft_puterror(NO_PARAMS), 0);
	else if (ac > 6)
		return (ft_puterror(BAD_PARAMS), 0);
	while (av[++i])
		if (!check_param(av[i]))
			return (ft_puterror(WRONG_PARAMS), 0);
	i = 0;
	bag->arr = malloc(sizeof(int) * (ac - 1));
	if (!bag->arr)
		return (0);
	while (av[++i])
	{
		nbr = ft_atol(av[i]);
		if (nbr > 2147483647 || nbr < -2147483648)
			return (free(bag->arr), ft_puterror(WRONG_PARAMS), 0);
		else
			bag->arr[i - 1] = nbr;
	}
	return (1);
}
*/

static void	populate_bag(t_main *bag)
{
	bag->arr = NULL;
}

int	main(int ac, char **av)
{
	t_main	bag;

	populate_bag(&bag);
	if (!validate_input(ac, av, &bag))
		return (0);
	printf("OK!\n");
	free(bag.arr);
	return (1);
}
