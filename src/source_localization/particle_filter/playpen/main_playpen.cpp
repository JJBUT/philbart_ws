// /https://en.cppreference.com/w/cpp/language/rule_of_three

#include "iostream"
#include "stdexcept"
#include "initializer_list"
#include "algorithm"
#include "typeinfo" //typeid()


// "static assertions" are used to enforce invariants at compile time by causing and printing compiler errors
// Can only be used on things that can be evaluated at compile time- think "constexpr" (sec 1.7)
static_assert(4<=sizeof(int), "integers are too small");

template<typename T>    //uses "template"
class Vector{
    T* elem;                                // "pointer" to the elements
    int sz;                                 // The number of elements
public:
    // Constructor: Uses "new" to allocate s*sizeof(T) bytes of memory on the heap
    Vector(int s){
        if (s<0) {  
            throw std::length_error("Vector<T>:Vector()");  
        }
        std::cout<< "Length Constructor: Claiming " << s << " heap values of size " << sizeof( T ) << " byte each holding type " << typeid( T ).name() << "\n" ;
        elem= new T[s]();   // Zero initialize each element
        sz= s;

        //NOTE: The condition s<0 enforces an invariant 
        //QUESTION: Why not just require "unsigned int" instead of "int" to ensure its a positive length
    } 

    Vector(std::initializer_list<T> lst)
    :elem{new T[lst.size()]},  sz{static_cast<int>(lst.size())}
    {
        std::cout<< "Initializer List Constructor: Claiming " << lst.size() << " heap values of size " << sizeof( T ) << " byte each holding type " << typeid( T ).name() << "\n" ;
        std::copy(lst.begin(), lst.end(), elem);
    }

    // Copy Constructor:
    // Rule of three for copy! If you have a custom destructor, that probably means
    // you are managing some heap resource which you only have a pointer to (i.e. its a resource handle).
    // The auto generated copy constructor essentially copies over the stack variables directly. 
    // If you dont define your own copy constructor (or specify the compiler not generate
    // its own with "Vector(const Vector&) = delete") then you will essentially just be copying
    // over the pointer handle, and not creating new objects on the heap.
    Vector(const Vector<T>& a)
        :elem{new T[a.size()]()}, sz{a.sz}
    {
        std::cout<< "Copy Constructor: Claiming " << a.sz << " heap values of size " << sizeof( T ) << " byte each holding type " << typeid( T ).name() << " and manually copying input Vector into this memory"<< "\n" ;
        for (int i = 0; i < a.size(); i++){
            elem[i] = a.elem[i];
        }
    }

    // Move Constructor:
    // "move": We avoid the cost of copying into a function by passing functions. 
    // But if you would like to return something from a function   you cannot return it 
    // by reference, because it would be refering to some local to the function variable 
    // that will be destroyed when the function exits, leaving you with hanging reference.
    // So to get around the the huge cost or copying large data objects when we want to
    // return them, we introduce move semantics. This is essentially transfering ownership 
    // of a resource and deleting the original parent.
    Vector( Vector&& a )
        :elem{ a.elem }, sz{ a.sz }
        {
            std::cout<< "Move Constructor: Transfering ownership of " << a.sz << " heap values of size " << sizeof( T ) << " byte each holding type " << typeid( T ).name() <<" and destroying the former owner"<< "\n" ;
            a.elem= nullptr;
            a.sz= 0;
        }

    // Destructor: Use "delete" to clear deallocate memory on the heap.
    // A destructor is automatically called when the variables scope is exited.
    // The stack has automatic memory management, and building and properly using
    // using destructors is how we (but kinda manually) manage the heap.
    // But instead of using delete lets use "smart pointers" yayayay!
    ~Vector(){
        std::cout<< "Destructor!\n" ;
        delete[] elem;

        //QUESTION: How can we show everyone this thing actually works?
    }
    
