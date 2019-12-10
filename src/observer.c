#include "observer.h"
#include "logf.h"

void
observer_subscribe (Observer* observers, void (*callback)(void *data))
{
    observers->callback[observers->count] = callback;
    observers->count++;
}

void
observer_notify_all (Observer* observers, void *data)
{
    game_logf ("Notifying %d observers\n", observers->count);
    for (int i = 0; i < observers->count; i++)
        observers->callback[i](data);
}
