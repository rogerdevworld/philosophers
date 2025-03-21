#ifndef PHILO_H
#define PHILO_H
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

#include "../libft/libft.h"

// Estructura que representa la información de cada filósofo.
typedef struct s_philo
{
	int				id;             // Identificador único del filósofo
	pthread_t		thread;         // Hilo del filósofo
	long			last_meal_time; // Tiempo de la última comida
	int				meals_eaten;    // Número de comidas que ha realizado
	struct s_data	*data;          // Datos globales
    pthread_mutex_t death_mutex;
} t_philo;

// Estructura para almacenar los parámetros globales.
typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             max_meals;
    long            start_time;
    int             death_occurred;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;  // Mutex para proteger death_occurred
} t_data;

typedef struct s_monitor
{
    t_data  *data;
    t_philo  *philos;
} t_monitor;

// Prototipos de las funciones
int		validate_args(int argc, char **argv);
int		parse_args(int argc, char **argv, t_data *data);
int		init_data(t_data *data);
void	*philo_routine(void *arg);
long	get_time_in_ms(void);
void	usleep_ms(long ms);
void	print_status(t_philo *philo, const char *status);

void ft_think(t_philo *philo);
void ft_sleep(t_philo *philo);
void ft_eat(t_philo *philo);
void ft_fork(t_philo *philo);
int check_death(t_philo *philo, t_data *data);
void *monitor_routine(void *arg);

int check_all_philosophers(t_philo *philos, t_data *data);
#endif