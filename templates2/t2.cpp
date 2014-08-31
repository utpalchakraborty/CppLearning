#include <iostream>
#include <vector>

using std::ostream;

namespace{

    // define a template
    // this is a complex with type T
    // as the individual types of the 
    // real & imaginary
    template<typename T>
    class complex{
    private:
	T re;
	T im;
    public:
	complex() : re {}, im {} {}

	// now how do we specify all non narrowing 
	// conversions in a constructor.
	// by another template
	template<typename C>
	complex(C r, C i) : re {r}, im {i} {}
	
	complex(const complex&) = default;

	template<typename C>
	complex(const complex<C>& c) : re {c.real()}, im{c.imaginary()} {}

	const T real() const { return re; }

	const T imaginary() const { return im; }
	
	// operator required for template usage later.
	complex operator+=(complex c) { 
	    re += c.real();
	    im += c.imaginary();
	    return complex { re, im };
	}

    };

    // tmeplated output stream operator.
    template<typename T>
    ostream& operator<<(ostream& stream, const complex<T>& c){
	stream << c.real() << " + i" << c.imaginary();
	return stream;	
    }

    // declare both the classes
    template<typename T> class Matrix;
    template<typename T> class Vector;
    // and the friended operator function.
    template<typename T>
    Vector<T> operator*(const Matrix<T>& m, const Vector<T>& t);

    
    // now define the classes.
    template<typename T> class Vector{
	T v[4];
    public:
	friend Vector operator*<>(const Matrix<T>&, const Vector&);
    };

    // define the other class.
    template<typename T> class Matrix{
	Vector<T> v[4];
    public:
	friend Vector<T> operator*<>(const Matrix&, const Vector<T>&);
    };

    // define the actual implementation.
    template<typename T>
	Vector<T> operator*(const Matrix<T>& m, const Vector<T>& t){
	return Vector<T> {};
    } 


    //----------------------
    // The concept of Lifting.
    // ---------------------
    // Generalizing an algorithm from a specific type to 
    // an arbitrary type
    template<typename Iter, typename T = typename Iter::value_type>
    T sum(Iter begin, Iter end){

	T retValue = *begin++;
	while(begin != end){
	    retValue += (*begin++);
	}
	return retValue;
    }

}

int main() {

    // now we can define a double template and pass in 
    // integers in constructors. 
    complex<double> cd { 1.2 , 3.3 };
    complex<double> cd1 { 1.2 , 3.4 };
    complex<double> cd2 { 1.2 , 3.5 };
    complex<int> ci {1, 2};

    complex<long> cl { ci };

    // but the following will give a compile error
    complex<int> aci { cd };

    int v[] = { 1 , 2, 3, 4, 5, 6, 7};

    int value =  sum<int*, int>(v, v + 7);
    std::cout << value << std::endl;

    std::vector<complex<double>> c;
    c.push_back(cd);
    c.push_back(cd1);
    c.push_back(cd2);

    // now see the template operation on the followin 
    complex<double> result = sum<
	std::vector<complex<double>>::iterator, // first template type
	complex<double> // second template type
	> (c.begin(), c.end());

    // because the template argument second can be defaulted we can also write
    complex<double> result2 = sum<std::vector<complex<double>>::iterator> (c.begin(), c.end());

    std::cout << result2 << std::endl;
    std::cout << result << std::endl;


}
