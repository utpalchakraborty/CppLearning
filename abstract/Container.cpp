#include "Container.h"


int sum(Container& container)
{
    int retvalue = 0;
    for(int i = 0; i < container.size(); i++)
    {
	retvalue += container[i];
    }
}

void clear(Container& container)
{
    for(int i = 0; i < container.size(); i++)
    {
	container[i] = 0;
    }
}

