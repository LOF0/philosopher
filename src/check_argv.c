/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** check_argv
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "philosopher.h"

int	Usage(void)
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\n");
	printf("DESCRIPTION\n\t-p nbr_p  number of philosophers\n");
	printf("\t-e nbr_e  maximum number times a philosopher eats");
	printf(" before exiting the program\n");
	return (ERROR);
}

int		put_value(char **av, int ac, int *nb_philo, int *nb_eat)
{
	for (int i = 0; i < ac; i++) {
		if (strcmp(av[i], "-p") == 0)
			if (av[i + 1] && atoi(av[i + 1]) > 0)
				*nb_philo = atoi(av[i + 1]);
		if (strcmp(av[i], "-e") == 0)
			if (av[i + 1] && atoi(av[i + 1]) > 0)
				*nb_eat = atoi(av[i + 1]);
	}
	if (nb_philo == 0 || nb_eat == 0)
		return (ERROR);
	return (SUCCESS);
}

int	check_argv(int ac, char **av)
{
	if (ac == 2 && strcmp(av[1], "--help") == SUCCESS) {
		Usage();
		return (SUCCESS);
	}
	if (ac != 5)
		return (Usage());
	else {
		if (strcmp(av[1], "-p") != SUCCESS ||
		    atoi(av[2]) <= 0 ||
		    strcmp(av[3], "-e") != SUCCESS ||
		    atoi(av[4]) <= 0) 
			return (Usage());
	}
	return (SUCCESS);
}
