/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:40:43 by aprado            #+#    #+#             */
/*   Updated: 2024/08/19 14:43:51 by aprado           ###   ########.fr       */
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
