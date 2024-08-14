/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:28:36 by aprado            #+#    #+#             */
/*   Updated: 2024/08/14 17:48:18 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"
//--- INSTRUCOES ---
// 1 argumento => numero de filosofos e de garfos.
// 2 argumento => tempo para morrer (em ms)
// 3 argumento => tempo para comer (em ms)
// 4 argumento => tempo para dormir (em ms)
// 5 argumento => numero de vezes que um filosofo deve comer (opcional)

void	set_philo_state(t_philo *philo, int new_state)
{
	pthread_mutex_lock(&philo->state_mtx);
	philo->state = new_state;
	pthread_mutex_unlock(&philo->state_mtx);
}

int	is_philo_dead(t_philo *philo, int time)
{
	long	current;
	int		value;

	current = get_time();
	pthread_mutex_lock(&philo->last_meal_mtx);
	if ((current - philo->last_meal_time + 10) >= time)
		value = 1;
	else
		value = 0;
	pthread_mutex_unlock(&philo->last_meal_mtx);
	if (value)
		set_philo_state(philo, DIE);
	return (value);
}

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
