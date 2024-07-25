/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:42:12 by aprado            #+#    #+#             */
/*   Updated: 2024/07/25 17:48:27 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE "died"

typedef struct		s_arbitrator
{
	int		philo_id;
	int		*ref_forks;
	pthread_mutex_t	mutex;
}			t_arbitrator;

typedef struct		s_philo
{
	pthread_t	tid;
	int		id;
	long		time_die;
	long		time_sleeped;
	long		time_eated;
	int		n_eat;
	struct	s_philo	*next;
	struct	s_philo	*prev;
}			t_philo;

typedef struct		s_main
{
	int		*arr;
	int		arr_size;
	int		*forks;
	int		q_forks;
	pthread_mutex_t	mutex;
	t_philo		*head;
	t_philo		*tail;
}			t_main;

enum	e_errors
{
	NO_PARAMS = -1,
	BAD_PARAMS = -2,
	WRONG_PARAMS = -3
};

enum	e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

/*----- Validations -----*/
int	validate_input(int ac, char **av, t_main *bag);
int	check_param(char *s);

/*----- Circle Linked list -----*/

void		print_philos(t_main *bag);
void		populate_philo(t_philo **node);
t_philo		*create_philo(int id);
void		create_list(t_main *bag);

/*----- Free functions -----*/
void	free_philo(t_philo *philo);
void	free_list(t_main *bag);

/*----- Utils -----*/
long	ft_atol(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(int error);
void	start_forks(t_main *bag);

#endif
