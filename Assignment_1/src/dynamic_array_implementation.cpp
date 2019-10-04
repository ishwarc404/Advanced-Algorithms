#include "../include/dynamic_array.hpp"

using namespace std;

//Given just for reference. Only the class name and function names should match.
class dynamic_array_implementation : public dynamic_array
{
private:
    int size;
    int capacity;
    int *arr;
    double increase_factor;
    double decrease_factor;

public:
    dynamic_array_implementation();
    int get_size();
    int get_capacity();
    void set_increase_factor_table_size(double);
    void set_load_factor_reduction(double);
    void append(int);
    void pop();
    int get(int);
    ~dynamic_array_implementation();
};

dynamic_array_implementation::dynamic_array_implementation()
{
    size = 0;
    capacity = 0;
    increase_factor = 2;
    decrease_factor = 0.25;
}
int dynamic_array_implementation::get_size()
{
    //basically we are returning the size
    //nothing else needed here
    return size;
}
int dynamic_array_implementation::get_capacity()
{
    //returning the capacity
    //nothing else needed here
    return capacity;
}

void dynamic_array_implementation::set_increase_factor_table_size(double new_increase_factor)
{
    {
        increase_factor = new_increase_factor ;  //setting the new factor
        return;
    }
}

void dynamic_array_implementation::set_load_factor_reduction(double new_decrease_factor)
{
    decrease_factor = new_decrease_factor;
    return;
}

void dynamic_array_implementation::append(int element)
{
    
    //if we're adding the first element
    if(size==0)
    {
        //we first need to create a new array
        // *arr will point to this
        int array_size  = 1 ;
        capacity = 1; //changing capacity value
        int *new_array = new int[array_size]; //dynamically creating one array
        new_array[0] = element;
        size = size + 1;

        //now let's point *arr
        arr = new_array;
        // cout<<"First If";
        // cout<<"New Array Created with element: "<<arr[size-1]<<endl;  //size-1 because size is incremented 
    }

    //what to do if array already contains elements and it is full
    // we need to double the size of the array 
    else if(size == capacity)
    {
        capacity = increase_factor * capacity ;
        int *temp_array = new int[capacity];
        //lets copy the elements from the small array to the new big array
        for(int i = 0; i<size;i++)
        {
            temp_array[i] = arr[i];
        }
        //new temp_array contains all the elements plus some extra space
        temp_array[size] = element; //adding the new element //not size+1
        size = size + 1 ; //coz now another element has been added

        arr = temp_array ; //pointing to new temp array now

    }    

    else if(size < capacity)
    {
        arr[size] = element; //adding the new element //not size+1
        size = size + 1 ; //coz now another element has been added

    }

    return;
}

void dynamic_array_implementation::pop()
{   
    if(size == 0)
    {
        return;
    }
    //pop means removal of an element
    //cases
    //case1 : when the element was poped and no contraction is needed
    //case2 : when the element was poped and now we need to contract it

    //in both cases we need to check the decrease_factor first
    //if the new capacity after decrease is lesser than the capacity after decrease factor, we decrease it
    //else we do not decrease it

    /////////////

    //is poping same

    int new_capacity = decrease_factor * capacity  * increase_factor;
    if(decrease_factor * capacity >= size-1) //case 2
    {
        //we decrease the size of the array
        int *new_decreased_array = new int[new_capacity];
        //lets copy all the values except the last value as we need to pop it out //hence i<size-1
        for(int i=0;i<size-1;i++)
        {
            new_decreased_array[i] = arr[i];
        }
        //now derefrence and re-reference
        arr = new_decreased_array;
        size = size - 1 ;
        capacity = new_capacity;

    }
    else //case 1 
    {
        //we do not decrease the size of the array
        // int *new_decreased_array = new int[size-1]; //here the new capacity is just 1 less
        // //lets copy all the values except the last value as we need to pop it out //hence i<size-1
        // for(int i=0;i<size-1;i++)
        // {
        //     new_decreased_array[i] = arr[i];
        // }
        // //now derefrence and re-reference
        // arr = new_decreased_array;
        size = size - 1;
    }

    //lets print the array after popping
    // cout<<"The array after popping is: ";
    // for(int j =0;j<size;j++)
    // {
    //     cout<<arr[j]<<" ";
    // }
    // cout<<endl;

    return;
}
int dynamic_array_implementation::get(int index)
{
    //get an element based on index
    //lets return the element based on index
    if(index>=0 && index<size)
    {
        return arr[index]; //returns the value stored in the array
    }
    else if(index>=size && index<capacity)
    {
        return 0; //if value requested from the empty part of the array
        
    }
    {
        //if out of bounds
        cout<<"Out of Range! Hence -1 will be returned:"<<endl;
        return -1;
    }
    
}

dynamic_array_implementation::~dynamic_array_implementation()
{
    if (capacity > 0)
    {
        delete[] arr;
    }
}