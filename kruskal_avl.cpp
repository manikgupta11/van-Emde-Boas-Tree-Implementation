#include<bits/stdc++.h>
using namespace std;
vector<int> parent(3000);
vector<int> size(3000);

unordered_map<int,forward_list<pair<int,int>>> m;
class node{
  public:
	int data, height, count; 
	node* left; node*right;
   //  node(int v){
	  // data=v; height=0 ; weight=1; left=NULL; right=NULL;
   //  } 
};  
 

int height(node* node)
{
  int  height=(node==NULL)? -1 : node->height;	//height of null is -1
  return height;
}

int count(node* node)
{
  int  count=(node==NULL)? 0 : node->count;	 //count of null is 0
  return count;
}

// Get Balance factor of node N  
int balancefn(node *node)  
{  
   int bal=(node==NULL)? 0: height(node->left)-height(node->right);
    return bal;
}  

node *rightrotate(node *grandparent)  
{  
  node *parent=grandparent->left;     
  node *parentright = grandparent->left->right;  //save left child of parent
  grandparent->left->right = grandparent;  //make gp right child of parent
  grandparent->left = parentright;         


  grandparent->count = count(grandparent->left)+ count(grandparent->right)+ 1;
  parent->count = count(parent->left)+ count(parent->right) + 1; 

  
  // parent->height = max(height(parent->left), height(parent->right)) + 1;  
  grandparent->height = max(height(grandparent->left),height(grandparent->right)) + 1;
  parent->height = max(height(parent->left), height(parent->right)) + 1;   //Calculate parent height after grandparent because gp is now child of parent
  
  return parent;
}  


node *leftrotate(node *grandparent)  
{  
  node *parent=grandparent->right;
  node *parentleft = grandparent->right->left;
  grandparent->right->left = grandparent;  //make gp right child of parent
  grandparent->right = parentleft;  

 grandparent->count = count(grandparent->left)+ count(grandparent->right)+ 1;
  parent->count = count(parent->left)+ count(parent->right) + 1; 

  grandparent->height = max(height(grandparent->left),height(grandparent->right)) + 1;
  parent->height = max(height(parent->left), height(parent->right)) + 1;   //Calculate parent height after grandparent because gp is now child of parent
  return parent;   
}  

node *lrrotate(node *grandparent)
{
  grandparent->left = leftrotate(grandparent->left);  //First apply left rotation on parent so it becomes LL case
  return rightrotate(grandparent);            //Height will be adjusted in RR case so no need here        
}  

node *rlrotate(node *grandparent)
  {
  grandparent->right = rightrotate(grandparent->left);  //First apply right rotation on parent so it becomes RR case  
  return leftrotate(grandparent);  
}


node* insert(node *root, int key){
  if(root==NULL){
  	node *root = new node(); 
    root->data = key;
    root->left = NULL; 
    root->right = NULL;
    root->height = 0;   //height of new node is 0
     root->count=1;     //count of new node is 1
    return root;	  
  }
  
  if(key>root->data){
    root->right=insert(root->right,key);  //If equal nodes, insert in right child
  }
  else if(key<root->data){
  	root->left=insert(root->left,key);
  }
  else{
     // Ignore this case because ordered set contain unique elements
  }

int leftheight=(root->left==NULL)? -1 : root->left->height;
int rightheight=(root->right==NULL)? -1 : root->right->height;
root->height=1+max( leftheight , rightheight );  
int diff=(leftheight-rightheight);  // diff will act as balancing factor

int leftcount=(root->left==NULL)? 0 : root->left->count;
int rightcount=(root->right==NULL)? 0 : root->right->count;
root->count=1+leftcount+rightcount;

 if (diff==2)                   //LL or LR case
 {  if(key<root->left->data)  {   
     return rightrotate(root);   //LL case
    }
    else if(key>root->left->data){
       root->left = leftrotate(root->left);  //LR case First left rotate parent then right rotate grandparent  
      return rightrotate(root); 	
    }
  }
  else if(diff==-2)         //RR or RL case
  {
     if(key > root->right->data)  {  
       return leftrotate(root);
     }
     else if(key < root->right->data) {
       root->right = rightrotate(root->right);  
     return leftrotate(root);  //RL
    }
  }    

  // cout<<root->data<<" "<<diff<<" "<<leftheight<<" "<<rightheight<<" "<< root->height<<endl;
   //cout << root->height;
  return root;  
}

