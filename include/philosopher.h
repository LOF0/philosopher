/*
** EPITECH PROJECT, 2018
** philosopher
** File description:
** header
*/

#ifndef PHILOSOPHER_H_
# define PHILOSOPHER_H_

# include <pthread.h>

/*
** --------- DEFINE -----------
*/

extern const int	SUCCESS;
extern const int	ERROR;
extern const int	FAILURE;
extern const int	EAT;
extern const int	REST;
extern const int	THINK;

/*
** ----------------------------
*/

typedef struct philosopher_s	philosopher_t;
typedef struct chopstick_s	chopstick_t;

struct			philosopher_s
{
	int		nb_chopstick;
	int		max_eat;
	int		max_philo;
	int		redirect;
	int		status;
	int		rice;
	int		id;
	pthread_t	th;
	pthread_mutex_t	mutex;
	philosopher_t	*left;
	philosopher_t	*right;
};


struct			chopstick_s
{
	int		id;
};

int			check_argv(int ac, char **av);
int			prev_eat(philosopher_t *philosoph);
int			Usage(void);
int			put_value(char **av, int ac, int *nb_philo, int *nb_eat);
void			philosopher(int nb_philo, int nb_eat);
void			wait_mutex_to_eat(philosopher_t *m_philo, philosopher_t *philo1);
void			prev_think(philosopher_t *philosoph);
void			prev_sleep(philosopher_t *philosoph);
void			init_right_left(philosopher_t *p,philosopher_t *l, philosopher_t *r);

#endif /* !PHILOSOPHER_H_ */
