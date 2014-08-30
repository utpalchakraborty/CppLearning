#include <iostream>
#include <vector>
#include <algorithm>

//----------------------------------------------------
//        The Visitor Design pattern 
//
// This design pattern does a duble dispatch. So a call
// like 
// methodA(Class A, Class B) gets approapriately called 
// the rightKindOfA.method(rightKindofB).
//--------------------------------------------------
namespace{
    // just declare the Visior.
    class Visitor;

    // Now declare the acceptor interface.
    class Node{
    public:
	virtual void acceptVisitor(Visitor&) = 0;
	
	~Node() {}	
    };

    // now we define one kind of acceptor.
    // the is one of the kind of classes.
    class SquareNode : public Node {
    public:
	void acceptVisitor(Visitor& v);
    };

    // define another kind of acceptor
    class CircleNode : public Node {
    public:
	void acceptVisitor(Visitor& v);
    };


    // now define the visitor that has pure virtual 
    // implementations of both kinds of nodes. 
    class Visitor {
    public:
	virtual void Visit(SquareNode&) = 0;
	virtual void Visit(CircleNode&) = 0;

	~Visitor() {}
    };

    // now implement the node accepts
    void SquareNode::acceptVisitor(Visitor& v){
	v.Visit(*this);
    }

    void CircleNode::acceptVisitor(Visitor& v){
	v.Visit(*this);
    }

    // now implement concrete visitors.
    class Visitor1 : public Visitor{
    public:
	void Visit(SquareNode& s){
	    std::cout << "Visitor 1 visiting square." << std::endl;
	}

	void Visit(CircleNode& s){
	    std::cout << "Visitor 1 visiting circle." << std::endl;
	}

    };

    // implement another visitor
    class Visitor2 : public Visitor{
    public:
	void Visit(SquareNode& s){
	    std::cout << "Visitor 2 visiting square." << std::endl;
	}

	void Visit(CircleNode& s){
	    std::cout << "Visitor 2 visiting circle." << std::endl;
	}

    };

}

void runVisitors(std::vector<Node*> nodes, Visitor& v){
    for_each(nodes.begin(), nodes.end(), 
	     [&v](Node* n) { n->acceptVisitor(v); });   
}

int main(){

    // with all that defined lets run some tests.
    CircleNode a;
    CircleNode b;
    SquareNode c;
    SquareNode d;
    CircleNode e;

    std::vector<Node*> nodes { &a, &b, &c, &d, &e };
    Visitor1 v1;
    Visitor2 v2;

    // now we are dealing only with nodes. 
    // but the correct visitor method belonging to the 
    // appropriate node gets called.
    runVisitors(nodes, v1);
    runVisitors(nodes, v2);

    // if more types of Nodes are added then 
    // only that new node class has to be impleemented
    // and the requisite method in the Vistor 
    // implementers need to be added.


    // the typeid operator provides type of instance
    // that is the most derived definition of the instance.
    // for example
    for_each(nodes.begin(), nodes.end(), 
	     [](Node* n) { std::cout << typeid(*n).name()  << std::endl; });   


}