node * successor(node* node1)  
{  
    node1=node1->right;
    while (node1->left != NULL){  
        node1 = node1->left;  
      }
  
    return node1;
} 

void printtree(node* root)
{
	if(root==NULL) return;
	printtree(root->left);
	cout<<root->data<<" "<<root->height<<" "<<root->count<<endl;
	printtree(root->right);
}


int ksmall(node* root, int k) 
    {
        int leftcount=count(root->left);
        if(leftcount+1==k) {
        	return root->data;
        }
        else if(leftcount+1>k) {
        	return ksmall(root->left, k);
        }
        else return ksmall(root->right, k-leftcount-1);   //subtract leftcount cz every node in left subtree is smaller and subtract 1 for root
    }


node* deletenode(node* root, int key)  
{  
    if(root==NULL)
        {  
        return root;  
        }
    else if(key==root->data)  
        {     
            if(root->left == NULL &&     root->right == NULL){   //no child
               node* temp = root;  
                root = NULL;  
            free(temp);  
            }
            else if(root->left == NULL &&     root->right != NULL)           {  // right child
            node *temp = root->right; 
            *root = *temp;
            free(temp);  
            }
             else if(root->left != NULL &&     root->right == NULL){   //left child
            node *temp = root->left ;  
            *root = *temp; 
            free(temp);  
             }
           else{    //both child
          
            node* temp = successor(root);  
  
            // Copy the inorder successor's  
            // data to this node  
            root->data = temp->data;  
  
            // Delete the inorder successor  
            root->right = deletenode(root->right,  
                                     temp->data);  
             } 

        }
   else if ( key > root->data )  
   {   root->right = deletenode(root->right, key); 
   }
    
    else 
    {    root->left = deletenode(root->left, key); 
    }

     if (root == NULL)  
    return root;  
  
  

    int leftheight=(root->left==NULL)? -1 : root->left->height;
    int rightheight=(root->right==NULL)? -1 : root->right->height;
    root->height=1+max( leftheight , rightheight );  
    int balance=(leftheight-rightheight); 
   
    if (balance ==2) {     //LL or LR 
        if( balancefn(root->left) >= 0)    //LL  
          return rightrotate(root);  
  
        else   
        {  
          root->left = leftrotate(root->left);      //LR
           return rightrotate(root);  
        }  
  }
    
    else if (balance == -2){      //RR
        if(balancefn(root->right) <= 0)  
           return leftrotate(root);  
   
        else        //RL
        {  
          root->right = rightrotate(root->right);  
          return leftrotate(root);  
         }
    }  

    return root;  
   
}  
  

void preorder(node *root)  
{  
    if(root!=NULL)  
    {  
        cout << root->data << " ";  
        preorder(root->left);  
        preorder(root->right);  
    }  
}  

int find(int i)
{
    while(parent[i]!=i)
    {
        parent[i]=parent[parent[i]];
        i=parent[i];
    }
    return i;
}

void union1(int a,int b)
{
    int parent_a=find(a);
    int parent_b=find(b);

    if(size[parent_a]>size[parent_b])
    {
        parent[parent_b]=parent_a;
        size[parent_a]+=size[parent_b];
    }
    else
    {
        parent[parent_a]=parent_b;
        size[parent_b]+=size[parent_a];
    }
}

