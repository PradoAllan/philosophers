/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:38:48 by aprado            #+#    #+#             */
/*   Updated: 2024/07/12 18:44:18 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 2)
	{
		printf("Try to input something.\n");
		return (0);
	}
	while (av[i])
	{
		printf("strings :%s:\n", av[i]);
		i++;
	}
	return (1);
}
