/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:43:59 by aprado            #+#    #+#             */
/*   Updated: 2024/08/23 12:11:43 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h> // sem_open, sem_close, sem_wait, sem_post, sem_unlink
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE "died"

enum	e_errors
{
	NO_PARAMS = -1,
	BAD_PARAMS = -2,
	WRONG_PARAMS = -3
};

typedef struct s_main
{
	int	*arr;
	int	arr_size;
}		t_main;

/*----- Validation functions -----*/
int	check_param(char *s);
int	validate_input(int ac, char **av, t_main *bag);

/*----- Utils -----*/
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(int error);
long	ft_atol(const char *nptr);

#endif
