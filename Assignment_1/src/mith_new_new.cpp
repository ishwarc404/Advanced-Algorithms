#include "../include/splay_tree.hpp"
//mithali
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

splay_tree_implementation();
void insert(int);
void remove(int);
int get_num_nodes();
int find(int);
//void delete_key(int); 
  
vector<int> post_order();
vector<int> post;
void post_order1(node *); 

vector<int> pre;
vector<int> pre_order();
void pre_order1(node *);

vector<int> in;
vector<int> in_order();
void in_order1(node *);



};
splay_tree_implementation::node *splay(splay_tree_implementation::node *, int);

splay_tree_implementation::splay_tree_implementation()
{
num_nodes = 0;

}

splay_tree_implementation:: node* newNode(int key)  
{  
    splay_tree_implementation::node* Node = new splay_tree_implementation::node(); 
    Node->key = key;  
    Node->left = Node->right = NULL;  
    return (Node);  
}


int splay_tree_implementation::get_num_nodes()
{
    
    return num_nodes;

}
void splay_tree_implementation::remove(int element)
{
    pre.clear();
    post.clear();
    in.clear();

    splay_tree_implementation::node *previous, *curr, *p;
    splay_tree_implementation::node *q, *temp, *temp_root;
    previous=NULL;
    curr=root;

   //find the key in the tree
   while((curr!=NULL)&&(curr->key!=element))
   {
     previous=curr;
     if(element<curr->key)
      curr=curr->left;
     else
      curr=curr->right;
    }
    if(curr==NULL)
    {
      printf("Key not found..\n");
      root = splay(root, element);
      return;
    }
    //if one subtree present or no subtrees 
    if((curr->left==NULL)||(curr->right==NULL))
    {
      if(curr->left==NULL)
        q=curr->right;
      else
        q=curr->left;
       //deleting a root with one subtree
    if(previous==NULL)//deleting root
    {
        num_nodes--;
        if(curr->left == NULL)
        {
            root = curr->right;
            free(curr);
            return;
        }
        else
        {
            root = curr->left;
            free(curr);
            return;
        }

        
        // return;
    }
      
    if(curr==previous->left)
        previous->left=q;
     else
        previous->right=q;
    free(curr);
    //num_nodes--;
   }
   else
   {
     //two subtrees present
     //find inorder successor
     p=NULL;//for the parent of inorder successor     
     temp=curr->right;
     while(temp->left!=NULL)
     {
       p=temp;
       temp=temp->left;
     }
     //inorder successor found(temp)
     if(p!=NULL)
      p->left=temp->right;
     else 
      curr->right =temp->right;
     curr->key=temp->key;
     free(temp);
     //num_nodes--;
    }
    root = splay(root, previous->key);
    num_nodes--;

}


int splay_tree_implementation::find(int element)
{
    
    //node *temp;

    pre.clear();
        post.clear();
        in.clear();
    root = splay(root, element);
    if(root->key == element)
    {
        
        return 1;
    }
    else
    //cout<<"here:"<<temp->key<<endl;
    // cout<<splay(root, element)->key; 
    return 0;

    
}


void splay_tree_implementation :: insert(int element) 
{
    //if the number of nodes reaches null, we just dereference the root node
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
    
    pre.clear();
    post.clear();
    in.clear();

//Case 2 : if tree is not empty

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


//rotate code
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
splay_tree_implementation::node *rightRotate(splay_tree_implementation::node *x)  
{  
    splay_tree_implementation::node *y = x->left;  
    x->left = y->right;  
    y->right = x;  
    return y;  
}  
  
// A utility function to left 
// rotate subtree rooted with x  
// See the diagram given above.  
splay_tree_implementation::node * leftRotate(splay_tree_implementation::node *x)  
{  
    splay_tree_implementation::node *y = x->right;  
    x->right = y->left;  
    y->left = x;  
    return y;  
}  

//splay code
splay_tree_implementation::node *splay(splay_tree_implementation::node *newtemp, int key)  
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


//preorder  
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



//IN ORDER 
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

// void splay_tree_implementation ::delete_key(int key) 
// { 
//     splay_tree_implementation ::node *temp; 
//     //splay_tree_implementation ::node *root1 = root;
//     if (root == NULL) 
//         return; 
      
//     // Splay the given key     
//     root = splay(root, key); 
      
//     // If key is not present, then 
//     // return root 
//     if (key != root->key) 
//         return; 
          
//     // If key is present 
//     // If left child of root does not exist 
//     // make root->right as root    
//     if (!root->left) 
//     { 
//         temp = root; 
//         root = root->right; 
//     } 
      
//     // Else if left child exits 
//     else
//     { 
//         temp = root; 
  
//         /*Note: Since key == root->key, 
//         so after Splay(key, root->lchild), 
//         the tree we get will have no right child tree 
//         and maximum node in left subtree will get splayed*/
//         // New root 
//         root = splay(root->left, key); 
          
//         // Make right child of previous root  as 
//         // new root's right child 
//         root->right = temp->right; 
//     } 
      
//     // free the previous root node, that is, 
//     // the node containing the key 
//     free(temp);
//     //num_nodes--; 
      
//     // return root of the new Splay Tree 
     
      
// } 