/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:42:12 by aprado            #+#    #+#             */
/*   Updated: 2024/08/12 15:54:17 by aprado           ###   ########.fr       */
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

typedef struct		s_main	t_main;

typedef struct		s_arbitrator
{
	int		philo_id;
	int		*ref_forks;
	pthread_mutex_t	mutex;
}			t_arbitrator;

typedef struct		s_fork
{
	pthread_mutex_t	fork;
	int		fork_status;
	int		fork_id;
}			t_fork;

typedef struct		s_philo
{
	pthread_t	tid;
	int		id;
	int		state;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		meals_counter;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_main		*bag;
	struct	s_philo	*next;
	struct	s_philo	*prev;
}			t_philo;

struct			s_main
{
	int		*arr;
	int		arr_size;
	int		end_dinner;
	int		all_ready;
	long		start_timestamp;
	pthread_mutex_t	ready_mutex;
	t_fork		*forks;
	t_philo		*head;
	t_philo		*tail;
};

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
	DIE = 4
};

/*----- Validations -----*/
int	validate_input(int ac, char **av, t_main *bag);
int	check_param(char *s);

/*----- Circle Linked list -----*/
void		print_philos(t_main *bag);
void		populate_philo(t_philo **node);
t_philo		*create_philo(int id, int *arr, t_main *bag);
void		create_list(t_main *bag);
void		assign_forks(t_main *bag);

/*----- Dinner funcs -----*/
void	start_dinner(t_main *bag);

/*----- Free functions -----*/
void	free_philo(t_philo *philo);
void	free_list(t_main *bag);

/*----- Utils -----*/
long	ft_atol(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(int error);
void	start_forks(t_main *bag); // mutex init
void	finish_forks(t_main *bag); // mutex destroy
long	get_time(void);

#endif
