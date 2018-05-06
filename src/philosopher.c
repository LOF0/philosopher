/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** philo
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "philosopher.h"
#include "extern.h"


void	*philo(void *arg)
{
	philosopher_t *philosoph = arg;

	while (philosoph->rice < philosoph->max_eat) {
		if (philosoph->redirect == EAT){
			if (prev_eat(philosoph) == 1) {
				pthread_exit(NULL);
				return arg;
			}
		}
		else if (philosoph->redirect == THINK)
			prev_think(philosoph);
		else if (philosoph->redirect == REST)
			prev_sleep(philosoph);
	}
	pthread_exit(NULL);
	return arg;
}

void	init_status(philosopher_t **philosoph)
{
	int i = philosoph[0]->max_philo ;
	int eat = 0;
	int think = 0;
	int rest = 0;

	for (int e = 0; e < i; e++) {
		if (eat == 0){
			philosoph[e]->status = EAT;
			philosoph[e]->redirect = EAT;
			eat = 1;
		}
		else if (rest == 0) {
			philosoph[e]->status = REST;
			philosoph[e]->redirect = REST;
			rest = 1;
		}
		else if (think == 0) {
			philosoph[e]->status = THINK;
			philosoph[e]->redirect = THINK;
			think = 1;
		}
		if (eat == 1 && think == 1 && rest == 1) {
			rest = 0;
			think = 0;
			eat = 0;
		}
	}
}

void	init_philo(philosopher_t **the_philo)
{
	int	i = the_philo[0]->max_philo;

	init_status(the_philo);
	for (int e = 0; e < i-1; e++) {
		the_philo[e]->id = e;
		the_philo[e]->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		the_philo[e]->rice = 0;
		if (e == 0) {
			the_philo[e]->right = the_philo[e + 1];
			the_philo[e]->left = the_philo[i - 1];
		}
		else {
			the_philo[e]->right = the_philo[e + 1];
			the_philo[e]->left = the_philo[e - 1];
		}
		sleep(1);
		pthread_create(&(the_philo[e]->th), NULL, philo, the_philo[e]);
	}
	the_philo[i - 1]->id = the_philo[i - 1]->max_philo - 1;
	the_philo[i - 1]->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_create(&(the_philo[i - 1]->th), NULL, philo, the_philo[i - 1]);
	the_philo[i - 1]->left = the_philo[i - 2];
	the_philo[i - 1]->left = the_philo[0];
	the_philo[i - 1]->rice = 0;	
}



void	philosopher(int nb_philo, int nb_eat)
{
	philosopher_t	**philosoph;

	philosoph = malloc(sizeof(philosopher_t*) * (nb_philo + 2));
	if (philosoph == NULL)
		return ;
	philosoph[nb_philo + 1] = NULL;
	for (int i = 0; i < nb_philo; i++) {
		philosoph[i] = malloc(sizeof(philosopher_t));
		if (philosoph[i] == NULL)
			return ;
		philosoph[i]->max_philo = nb_philo;
		philosoph[i]->max_eat = nb_eat;
	}
	init_philo(philosoph);
	for  (int i = 0; i < nb_philo; i++) {
		pthread_join(philosoph[i]->th, NULL);
	}
	return ;
}
