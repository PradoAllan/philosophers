/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:43:59 by aprado            #+#    #+#             */
/*   Updated: 2024/08/23 14:17:09 by aprado           ###   ########.fr       */
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

typedef struct s_main	t_main;

enum	e_errors
{
	NO_PARAMS = -1,
	BAD_PARAMS = -2,
	WRONG_PARAMS = -3
};

enum	e_state
{
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	FORK = 4,
	DIE = 5
};

typedef struct s_philo
{
	int					id;
	int					state;
	long				time_to_die;
	long				time_to_sleep;
	long				time_to_eat;
	int					times_eaten;
	int					meals_counter;
	long				last_meal_time;
	long				dying_at;
	t_main				*bag;
	struct s_philo		*next;
	struct s_philo		*prev;
}						t_philo;

struct s_main
{
	int	*arr;
	int	arr_size;
	t_philo	*head;
	t_philo	*tail;
};

/*----- Validation functions -----*/
int	check_param(char *s);
int	validate_input(int ac, char **av, t_main *bag);

/*----- linked list functions -----*/
void	print_philos(t_main *bag);
t_philo	*create_philo(int id, int *arr, t_main *bag);
void	create_list(t_main *bag);

/*----- Utils -----*/
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(int error);
long	ft_atol(const char *nptr);

#endif
