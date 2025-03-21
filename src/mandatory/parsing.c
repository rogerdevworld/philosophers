#include "../../include/philo.h"

// Función para validar los argumentos.
int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6) // Comprobamos si hay 4 o 5 argumentos
	{
		ft_putstr_fd("Error: Número de argumentos incorrecto.\n", 2);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0) // Los argumentos deben ser números positivos
		{
			ft_putstr_fd("Error: Todos los argumentos deben ser enteros positivos.\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

// Función para parsear los argumentos y almacenarlos en una estructura.
int	parse_args(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);

	// Si hay un quinto argumento, se parsea también.
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1; // Sin límite de comidas.

	return (0);
}