#include "philo.h"

int	get_mutex_var(t_mutex *mutex)
{
	int	var;

	pthread_mutex_lock(&mutex->mutex);
	var = mutex->value;
	pthread_mutex_unlock(&mutex->mutex);
	return (var);
}

void	set_mutex_var(t_mutex *mutex, int var)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->value = var;
	pthread_mutex_unlock(&mutex->mutex);
}

void	increment_mutex_var(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->value++;
	pthread_mutex_unlock(&mutex->mutex);
}
