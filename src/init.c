#include "philo.h"

int init_simulation(t_param *param, int argc, char **argv)
{
    int i;

    if (argc != 5)
        return (printf("Usage: ./philo nb_philos time_to_die time_to_eat time_to_sleep\n"), 0);
    param->nb_philos = atoi(argv[1]);
    param->time_to_die = atoi(argv[2]);
    param->time_to_eat = atoi(argv[3]);
    param->time_to_sleep = atoi(argv[4]);
    if (param->nb_philos < 1 || param->time_to_die < 0 || param->time_to_eat < 0 || param->time_to_sleep < 0)
        return (0);
    param->forks = malloc(sizeof(t_mutex) * param->nb_philos);
    param->philos = malloc(sizeof(t_philo) * param->nb_philos);
    if (!param->forks || !param->philos)
        return (0);
    i = 0;
    while (i < param->nb_philos)
    {
        pthread_mutex_init(&param->forks[i].mutex, NULL);
        param->forks[i].value = 0;
        i++;
    }
    pthread_mutex_init(&param->run.mutex, NULL);
    pthread_mutex_init(&param->full_courses_eaten.mutex, NULL);
    set_mutex_var(&param->run, WAITING);
    set_mutex_var(&param->full_courses_eaten, 0);
    i = 0;
    while (i < param->nb_philos)
    {
        param->philos[i].philo_id = i + 1;
        param->philos[i].last_meal = get_curr_time();
        param->philos[i].meals_to_eat = -1;
        param->philos[i].par = param;
        param->philos[i].own_fork = &param->forks[i];
        param->philos[i].other_fork = &param->forks[(i + 1) % param->nb_philos];
        i++;
    }
    return (1);
}

int start_simulation(t_param *param)
{
    int i;
    pthread_t thread;

    i = 0;
    while (i < param->nb_philos)
    {
        if (pthread_create(&thread, NULL, routine, &param->philos[i]) != 0)
            return (0);
        pthread_detach(thread);
        i++;
    }
    set_mutex_var(&param->run, RUNNING);
    return (1);
}

void clean_up(t_param *param)
{
    int i;

    i = 0;
    while (i < param->nb_philos)
    {
        pthread_mutex_destroy(&param->forks[i].mutex);
        i++;
    }
    pthread_mutex_destroy(&param->run.mutex);
    pthread_mutex_destroy(&param->full_courses_eaten.mutex);
    free(param->forks);
    free(param->philos);
}
