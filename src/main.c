/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** main
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "philosopher.h"
#include "extern.h"

const int	SUCCESS = 0;
const int	ERROR = -1;
const int 	FAILURE = 84;
const int	EAT = 0;
const int 	REST = 1;
const int	THINK = 2;


int	main(int ac, char **av)
{
	int		nb_philo = 0;
	int		nb_eat = 0;

	RCFStartup(ac, av);
	if (put_value(av, ac, &nb_philo, &nb_eat) != 0) {
		Usage();
		return (ERROR);
	}
	philosopher(nb_philo, nb_eat);
	RCFCleanup();
	return (SUCCESS);
}
