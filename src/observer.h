#ifndef _OBSERVER_H_
#define _OBSERVER_H_

typedef struct
{
    int count;
    void (*callback[1024])(void* data);
} Observer;

void    observer_subscribe      (Observer* observers, void (*callback)(void *data));
void    observer_notify_all     (Observer* observers, void *data);

#endif
