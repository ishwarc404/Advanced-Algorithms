#include "../include/splay_tree.hpp"
//ishwar
using namespace std;

class splay_tree_implementation : public splay_tree
{
    private:
        int num_nodes;

    public:

        class node  
        {  
            public: 
            int key;  
            node *left, *right;  
        }*root;

        vector<int> pre;
        vector<int> post;
        vector<int> in;
        
        splay_tree_implementation();
        void insert(int);
        void remove(int);
        int get_num_nodes();
        int find(int);
        vector<int> post_order();
        vector<int> pre_order();
        vector<int> in_order();


        //vector<int> pre_order;
        void post_order1(node *);    
        void pre_order1(node *);
        void in_order1(node *);

        node* splay(node *,int) ;
        node* newNode(int);
        node* leftRotate(node *x) ;
        node* rightRotate(node *x) ; 
        

};

//constructor 
splay_tree_implementation::splay_tree_implementation()
{
// cout<<"comes here";
num_nodes = 0;
// cout<<num_nodes;
}





//find operation explaination
/*whenever we find an item, we make it the root node so that
it can be found faster the next time
this is called splaying

3 ways to do this if we are finding X
1)Zig-Zag situation : X is (l child of a r child) : rotate same node to right
or (r child of a l child) : rotate same node to left
keep doing until X is the root node

2)Zig Zig situation: (l child of a l child) : rotate parent node to the right
 or 
(r child of a r  child) : rotate parent node to the left

then keep doing until it is the root

3)Zig situation : when X is the child of the root. 
Rotate right or left based on the postition.

Note: We do not make rotations to balance the trees, we do it
to get the recently searched items near the root
*/


//declarations
// splay_tree_implementation::node* splay(splay_tree_implementation::node *, int ) ;

splay_tree_implementation::node* splay_tree_implementation::newNode(int key)  
{  
    node* Node = new node(); 
    Node->key = key;  
    Node->left = Node->right = NULL;  
    return (Node);  
}


int splay_tree_implementation::get_num_nodes()
{
    
    return num_nodes;

}


int splay_tree_implementation::find(int element)
{
    
    
    root = splay(root, element);
    if(root->key == element)
    {
        //re initiliaisng vector pre
        pre.clear();
        post.clear();
        in.clear();

        return 1;
    }
    else
    return 0;

    

    
}
void splay_tree_implementation :: remove(int element) 
{

    //splay_tree_implementation ::
    node *temp; 
    
    if (root == NULL) 
        return; 

    if(num_nodes == 0)
    {
        return;
    }
      
    // Splay the given key     
    root = splay(root, element); 
    
    // If key is not present, then 
    // return root 
    if (element != root->key) 
       { 
        //    num_nodes--;
           return; //ret root
       }


    //re initiliaisng vector pre
    pre.clear();
    post.clear();
    in.clear();


    // If key is present 



    // If left child of root does not exist 
    // make root->right as root    
    if (!root->left) 
    {   
        temp = root; 
        root = root->right;
        num_nodes--;
        free(temp);
        return; 
    } 
      
    // Else if left child exits 
    else
    { 
        temp = root; 
        /*Note: Since key == root->key, 
        so after Splay(key, root->lchild), 
        the tree we get will have no right child tree 
        and maximum node in left subtree will get splayed*/
        // New root 
        root = splay(root->left, element); 
           
        // Make right child of previous root  as 
        // new root's right child 
        root->right = temp->right; 
        free(temp); 
        
        //cout<<root->key;
        
        // cout<<root->left->key;
        // cout<<root->right->key;
        num_nodes--;
        return;
    } 
      
    // free the previous root node, that is, 
    // the node containing the key 
    
      
    // return root of the new Splay Tree 
    //return root; 

}

void splay_tree_implementation :: insert(int element) 
{


    if(get_num_nodes() == 0)
    {
        root = NULL;
    }
// Case 1 : Simple Case: If tree is empty  
    if (root == NULL) 
    { 
        root = newNode(element); 
        num_nodes++;
        return;
        
    } 
    

//Case 2 : if tree is not empty

      //re initiliaisng vector pre
        pre.clear();
        post.clear();
        in.clear();

    // Bring the closest leaf node to root  //to check if element exists
    root = splay(root, element);  
  
    // If key is already present, then return  
    if (root->key == element) 
    return;  
  
    // Otherwise allocate memory for new node  
    node *newnode = newNode(element);  
  
    // If root's elementey is greater, make  
    // root as right child of newnode  
    // and copy the left child of root to newnode  
    if (root->key > element)  
    {  
        newnode->right = root;  
        newnode->left = root->left;
        root->left = NULL;  
    }  
  
    // If root's key is smaller, make  
    // root as left child of newnode  
    // and copy the right child of root to newnode  
    else
    {  
        newnode->left = root;  
        newnode->right = root->right;  
        root->right = NULL;  
    }  
  
    root = newnode; // newnode becomes new root
    num_nodes ++;
    


};