void automated_kruskal_avl(int universe_size, int v1, int e1){
	clock_t start, end;
    double cpu_time_used;
     
    start = clock();

	node* root=NULL;
	
    int e2=e1;
    for(int i=0;i<=v1;i++)
    {
        parent[i]=i;
        size[i]=1;
    }
    for(int i=0;i<v1;i++)
    {
        int u,v,weight;
      
        u=i;v=i+1; weight=rand()%universe_size;
     	//   cout<<u<<" "<<v<<" "<<weight<<" "<<endl;

        if(m.find(weight)==m.end())
        {
            m[weight].push_front({u,v});
            root = insert(root,weight);
			// display(root);
        }
        else
        {
            forward_list<pair<int,int>> f;
            f=m[weight];
            f.push_front({u,v});
            m[weight]=f;
        }

    }

    srand(time(0));

	for(int i=0;i<e2;i++)
    {
        int u,v,weight;
       
        //insert weight in avl tree  
         u=rand()%v1;v=rand()%v1; weight=rand()%universe_size;
    	 //   cout<<u<<" "<<v<<" "<<weight<<" "<<endl;

        if(m.find(weight)==m.end())
        {
            m[weight].push_front({u,v});
           root = insert(root,weight);
			// display(root);
            // veb1->insert(veb1,weight);
        }
        else
        {
            forward_list<pair<int,int>> f;
            f=m[weight];
            f.push_front({u,v});
            m[weight]=f;
        }
    }

    long long mst_cost=0;
    int i=0;
    int j=0;

    while(i<v1-1 && j<e1)
    {
        
        int min=ksmall(root,1);
        //  cout<<"min_element :"<<min<<endl;
        
        //taking out one edge which has min weight
        forward_list<pair<int,int>> list;
        list=m[min];
        pair<int,int> edge=list.front();//contains the edge with minm weight
        list.pop_front();


        //checking if there are more edges with min weight
        if(list.empty())
        {
     		//       cout<<"min :"<<min<<endl;
            // veb1->vebdelete(veb1,min);
            root=deletenode(root,min);
            m.erase(min);//also delete that weight from veb tree
        }
        else
        {
            m[min]=list;
        }

        //a contains the edge with minm weight
        int a=edge.first;
        int b=edge.second;
        int parent_a=find(a);
        int parent_b=find(b);
         //  cout<<"mst :";
        if(parent_a!=parent_b)
        {
      		// cout<<a<<" -> "<<b<<endl;
            union1(a,b);
            mst_cost+=min;
            i++;
        }
 
        j++;
    }

    // cout<<"minimum spanning tree cost :"<<mst_cost;

 	cout<<"minimum spanning tree cost :"<<mst_cost<<endl;
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cpu_time_used*=1000;
    cout<<cpu_time_used;
      ofstream outfile1,outfile2;
     outfile1.open("edges_avl.txt",std::ios_base::app);
     outfile2.open("time_avl.txt",std::ios_base::app);
     outfile1<<e1<<" ";
     outfile2<<cpu_time_used<<" ";

     outfile1.close();
     outfile2.close();	
	
}

void kruskal_avl(){
	 node* root=NULL;
	
    int v1,e1;
    cout<<"enter no of vertices :";
    cin>>v1;
     cout<<"enter no of edges :";
    cin>>e1;
    int e2=e1;
    for(int i=0;i<=v1;i++)
    {
        parent[i]=i;
        size[i]=1;
    }
    // cout<<"e1 "<<e1;

    while(e2--)
    {
        int u,v,weight;
        cout<<"enter in format (weight vertex1 vertex2) : ";
        cin>>weight>>u>>v;

        //insert weight in veb tree
        if(m.find(weight)==m.end())
        {
            m[weight].push_front({u,v});
            root=insert(root,weight);
			// display(root);
        }
        else
        {
            forward_list<pair<int,int>> f;
            f=m[weight];
            f.push_front({u,v});
            m[weight]=f;
        }

    }

    long long mst_cost=0;
    int i=0;
    int j=0;

    while(i<v1-1 && j<e1)
    {
       
        int min=ksmall(root,1);
        cout<<"min_element :"<<min<<endl;
        
        //taking out one edge which has min weight
        forward_list<pair<int,int>> list;
        list=m[min];
        pair<int,int> edge=list.front();//contains the edge with minm weight
        list.pop_front();


        //checking if there are more edges with min weight
        if(list.empty())
        {
          //  cout<<"min :"<<min<<endl;
            // veb1->vebdelete(veb1,min);
            root =deletenode(root,min);
            m.erase(min);//also delete that weight from veb tree
        }
        else
        {
            m[min]=list;
        }

        //a contains the edge with minm weight
        int a=edge.first;
        int b=edge.second;
        int parent_a=find(a);
        int parent_b=find(b);
        cout<<"mst :";
        if(parent_a!=parent_b)
        {
            cout<<a<<" -> "<<b<<endl;
            union1(a,b);
            mst_cost+=min;
            i++;
        }

        j++;
    }

    cout<<"minimum spanning tree cost :"<<mst_cost<<endl;
}

int main(int argc, char**argv)
{
    // int universe_size=8192;
    //   int vertices=1000; 
    //   int edges=stoi(argv[1]);
    // automated_kruskal_avl(universe_size,vertices,edges);
    kruskal_avl();
    return 0;
}


