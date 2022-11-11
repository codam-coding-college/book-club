#include "estimates.h"

static void
*xmalloc(size_t size)
{
    void    *p;

    p = malloc(size);
    if (!p)
    {
        dprintf(STDERR_FILENO, "malloc failure: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return (p);
}

static char
*xstrdup(const char *s1)
{
    char    *s;

    s = strdup(s1);
    if (!s)
    {
        dprintf(STDERR_FILENO, "strdup failure: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return (s);
}

t_estimate
*estimate_new(const char *name, const int points)
{
    t_estimate  *estimate;

    estimate = (t_estimate *)xmalloc(sizeof(t_estimate));
    estimate->points = points;
    estimate->name = (name != NULL) ? xstrdup(name) : NULL;
    return (estimate);
}

void
estimate_del(t_estimate *estimate)
{
    if (estimate != NULL)
        free((void *)estimate->name);
    free(estimate);
}

static int
estimate_list_len(t_estimate *estimates[])
{
    int count;

    count = 0;
    if (estimates != NULL)
    {
        while (estimates[count] != NULL)
            count++;
    }
    return (count);
}

static char
**estimate_new_list(t_estimate *lowest, t_estimate *highest)
{
    char  **developers;

    if (lowest == NULL || highest == NULL) {
        developers = (char **)xmalloc(sizeof(char *));
        *developers = NULL;
    }
    else {
        developers = (char **)xmalloc(sizeof(char *) * 3);
        developers[0] = xstrdup(lowest->name);
        developers[1] = xstrdup(highest->name);
        developers[2] = NULL;
    }
    return (developers);
}

char
**estimate_extremes(t_estimate *estimates[])
{
    t_estimate  *lowest_estimate;
    t_estimate  *highest_estimate;

    if (estimates == NULL) {
        dprintf(STDERR_FILENO, "Warning: List of estimates may not be NULL\n");
        return (NULL);
    }
    if (estimate_list_len(estimates) < 2) {
        dprintf(STDERR_FILENO, "Warning: There has to be more then 1 estimate in the list\n");
        return (NULL);
    }

    lowest_estimate = NULL;
    highest_estimate = NULL;
    for (int idx = 0; estimates[idx] != NULL; idx++) {

        if (lowest_estimate == NULL || estimates[idx]->points < lowest_estimate->points) {
            lowest_estimate = estimates[idx];
        }
        if (highest_estimate == NULL || estimates[idx]->points > highest_estimate->points) {
            highest_estimate = estimates[idx];
        }
    }

    if (lowest_estimate->points == highest_estimate->points) {
        return (estimate_new_list(NULL, NULL));
    }
    return (estimate_new_list(lowest_estimate, highest_estimate));
}
