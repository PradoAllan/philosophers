/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:41:04 by aprado            #+#    #+#             */
/*   Updated: 2024/08/22 13:31:10 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

void	set_philo_state(t_philo *philo, int new_state)
{
	pthread_mutex_lock(&philo->state_mtx);
	philo->state = new_state;
	pthread_mutex_unlock(&philo->state_mtx);
}

void	set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->last_meal_mtx);
}

void	set_dying_at(t_philo *philo)
{
	pthread_mutex_lock(&philo->dying_mtx);
	philo->dying_at = get_time() + philo->time_to_die;
	pthread_mutex_unlock(&philo->dying_mtx);
}
