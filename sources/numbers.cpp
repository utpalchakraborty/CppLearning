#include "numbers.h"

// now implement the namespace stuff.
namespace numbers
{
    int counter = 0;

    void increment()
    {
	counter++;
    }

    int getCounter()
    {
	return counter;
    }

}
