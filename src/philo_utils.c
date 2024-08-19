/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:34:02 by aprado            #+#    #+#             */
/*   Updated: 2024/08/19 14:55:53 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	print_philo_status(t_philo *philo)
{
	long	current;
	int		id;
	int		state;

	pthread_mutex_lock(&philo->print_mtx);
	current = get_time() - philo->bag->start_timestamp;
	id = philo->id;
	state = get_philo_state(philo);
	if (state == EAT)
		printf("%ld %i %s\n", current, id, MSG_EAT);
	else if (state == SLEEP)
		printf("%ld %i %s\n", current, id, MSG_SLEEP);
	else if (state == THINK)
		printf("%ld %i %s\n", current, id, MSG_THINK);
	else if (state == FORK)
		printf("%ld %i %s\n", current, id, MSG_FORK);
	else
		printf("%ld %i %s\n", current, id, MSG_DIE);
	pthread_mutex_unlock(&philo->print_mtx);
}

int	check_dinner_status(t_main *bag)
{
	int	value;

	pthread_mutex_lock(&bag->end_mutex);
	if (bag->end_dinner == 1)
		value = 1;
	else
		value = 0;
	pthread_mutex_unlock(&bag->end_mutex);
	return (value);
}

int	loop_helper(t_philo *philo)
{
	if (check_dinner_status(philo->bag) 
			|| get_philo_state(philo) == DIE
			|| is_philo_full(philo, philo->times_eaten))
		return (0);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (check_dinner_status(philo->bag))
	{
		//set_philo_state(philo, SLEEP);
		//print_philo_status(philo);
		return (0);
	}
	set_philo_state(philo, SLEEP);
	print_philo_status(philo);
	ft_usleep(philo->time_to_sleep);
	set_philo_state(philo, THINK);
	return (1);
}

void	increment_meals_counter(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->meal_mtx);
}
