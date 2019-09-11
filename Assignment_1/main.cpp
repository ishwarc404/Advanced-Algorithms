#include "src/splay_tree_implementation.cpp"
#include <iostream>

using namespace std;

//You can test/use your code here.
int main()
{
    splay_tree_implementation obj;

    
    obj.insert(25);
    obj.insert(50);
    obj.insert(100);
    obj.insert(200);

    
    cout<<endl;
    cout<<"Preorder traversal of the modified Splay tree is \n";

    vector<int> a = obj.pre_order() ;
	for (auto i = a.begin(); i != a.end(); ++i) 
      cout << *i << " ";  

  cout<<"Nodes:"<<obj.get_num_nodes()<<endl;

    obj.remove(200);

    cout<<"heressssss"<<endl;
    cout<<"Nodes:"<<obj.get_num_nodes()<<endl;

    vector<int> b = obj.pre_order() ;
    for (auto i = b.begin(); i != b.end(); ++i) 
      cout << *i << " "; 


}
