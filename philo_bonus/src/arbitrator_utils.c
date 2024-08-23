/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:28:36 by aprado            #+#    #+#             */
/*   Updated: 2024/08/21 10:55:25 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

int	is_philo_full(t_philo *philo, int n_eat)
{
	int	value;

	if (n_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_mtx);
	if (philo->meals_counter < n_eat)
		value = 0;
	else
		value = 1;
	pthread_mutex_unlock(&philo->meal_mtx);
	return (value);
}

void	stop_dinner(t_main *bag)
{
	pthread_mutex_lock(&bag->end_mutex);
	bag->end_dinner = 1;
	pthread_mutex_unlock(&bag->end_mutex);
}

int	all_philos_full(t_main *bag, int n_eat)
{
	t_philo	*aux;
	int		i;

	i = 0;
	aux = bag->head;
	while (i < bag->arr[0])
	{
		if (!is_philo_full(aux, n_eat))
			return (0);
		i++;
		aux = aux->next;
	}
	return (1);
}
