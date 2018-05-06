/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** state_philo.c
*/

#include "philosopher.h"
#include "extern.h"

void	prev_sleep(philosopher_t *philosoph)
{
	philosoph->status = REST;
	lphilo_sleep();
	philosoph->redirect = THINK;
}

void	 wait_mutex_to_eat(philosopher_t *m_philo, philosopher_t *philo1)
{
	while (1){
		if (pthread_mutex_trylock(&philo1->mutex) == 0) {
			lphilo_take_chopstick(&philo1->mutex);
			m_philo->status = EAT;
			lphilo_eat();
			pthread_mutex_unlock(&philo1->mutex);
			lphilo_release_chopstick(&philo1->mutex);
			return ;
		}
	}
}


int	prev_eat(philosopher_t *philosoph)
{
	for (int out = 0; out != 1;) {
		if (pthread_mutex_trylock(&philosoph->mutex) == 0) {
			lphilo_take_chopstick(&philosoph->mutex);
			wait_mutex_to_eat(philosoph, philosoph->left);
			pthread_mutex_unlock(&philosoph->mutex);
			lphilo_release_chopstick(&philosoph->mutex);
			out = 1;
		}
		else if (pthread_mutex_trylock(&philosoph->left->mutex) == 0) {
			lphilo_take_chopstick(&philosoph->left->mutex);
			wait_mutex_to_eat(philosoph, philosoph);
			pthread_mutex_unlock(&philosoph->left->mutex);
			lphilo_release_chopstick(&philosoph->left->mutex);
			out = 1;
		}
	}
	philosoph->rice++;
	if (philosoph->rice == philosoph->max_eat)
		return (1);
	philosoph->redirect = REST;
	return (0);
}

void	prev_think(philosopher_t *philosoph)
{
	for (int out = 0; out != 1;) {
		if (pthread_mutex_trylock(&philosoph->mutex) == 0) {
			lphilo_take_chopstick(&philosoph->mutex);
			philosoph->status = THINK;
			lphilo_think();
			pthread_mutex_unlock(&philosoph->mutex);
			lphilo_release_chopstick(&philosoph->mutex);
			out = 1;
		}
		else if (pthread_mutex_trylock(&philosoph->left->mutex) == 0) {
			lphilo_take_chopstick(&philosoph->left->mutex);
			philosoph->status = THINK;
			lphilo_think();
			pthread_mutex_unlock(&philosoph->left->mutex);
			lphilo_release_chopstick(&philosoph->left->mutex);
			out = 1;
		}
	}
	philosoph->redirect = EAT;
}
