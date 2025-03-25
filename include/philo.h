#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data   *data;
} t_philo;

typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    bool            someone_died;
    bool            all_ate;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t meal_check;
    pthread_mutex_t death;
    t_philo         *philos;
} t_data;

// Utils
long long   get_time(void);
void        print_status(t_philo *philo, char *status);
void        ft_usleep(long long time);
int         ft_atoi(const char *str);
void        clean_data(t_data *data);

// Init
int         init_data(t_data *data, int argc, char **argv);
int         init_philos(t_data *data);
int         init_forks(t_data *data);

// Threads
void        *philo_routine(void *arg);
void        *monitor_routine(void *arg);
int         start_simulation(t_data *data);

// Check
bool        check_death(t_philo *philo);
bool        check_all_ate(t_data *data);

#endif