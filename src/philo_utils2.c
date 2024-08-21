/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:46:25 by aprado            #+#    #+#             */
/*   Updated: 2024/08/21 10:53:24 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

int	am_i_dead(t_philo *philo)
{
	if (check_dinner_status(philo->bag))
		return (1);
	pthread_mutex_lock(&philo->dying_mtx);
	if (philo->dying_at <= get_time())
	{
		set_philo_state(philo, DIE);
		pthread_mutex_unlock(&philo->dying_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->dying_mtx);
	return (0);
}

int	philo_take_right_fork(t_philo *philo)
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

int	philo_take_left_fork(t_philo *philo)
{
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

int	philo_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (!am_i_dead(philo) && i != 2)
	{
		if (i == 0)
			i += philo_take_right_fork(philo);
		else
			i += philo_take_left_fork(philo);
	}
	if (i == 2)
	{
		set_philo_state(philo, EAT);
		print_philo_status(philo);
		increment_meals_counter(philo);
		philo->dying_at = get_time() + philo->time_to_die;
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
