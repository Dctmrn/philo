#include "philo.h"

int main(int argc, char **argv)
{
    t_param param;

    if (!init_simulation(&param, argc, argv))
        return (1);
    if (!start_simulation(&param))
    {
        clean_up(&param);
        return (1);
    }
    clean_up(&param);
    return (0);
}
