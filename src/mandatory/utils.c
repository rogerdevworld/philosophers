#include "../../include/philo.h"

// Función para verificar si todos los filósofos han comido suficiente
int check_all_philosophers(t_philo *philos, t_data *data)
{
    for (int i = 0; i < data->num_philos; i++)
    {
        if (philos[i].meals_eaten < data->max_meals)
            return (0);  // Al menos un filósofo no ha comido suficiente
    }
    return (1);  // Todos han comido suficiente
}