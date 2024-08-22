/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:40:43 by aprado            #+#    #+#             */
/*   Updated: 2024/08/22 13:31:23 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/philo.h"

int	get_philo_state(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->state_mtx);
	value = philo->state;
	pthread_mutex_unlock(&philo->state_mtx);
	return (value);
}

long	get_dying_at(t_philo *philo)
{
	long	value;

	pthread_mutex_lock(&philo->dying_mtx);
	value = philo->dying_at;
	pthread_mutex_unlock(&philo->dying_mtx);
	return (value);
}
