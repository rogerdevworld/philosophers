#include "../../include/philo.h"


// Función para inicializar los filósofos
void init_philosophers(t_philo *philos, t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        philos[i].id = i;
        philos[i].data = data;
        philos[i].last_meal_time = data->start_time;
        philos[i].meals_eaten = 0;
        pthread_mutex_init(&philos[i].death_mutex, NULL);  // Inicialización del mutex de muerte
        pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_data      data;
    t_philo     *philos;
    pthread_t   monitor_thread;
    t_monitor   monitor;

    // Validación de los argumentos
    if (validate_args(argc, argv))
        return (1);
    if (parse_args(argc, argv, &data))
        return (1);
    if (init_data(&data))
        return (1);

    // Asignación de memoria para los filósofos
    philos = malloc(sizeof(t_philo) * data.num_philos);
    if (!philos)
    {
        free(data.forks);  // Liberar memoria de los tenedores si falla la asignación
        return (1);
    }

    // Inicialización de los filósofos y creación de hilos
    init_philosophers(philos, &data);

    // Configurar la estructura de monitoreo
    monitor.data = &data;
    monitor.philos = philos;

    // Crear un hilo de monitoreo para verificar la muerte de los filósofos
    pthread_create(&monitor_thread, NULL, monitor_routine, &monitor);

    // Esperar a que todos los hilos de los filósofos terminen
    int i = 0;
    while (i < data.num_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }

    // Esperar a que el hilo de monitoreo termine
    pthread_join(monitor_thread, NULL);

    // Liberar memoria
    free(philos);
    free(data.forks);
    return (0);
}