#include "philo.h"

int print_log(t_philo *philo, int action)
{
    long timestamp;

    timestamp = get_curr_time();
    if (get_mutex_var(&philo->par->run) != RUNNING)
        return (1);
    pthread_mutex_lock(&philo->par->run.mutex);
    if (action == TAKEN_FORK)
        printf("%ld %d has taken a fork 🍴\n", timestamp, philo->philo_id);
    else if (action == EATING)
        printf("%ld %d is eating 🍝\n", timestamp, philo->philo_id);
    else if (action == SLEEPING)
        printf("%ld %d is sleeping 🛌\n", timestamp, philo->philo_id);
    else if (action == THINKING)
        printf("%ld %d is thinking 💭\n", timestamp, philo->philo_id);
    pthread_mutex_unlock(&philo->par->run.mutex);
    return (0);
}

long get_curr_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int ft_usleep(int time_in_ms, t_mutex *run_mutex)
{
    long start_time;

    start_time = get_curr_time();
    while ((get_curr_time() - start_time) < time_in_ms)
    {
        if (get_mutex_var(run_mutex) != RUNNING)
            return (0);
        usleep(500);
    }
    return (1);
}
