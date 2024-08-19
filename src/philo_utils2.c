/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:46:25 by aprado            #+#    #+#             */
/*   Updated: 2024/08/19 17:29:44 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	set_last_meal_time_to_zero(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal_time = 0;
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
		set_last_meal_time_to_zero(philo);
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
