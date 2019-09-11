#include "src/dynamic_array_implementation.cpp"
#include <iostream>

using namespace std;

//You can test/use your code here.
int main()
{
    dynamic_array_implementation array;
    //Output should be 1
    array.append(1);
    array.append(2);
    array.append(3);
    cout<<"New Size after adding"<<array.get_capacity()<<endl;
    array.set_load_factor_reduction(0.6);
    array.pop();
    cout<<"New Size after popping"<<array.get_capacity()<<endl;
    return 0;

    
}