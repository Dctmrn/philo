#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define WAITING 0
# define RUNNING 1
# define STOPPED 2

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define TAKEN_FORK 3

typedef struct s_mutex
{
    pthread_mutex_t mutex;
    int             value;
}   t_mutex;

typedef struct s_philo
{
    int             philo_id;
    int             meals_to_eat;
    long            last_meal;
    struct s_param  *par;
    struct s_mutex  *own_fork;
    struct s_mutex  *other_fork;
}   t_philo;

typedef struct s_param
{
    int             nb_philos;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    t_mutex         run;
    t_mutex         full_courses_eaten;
    t_philo         *philos;
    t_mutex         *forks;
}   t_param;

// Prototypes
int     init_simulation(t_param *param, int argc, char **argv);
int     start_simulation(t_param *param);
void    clean_up(t_param *param);

int     pick_up_fork(t_philo *philo, t_mutex *fork);
void    put_fork_down(t_philo *philo);
int     eat(t_philo *philo);
int     sleep_routine(t_philo *philo);
int     think(t_philo *philo);
void    *routine(void *varg);

int     print_log(t_philo *philo, int action);
long    get_curr_time(void);
int     ft_usleep(int time_in_ms, t_mutex *run_mutex);

void    increment_mutex_var(t_mutex *mutex);
int     get_mutex_var(t_mutex *mutex);
void    set_mutex_var(t_mutex *mutex, int var);

#endif
