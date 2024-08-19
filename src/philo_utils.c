/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:34:02 by aprado            #+#    #+#             */
/*   Updated: 2024/08/19 14:47:42 by aprado           ###   ########.fr       */
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

/*
int	get_philo_state(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->state_mtx);
	value = philo->state;
	pthread_mutex_unlock(&philo->state_mtx);
	return (value);
}
*/

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

/*
int	philo_take_fork(t_philo *philo, int which)
{
	if (which == 2)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		if (philo->right_fork->fork_status)
		{
			philo->right_fork->fork_status = 0;
			set_philo_state(philo, FORK);
			print_philo_status(philo);
			pthread_mutex_unlock(&philo->right_fork->fork);
			return (1);
		}
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (0);
	}
	pthread_mutex_lock(&philo->left_fork->fork);
	if (philo->left_fork->fork_status)
	{
		philo->left_fork->fork_status = 0;
		set_philo_state(philo, FORK);
		print_philo_status(philo);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (0);
}
*/

void	increment_meals_counter(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->meal_mtx);
}

/*
void	set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->last_meal_mtx);
}

int	philo_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (get_philo_state(philo) != DIE && i != 2)
	{
		if (check_dinner_status(philo->bag))
			break ;
		if (i == 0)
			i += philo_take_fork(philo, 1);
		else if (i == 1)
			i += philo_take_fork(philo, 2);
	}
	if (i == 2)
	{
		set_philo_state(philo, EAT);
		print_philo_status(philo);
		increment_meals_counter(philo);
		ft_usleep(philo->time_to_eat);
		set_last_meal_time(philo);
		return (1);
	}
	return (0);
}

void	stop_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	philo->right_fork->fork_status = 1;
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	philo->left_fork->fork_status = 1;
	pthread_mutex_unlock(&philo->left_fork->fork);
	set_philo_state(philo, SLEEP);
}
*/
