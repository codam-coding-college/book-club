#ifndef ESTIMATES_H

# define ESTIMATES_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_estimate
{
    const char  *name;
    int         points;
}   t_estimate;

t_estimate  *estimate_new(const char *name, const int estimate);
void        estimate_del(t_estimate *estimate);

char        **estimate_extremes(t_estimate *estimates[]);

#endif
