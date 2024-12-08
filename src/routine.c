#include "philo.h"

int	pick_up_fork(t_philo *philo, t_mutex *fork)
{
	if (!fork)
		return (0);
	pthread_mutex_lock(&fork->mutex);
	if (print_log(philo, TAKEN_FORK))
	{
		pthread_mutex_unlock(&fork->mutex);
		return (0);
	}
	return (1);
}

void	put_fork_down(t_philo *philo)
{
	pthread_mutex_unlock(&philo->own_fork->mutex);
	pthread_mutex_unlock(&philo->other_fork->mutex);
}

int	eat(t_philo *philo)
{
	if (!pick_up_fork(philo, philo->own_fork))
		return (0);
	if (!pick_up_fork(philo, philo->other_fork))
		return (0);
	if (print_log(philo, EATING))
		return (0);
	philo->last_meal = get_curr_time();
	if (!ft_usleep(philo->par->time_to_eat, &philo->par->run))
		return (0);
	put_fork_down(philo);
	if (philo->meals_to_eat > 0)
	{
		philo->meals_to_eat--;
		if (philo->meals_to_eat == 0)
			increment_mutex_var(&philo->par->full_courses_eaten);
	}
	return (1);
}

int	sleep_routine(t_philo *philo)
{
	if (print_log(philo, SLEEPING))
		return (0);
	return (ft_usleep(philo->par->time_to_sleep, &philo->par->run));
}

int	think(t_philo *philo)
{
	if (print_log(philo, THINKING))
		return (0);
	return (1);
}

void	*routine(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	// Attente que tous les threads soient prêts
	while (get_mutex_var(&philo->par->run) == WAITING)
		usleep(500);
	// Premier cycle de pensée pour éviter la collision
	think(philo);
	if (philo->philo_id % 2)
		usleep(1000);
	// Boucle principale : penser → manger → dormir
	while (eat(philo) && sleep_routine(philo) && think(philo))
		;
	return (NULL);
}
