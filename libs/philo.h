/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:42:12 by aprado            #+#    #+#             */
/*   Updated: 2024/07/16 09:47:08 by aprado           ###   ########.fr       */
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

typedef struct		s_philo
{
	int		id;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		n_eat;
	struct	s_philo	*next;
	struct	s_philo	*prev;
}			t_philo;

typedef struct	s_main
{
	int	*arr;
	int	arr_size;
	t_philo	*head;
}		t_main;

enum	e_errors
{
	NO_PARAMS = -1,
	BAD_PARAMS = -2,
	WRONG_PARAMS = -3
};

/*----- Validations -----*/
int	validate_input(int ac, char **av, t_main *bag);
int	check_param(char *s);

/*----- Utils -----*/
long	ft_atol(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(int error);

#endif
