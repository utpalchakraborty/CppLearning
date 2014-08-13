#ifndef __CONTAINER_H__
#define __CONTAINER_H__
// this is the definition of the abstract class Container

class Container
{
public:
    // pure virtual function. must be implemented 
    virtual int& operator[](int) = 0;
    // pure virtual function. must be implemented.
    virtual int size() const = 0;
    // virtual destructor. Must be overridden
    // as needed. Tells the compiler using the 
    // abstract type that the destructor should be 
    // called.
    virtual ~Container() {}

    // finally we want to make sure that there are 
    // no copy and move operations. After all this is 
    // an interface.
    Container(const Container& c) = delete;
    Container& operator=(const Container& c) = delete;

    Container(Container&& c) = delete;
    Container& operator=(Container&& c) = delete;

};

// provides the sum
int sum(Container& container);

void clear(Container& container);

#endif
