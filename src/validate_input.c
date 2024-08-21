/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:41:58 by aprado            #+#    #+#             */
/*   Updated: 2024/08/21 10:59:28 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

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
	long	nbr;
	int		i;

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
		if (nbr > 2147483647 || nbr < -2147483648 || nbr == 0)
			return (free(bag->arr), ft_puterror(WRONG_PARAMS), 0);
		else
			bag->arr[i - 1] = nbr;
	}
	return (1);
}
