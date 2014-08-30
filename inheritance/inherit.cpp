#include <iostream>

namespace{

    // we define a class that is going to be inherited.
    class Level1 {
    private:
        int data1;
    public:
        Level1(){
            data1 = 0;
        }

        void setLevel1(int i) { data1 = i; }
        
        virtual void print() { std::cout << "data1 = " << data1; }

        ~Level1() {}
    };

    // we inherit as public.
    class Level2a : public Level1{
    private:
        int data2a;
    public:
        Level2a(){
            data2a = 0;
        }
        
        void setLevel2a(int i) { data2a = i; }

        void print() {
            Level1::print(); std::cout << "data2a = " << data2a << std::endl;
        }
    };
    
    // again we inherit as public.
    class Level2b : public Level1{
    private:
        int data2b;
    public:
        Level2b(){
            data2b = 0;
        }
        
        void setLevel2b(int i) { data2b = i; }

        void print() {
            Level1::print(); std::cout << "data2b = " << data2b << std::endl;
        }
    };

    // now how many copies of Level1 does Level3 have?
    // two. This is tested below by setting and copying calls
    class Level3 : public Level2a, public Level2b {
    };


    // now lets inherit in virtual mode.
    class Level2av : public virtual Level1{
    private:
        int data2a;
    public:
        Level2av(){
            data2a = 0;
        }
        
        void setLevel2a(int i) { data2a = i; }

        void print() {
            Level1::print(); std::cout << "data2a = " << data2a << std::endl;
        }
    };
    
    // inherit again in public virtual mode.
    class Level2bv : public virtual Level1{
    private:
        int data2b;
    public:
        Level2bv(){
            data2b = 0;
        }
        
        void setLevel2b(int i) { data2b = i; }

        void print() {
            Level1::print(); std::cout << "data2b = " << data2b << std::endl;
        }
    };

    // now how many copies of Level1 does Level3 have?
    // one. This is tested below by setting and copying calls
    class Level3v : public Level2av, public Level2bv {
    public:
	// we have to override because it is not clear to 
	// compiler when the print() is called.
	// and it does not matter that but level 2 classes
	// had overridden print.
	virtual void print() override{
	    Level1::print();
	}

	void level3function() { std::cout << "This is pure level 3." << std::endl; }
    };
    
        
}

int main()
{
    Level3 l3;

    // now set the Level2a copy of Level1 to 1;
    // and set the Level1a copy of Level1 to 2;
    // and then print them out.

    // the following is ambiguous... which level1 are we
    // speaking of?
    //l3.setLevel1(3);

    // but this compiles because we break ambiguity.
    l3.Level2a::setLevel1(1);

    l3.Level2b::setLevel1(2);

    // should print 1
    l3.Level2a::print();

    // shoudl print 2.
    l3.Level2b::print();

    Level3v l3v;

    // can call without ambiguity. since only one copy.
    l3v.setLevel1(3);
    l3v.Level2av::setLevel1(1);
    l3v.Level2bv::setLevel1(2);
    // shoudl print 2. the last one set.
    l3v.print();

    // finally say we have a pointer to Level1
    Level1* lv1p = &l3v;

    // how we do get a base class pointer from that
    // use dynamic_cast
    if(auto lv3p = dynamic_cast<Level3v*>(lv1p)){
	std::cout << "conversion succeeded" << std::endl;
    }else{
	// if the conversion failed l3vp would be null.
	std::cout << "conversion failed." << std::endl;
    }

    // dynamic cast can also convert a refercne. but if 
    // that conversion fails it throws bad_cast exception
    Level1& lv1r = l3v;

    auto lv3r = dynamic_cast<Level3v&>(lv1r);
    std::cout << "conversion succeeded" << std::endl;
    lv3r.level3function();

    // of course all this can be done with static cast also
    // but that is not always run time safe. static cast 
    // assumes that the programmer knows what he is doing\
    auto lv3p = static_cast<Level3v*>(lv1p);

    // finally reinterpret cast can convert anything to anything
    void* p = 0;
    auto lv3p = reinterpret_cast<Level3v*>(p);

    // calls on the above two pointers will lead to disaster of course.

    // finally const_cast<> can cast away a const 

    
}
