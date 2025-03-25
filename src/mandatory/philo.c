#include "philo.h"

// Utility functions
long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print);
    if (!philo->data->someone_died && !philo->data->all_ate)
    {
        printf("%lld %d %s\n", get_time() - philo->data->start_time, 
               philo->id + 1, status);
    }
    pthread_mutex_unlock(&philo->data->print);
}

void ft_usleep(long long time)
{
    long long start = get_time();
    while (get_time() - start < time)
        usleep(100);
}

int ft_atoi(const char *str)
{
    int res = 0;
    int sign = 1;
    int i = 0;
    
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || 
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

// Initialization functions
int init_data(t_data *data, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        return (printf("Error: wrong number of arguments\n"), 1);
    
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat = -1;
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    
    if (data->num_philos <= 0 || data->time_to_die <= 0 || 
        data->time_to_eat <= 0 || data->time_to_sleep <= 0 || 
        (argc == 6 && data->must_eat <= 0))
        return (printf("Error: invalid arguments\n"), 1);
    
    data->someone_died = false;
    data->all_ate = false;
    data->start_time = get_time();
    return (0);
}

int init_forks(t_data *data)
{
    int i;
    
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (printf("Error: malloc failed\n"), 1);
    
    for (i = 0; i < data->num_philos; i++)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (printf("Error: mutex init failed\n"), 1);
    }
    
    if (pthread_mutex_init(&data->print, NULL))
        return (printf("Error: mutex init failed\n"), 1);
    if (pthread_mutex_init(&data->meal_check, NULL))
        return (printf("Error: mutex init failed\n"), 1);
    if (pthread_mutex_init(&data->death, NULL))
        return (printf("Error: mutex init failed\n"), 1);
    
    return (0);
}

int init_philos(t_data *data)
{
    int i;
    
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->philos)
        return (printf("Error: malloc failed\n"), 1);
    
    for (i = 0; i < data->num_philos; i++)
    {
        data->philos[i].id = i;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = data->start_time;
        data->philos[i].data = data;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
    }
    return (0);
}

// Check functions
bool check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_check);
    if (get_time() - philo->last_meal_time > philo->data->time_to_die)
    {
        pthread_mutex_unlock(&philo->data->meal_check);
        pthread_mutex_lock(&philo->data->death);
        if (!philo->data->someone_died && !philo->data->all_ate)
        {
            philo->data->someone_died = true;
            pthread_mutex_lock(&philo->data->print);
            printf("%lld %d died\n", get_time() - philo->data->start_time, philo->id + 1);
            pthread_mutex_unlock(&philo->data->print);
        }
        pthread_mutex_unlock(&philo->data->death);
        return (true);
    }
    pthread_mutex_unlock(&philo->data->meal_check);
    return (false);
}

bool check_all_ate(t_data *data)
{
    int i;
    bool all_ate;
    
    if (data->must_eat == -1)
        return (false);
    
    all_ate = true;
    pthread_mutex_lock(&data->meal_check);
    for (i = 0; i < data->num_philos; i++)
    {
        if (data->philos[i].meals_eaten < data->must_eat)
        {
            all_ate = false;
            break;
        }
    }
    pthread_mutex_unlock(&data->meal_check);
    return (all_ate);
}

// Thread routines
void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    if (philo->id % 2 == 0)
        ft_usleep(philo->data->time_to_eat / 2);
    
    while (1)
    {
        pthread_mutex_lock(&philo->data->death);
        if (philo->data->someone_died || philo->data->all_ate)
        {
            pthread_mutex_unlock(&philo->data->death);
            break;
        }
        pthread_mutex_unlock(&philo->data->death);
        
        // Take forks
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        
        if (philo->data->num_philos == 1)
        {
            ft_usleep(philo->data->time_to_die * 2);
            pthread_mutex_unlock(philo->left_fork);
            break;
        }
        
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        
        // Eat
        print_status(philo, "is eating");
        pthread_mutex_lock(&philo->data->meal_check);
        philo->last_meal_time = get_time();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->data->meal_check);
        
        ft_usleep(philo->data->time_to_eat);
        
        // Release forks
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        
        // Sleep
        print_status(philo, "is sleeping");
        ft_usleep(philo->data->time_to_sleep);
        
        // Think
        print_status(philo, "is thinking");
    }
    return (NULL);
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    
    while (1)
    {
        usleep(1000);
        
        if (check_all_ate(data))
        {
            pthread_mutex_lock(&data->death);
            data->all_ate = true;
            pthread_mutex_unlock(&data->death);
            break;
        }
        
        for (i = 0; i < data->num_philos; i++)
        {
            if (check_death(&data->philos[i]))
                return (NULL);
        }
    }
    return (NULL);
}

// Simulation control
int start_simulation(t_data *data)
{
    int i;
    pthread_t monitor;
    
    if (pthread_create(&monitor, NULL, &monitor_routine, data))
        return (printf("Error: thread creation failed\n"), 1);
    
    for (i = 0; i < data->num_philos; i++)
    {
        if (pthread_create(&data->philos[i].thread, NULL, 
                         &philo_routine, &data->philos[i]))
            return (printf("Error: thread creation failed\n"), 1);
    }
    
    pthread_join(monitor, NULL);
    
    for (i = 0; i < data->num_philos; i++)
        pthread_join(data->philos[i].thread, NULL);
    
    return (0);
}

void clean_data(t_data *data)
{
    int i;
    
    for (i = 0; i < data->num_philos; i++)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->meal_check);
    pthread_mutex_destroy(&data->death);
    free(data->philos);
    free(data->forks);
}

int main(int argc, char **argv)
{
    t_data data;
    
    if (init_data(&data, argc, argv))
        return (1);
    if (init_forks(&data))
        return (1);
    if (init_philos(&data))
    {
        free(data.forks);
        return (1);
    }
    if (start_simulation(&data))
    {
        clean_data(&data);
        return (1);
    }
    
    clean_data(&data);
    return (0);
}