splay_tree_implementation::node* splay_tree_implementation::rightRotate(node *x)  
{  
    splay_tree_implementation::node *y = x->left;  
    x->left = y->right;  
    y->right = x;  
    return y;  
}  
  
  
splay_tree_implementation::node* splay_tree_implementation::leftRotate(node *x)  
{  
    splay_tree_implementation::node *y = x->right;  
    x->right = y->left;  
    y->left = x;  
    return y;  
}  

//splay code
splay_tree_implementation::node* splay_tree_implementation::splay(node *newtemp, int key)  
{  
    // Base cases: root is NULL or  
    // key is present at root  
    if (newtemp == NULL || newtemp->key == key)  
        return newtemp;  
  
    // Key lies in left subtree  
    if (newtemp->key > key)  
    {  
        // Key is not in tree, we are done  
        if (newtemp->left == NULL) return newtemp;  
  
        // Zig-Zig (Left Left)  
        if (newtemp->left->key > key)  
        {  
            // First recursively bring the 
            // key as root of left-left  
            newtemp->left->left = splay(newtemp->left->left, key);  
  
            // Do first rotation for root,  
            // second rotation is done after else  
            newtemp = rightRotate(newtemp);  
        }  
        else if (newtemp->left->key < key) // Zig-Zag (Left Right)  
        {  
            // First recursively bring  
            // the key as root of left-right  
            newtemp->left->right = splay(newtemp->left->right, key);  
  
            // Do first rotation for root->left  
            if (newtemp->left->right != NULL)  
                newtemp->left = leftRotate(newtemp->left);  
        }  
  
        // Do second rotation for root  
        return (newtemp->left == NULL)? newtemp: rightRotate(newtemp);  
    }  
    else // Key lies in right subtree  
    {  
        // Key is not in tree, we are done  
        if (newtemp->right == NULL) return newtemp;  
  
        // Zig-Zag (Right Left)  
        if (newtemp->right->key > key)  
        {  
            // Bring the key as root of right-left  
            newtemp->right->left = splay(newtemp->right->left, key);  
  
            // Do first rotation for root->right  
            if (newtemp->right->left != NULL)  
                newtemp->right = rightRotate(newtemp->right);  
        }  
        else if (newtemp->right->key < key)// Zag-Zag (Right Right)  
        {  
            // Bring the key as root of  
            // right-right and do first rotation  
            newtemp->right->right = splay(newtemp->right->right, key);  
            newtemp = leftRotate(newtemp);  
        }  
  
        // Do second rotation for root  
        return (newtemp->right == NULL)? newtemp: leftRotate(newtemp);  
    }  
} 

//preorder code 
void preOrder(splay_tree_implementation::node * temp)  
{  
    if (temp != NULL)  
    {  
        cout<<temp->key<<" ";  
        preOrder(temp->left);  
        preOrder(temp->right);  
    }  
}  

void splay_tree_implementation ::pre_order1(splay_tree_implementation ::node *t)
{
     if(t!=NULL)
            {
                pre.push_back(t->key);
                pre_order1(t->left);
                pre_order1(t->right);
            }
}


 vector<int> splay_tree_implementation :: pre_order()
        {
           pre_order1(root);
           return pre;

        }

//POST ORDER TRAVERSAL
void splay_tree_implementation ::post_order1(splay_tree_implementation ::node *t)
{
     if(t!=NULL)
            {
                post_order1(t->left);
                post_order1(t->right);
                post.push_back(t->key);
            }
}


 vector<int> splay_tree_implementation :: post_order()
        {
           post_order1(root);
           return post;

        }


//IN ORDER TRAVERSAL
void splay_tree_implementation ::in_order1(splay_tree_implementation ::node *t)
{
     if(t!=NULL)
            {
                in_order1(t->left);
                in.push_back(t->key);
                in_order1(t->right);
                
            }
}


 vector<int> splay_tree_implementation :: in_order()
        {
           in_order1(root);
           return in;

        }