    // Member Function: Returns a "reference" which means I can access and edit vector members in place
    T& operator[]( int i ) {
        if(i<0 || i>=size()) {
            throw std::out_of_range("Vector<T>::operator[]");
        }
        return elem[i];

        // QUESTION: Why is i>=size() and not i>size()?
    } 
    
    //Copy Assignment
    Vector& operator=( const Vector& a ){
        std::cout<< "Copy Assignment: Claiming " << a.sz << " heap values of size " << sizeof( T ) << " byte each holding type " << typeid( T ).name() << " and manually copying input Vector into this memory"<< "\n" ;
        T* p= new T[a.size()];
        for (int i = 0; i < a.size(); i++){
            p[i]= a.elem[i];
        }
        delete[] elem;
        elem= p;
        sz=a.sz;
        return *this;
    }

    // Move Assignment:
    Vector& operator=( Vector&& a ){
        std::cout<< "Move Assignment: Transfering ownership of " << a.sz << " heap values of size " << sizeof( T ) << " byte each holding type " << typeid( T ).name() <<" and destroying the former owner"<< "\n" ;
        elem= a.elem ;
        sz= a.sz ;        
        a.elem= nullptr ;
        a.sz= 0 ;
    }

    // Member Function: "const" means that I cannot edit a class data member in this function and 
    // "noexcept" means it should never throw and error
    int size() const noexcept {
        return sz;
        
        //QUESTION: Why do we use const in this function declaration?
    }           

    void push_back( double x ){
        T* elem_new= new T[sz+1];
        for (int i = 0; i < sz; i++){
            elem_new[i]= elem[i];
        }
        elem_new[sz]=x;
        delete[] elem;
        elem= elem_new;     
        sz=sz+1;
    }
};

template<typename T>
T* begin(Vector<T>& x){
        return x.size() ? &x[0]:nullptr;
    }

template<typename T>
T* end(Vector<T>& x){
    return begin(x)+x.size();
}

// Resource Handle Concept:
// The Vector object can have a different number of elements of different sizes at differnet times,
// but it itself remains the same size.
// "This is the basic technique for handling varying amounts of
// information in C++: a fixed-size handle (JJB: found on the stack) referring to a variable amount
// of data stored "elsewhere" (e.g., on the free store allocated by new; JJB: aka the heap)"
void resource_handle(){
    // Each char is 1 byte
    Vector<char> char_vec(10);
    std::cout<<"Size of char_vec: "<<sizeof(char_vec)<<"\n";
    std::cout<<"Size of char_vec's data: "<<"PUT SIZE HERE"<<"\n";
    //Each float is 4 bytes
    Vector<float> float_vec(5);
    std::cout<<"Size of float_vec: "<<sizeof(float_vec)<<"\n";
    std::cout<<"Size of float_vec's data: "<<"PUT SIZE HERE"<<"\n";
    // Each double is 8 bytes
    Vector<double> double_vec(0);
    std::cout<<"Size of double_vec: "<<sizeof(double_vec)<<"\n";
    std::cout<<"Size of double_vec's data: "<<"PUT SIZE HERE"<<"\n";
}
// Error Handling:
// When we try to access element at index<0 or index>=size() the Vector::operator[](int) throws
// a "std::out_of_range" error. "throw" transfers control to a handler that has expresses interest
// in handling an error of that type. If ther is no handler to accept the error as the stack unwinds then 
// we get a run time error and the program exits
// Do not over use try-catch blocks; see section 4.2.2 for RAII principles (Resource Acquisition is 
// Initialization) (I dont understand it either :/)
void handle_exception(){
    Vector<double> double_vec(5);

    try{
        double_vec[6];
    } catch(std::out_of_range){
        std::cout<<"JJB is trying to handle exception ahhhh!\n\n";
        /* Handle exception here */
    }

    //NOTE: "exceptions" report errors at runtime!
}


int main(){
    std::cout<<"Executing Playpen\n";
    Vector<double> vec{1,1,1,};
    
   
    std::cout<<"Playpen Executed!\n";
    
    return 0;
}
