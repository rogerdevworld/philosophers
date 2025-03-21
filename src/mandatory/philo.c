#include "../../include/philo.h"

// Función para obtener el tiempo actual en milisegundos
long get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Función para dormir por un número de milisegundos
void usleep_ms(long ms)
{
	long	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < ms)
		usleep(500); // Dormir 500 microsegundos para no bloquear el hilo
}

// Función para inicializar los datos globales
int init_data(t_data *data)
{
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (1);

    for (int i = 0; i < data->num_philos; i++)
        pthread_mutex_init(&data->forks[i], NULL);

    pthread_mutex_init(&data->print_mutex, NULL);
    data->start_time = get_time_in_ms();
    data->death_occurred = 0; // Inicializar el flag de muerte

    return (0);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->death_occurred)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            break;  // Salir del bucle si alguien ha muerto
        }
        pthread_mutex_unlock(&philo->data->death_mutex);

        // Realizar acciones (tomar tenedores, comer, dormir, pensar)
        ft_fork(philo);
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}


void ft_think(t_philo *philo)
{
    print_status(philo, "is thinking");
}

void ft_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep_ms(philo->data->time_to_sleep);
}

void ft_eat(t_philo *philo)
{
    print_status(philo, "is eating");
    philo->last_meal_time = get_time_in_ms();
    philo->meals_eaten++;
    usleep_ms(philo->data->time_to_eat);
}

void ft_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->id]);
    print_status(philo, "has taken a fork");

    pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->num_philos]);
    print_status(philo, "has taken a fork");

    // Actualizar el tiempo de la última comida
    philo->last_meal_time = get_time_in_ms();
}


int check_death(t_philo *philo, t_data *data)
{
    long current_time;

    current_time = get_time_in_ms();
    if (current_time - philo->last_meal_time > data->time_to_die)
    {
        pthread_mutex_lock(&data->death_mutex);
        if (!data->death_occurred)
        {
            data->death_occurred = 1;
            pthread_mutex_lock(&data->print_mutex);
            printf("%ld %d has died\n", current_time - data->start_time, philo->id + 1);
            pthread_mutex_unlock(&data->print_mutex);
        }
        pthread_mutex_unlock(&data->death_mutex);
        return (1);  // El filósofo ha muerto
    }
    return (0);  // El filósofo sigue vivo
}

void *monitor_routine(void *arg)
{
    t_monitor *monitor = (t_monitor *)arg;
    t_data *data = monitor->data;
    t_philo *philos = monitor->philos;

    while (1)
    {
        for (int i = 0; i < data->num_philos; i++)
        {
            if (check_death(&philos[i], data))
            {
                pthread_mutex_lock(&data->death_mutex);
                data->death_occurred = 1;
                pthread_mutex_unlock(&data->death_mutex);
                return (NULL);  // Terminar el hilo de monitoreo
            }
        }
        usleep(1000);  // Esperar 1 ms antes de verificar de nuevo
    }
    return (NULL);
}

void print_status(t_philo *philo, const char *status)
{
    long time;

    pthread_mutex_lock(&philo->data->death_mutex);
    if (philo->data->death_occurred)
    {
        pthread_mutex_unlock(&philo->data->death_mutex);
        return;  // No imprimir si alguien ha muerto
    }
    pthread_mutex_unlock(&philo->data->death_mutex);

    pthread_mutex_lock(&philo->data->print_mutex);
    time = get_time_in_ms() - philo->data->start_time;
    printf("%ld %d %s\n", time, philo->id + 1, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}