#include<bits/stdc++.h> 
using namespace std;	

vector<int> parent(3000);
vector<int> size(3000);

unordered_map<int,forward_list<pair<int,int>>> m;

class veb {  
public:
    //Data Members
    int u, min, max;
    veb* summary_vector;
    vector<veb*> cluster_vector;

    //Constructor
    veb(int size);

    //Member functions

    int cluster_size(int u);
    int high(int x);
    int low(int x);
    int generate_index(int low, int high);
    void emptyinsert(veb* node, int key) ;
    void insert(veb* node, int key) ;
    void vebdelete(veb* node, int key);
    bool Member(veb* node, int key);  
    int minimum();
    int maximum();
   
    };  

veb::veb(int size){
    if (size <= 2) {
        u=size;
        min=-1;
        max=-1;
        summary_vector=NULL;
        cluster_vector=vector<veb*>(0, NULL);
    }
    else {
        u=size;
        min=-1;
        max=-1;
        summary_vector = new veb(cluster_size(u));
        cluster_vector = vector<veb*>(cluster_size(u), NULL);

        for (int i=0; i<cluster_size(u); i++) {
            cluster_vector[i] = new veb(cluster_size(u));
        }
    }
}

int veb::cluster_size(int u){
   return  (int)ceil(sqrt(u));
}

int veb::high(int x){
    return (int)floor(x/cluster_size(u));
}

int veb::low(int x){
  return x % cluster_size(u);
}

int veb::generate_index(int low, int high) {
 
    return low*cluster_size(u) + high;
}  

void veb::emptyinsert(veb* node, int key){
   node->min = key;
   node->max = key;
}  

void veb::insert(veb* node, int key){

  /*  Algo used

    vEB-TREE-INSERT (V, x)
1 if V.min == NIL
2 vEB-EMPTY-TREE-INSERT (V, x)
3 else
4 if x < V.min
5 exchange x with V.min
6 if V.u > 2
7 if vEB-TREE-min (V.cluster[high(x)]) == NIL
8 vEB-TREE-INSERT(V.summary, high(x))
9 vEB-EMPTY-TREE-INSERT (V.cluster[high(x)], low(x))
10 else vEB-TREE-INSERT (V.cluster[high(x)], low(x))
11 if x > V.max
12 V.max = x
  */
    if (node->min == -1 && node->max==-1) {
        //First insertion into empty tree, so make both min and max as key
         emptyinsert(node,key);
    }
    else {
        if (key < node->min) {  
            //swap min and key cz key is smaller and becomes new min
            int temp=node->min;
            node->min=key;
            key=temp;

        }
           
        if (node->u > 2) {
            if ((node->cluster_vector[node->high(key)])->min == -1) {
                //If cluster is empty, Recursively insert to summary vector
                insert(node->summary_vector, node->high(key));
                //Inserting into empty cluster
                emptyinsert(node->cluster_vector[node->high(key)],node->low(key) );
            }
            else {
                //Insert recursively into cluster_vector
                insert(node->cluster_vector[node->high(key)], node->low(key));
            }
        }

        if (key > node->max) {
             //Update max if its greater than current max
            node->max = key;
        }
    }
}

void veb::vebdelete(veb* node, int key)
{
   /* Algo used

VEB-TREE-DELETE(V,x)
1 if V.min == V.max
2   V:min = NIL
3   V:max = NIL
4 else if V.u == 2
5   if x == 0
6     V.min = 1
7   else V:min D 0
8   V:max = V:min
9 else if x == V.min
10   first-cluster = VEB-TREE-MINIMUM(V.summary)
11   x = index(first-cluster, VEB-TREE-MINIMUM(V.cluster[first-cluster]))
12   V:min = x
13  VEB-TREE-DELETE(V.cluster[high(x),low(x))
14  if VEB-TREE-MINIMUM(V:cluster[high(x)]== NIL
15    VEB-TREE-DELETE(V.summary.high(x))
16    if x == V:max
17      summary-max = VEB-TREE-MAXIMUM(V.summary)
18      if summary-max == NIL
19          V.max = V.min
20      else V.max = index(summary-max,VEB-TREE-MAXIMUM(V.cluster[summary-max])
21  elseif x == V:max
22     V.max = index(high(x))
23   VEB-TREE-MAXIMUM(V.cluster[high(x)]
*/  
    if(node->max==node->min) {
        //Only 1 key present
        node->min=-1;
        node->max=-1;
    }
 
    else if(node->u==2) {
       //2 keys present,i.e,0 and 1
        if (key==0) {
            //If key to delete is 0, then 1 is the only key left
            node->min = 1;
            node->max = 1;
        }
        else {
             //If key to delete is 0, then 1 is the only key left
            node->min = 0;
            node->max = 0;
        }
       
    }

    else {
       //more than  2 elements
        if (key==node->min) {
            //If key to delete is min, then replace min with 2nd min
            //2nd min lies in 1st cluster given by summary vector min
            int temp = (node->summary_vector)->min;
 
            key = node->generate_index(temp, (node->cluster_vector[temp])->min);
 
            node->min = key;
        }
 
        // Now delete the key from cluster vectorrecursively
        vebdelete(node->cluster_vector[node->high(key)], node->low(key));
 
       
        if ((node->cluster_vector[node->high(key)])->min == -1) {
 
        // After deleting the key,if min in cluster becomes -1(empty)
        // then delete corresponding entry in summary vector
            vebdelete(node->summary_vector,node->high(key));
 
            if (key == node->max) {
                // Checking if the key we are deleting is max
                //summary max is last non empty cluster
                int summary_max = (node->summary_vector)->max;
 
                if (summary_max == -1) {
                    //If max of summary is -1 then only min is present
                    node->max = node->min;
                }
                else {
 
                    //  Update max
                    node->max  = node->generate_index(summary_max, (node->cluster_vector[summary_max])->max);
                }
            }
        }
 
        // Simply find the new max key and
        // set the max         of the tree
        // to the new max

        else if (key == node->max) {
            //Case if cluster doesnt become empty
            //updating max
            node->max = node->generate_index(node->high(key),(node->cluster_vector[node->high(key)])->max);
        }
    }
}
 
bool veb::Member(veb* node, int key)
{
    /*
    Algo used for member:
    vEB-TREE-MEMBER (V, x)
    1 if x == V.min or x == V.max
    2 return TRUE
    3 elseif V.u == 2
    4 return FALSE
    5 else return vEB-TREE-MEMBER (V.cluster[high(x)], low(x))
  */

    if (key>node->u) {
     //Key greater than universe size is not possible
        return false;
    }
 
    else if (node->min==key || node->max==key) {
        // Min max are same so only 1 key
        return true;
    }
    else {
 
        if (node->u == 2) {
            //if size is 2 then key is either min or max. if not then key is not member
            return false;
        }
        else {
 
          //Check recursively
            return Member(node->cluster_vector[node->high(key)], node->low(key));
        }
    }
}

int veb::minimum(){
    return min;
}

int veb::maximum(){
    return max;
}

int find(int i){
    while(parent[i]!=i){
        parent[i]=parent[parent[i]];
        i=parent[i];
    }
    return i;
}

void union1(int a,int b){
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

void kruskal_veb(){
    int u=8192;
    veb* veb1 = new veb(u);
    
    int v1,e1;
    cout<<"enter no of vertices :";
    cin>>v1;
    cout<<"enter no of edges :";
    cin>>e1;
    int e2=e1;
    for(int i=0;i<=v1;i++){
        parent[i]=i;
        size[i]=1;
    }
    // cout<<"e1 "<<e1;

    while(e2--){
        int u,v,weight;
        cout<<"enter in format (weight vertex1 vertex2) : ";
        cin>>weight>>u>>v;

        //insert weight in veb tree
        

        if(m.find(weight)==m.end()){
            m[weight].push_front({u,v});
            veb1->insert(veb1,weight);
        }
        else{
            forward_list<pair<int,int>> f;
            f=m[weight];
            f.push_front({u,v});
            m[weight]=f;
        }
    }

    long long mst_cost=0;
    int i=0;
    int j=0;

    while(i<v1-1 && j<e1){
        int min=veb1->minimum();
        // cout<<"min_element :"<<min<<endl;
        
        //taking out one edge which has min weight
        forward_list<pair<int,int>> list;
        list=m[min];
        pair<int,int> edge=list.front();//contains the edge with minm weight
        list.pop_front();

        //checking if there are more edges with min weight
        if(list.empty()){
            // cout<<"min :"<<min<<endl;
            veb1->vebdelete(veb1,min);
            m.erase(min);//also delete that weight from veb tree
        }
        else{
            m[min]=list;
        }
        //a contains the edge with minm weight
        int a=edge.first;
        int b=edge.second;
        int parent_a=find(a);
        int parent_b=find(b);
        cout<<"mst :";
        if(parent_a!=parent_b){
            cout<<a<<" -> "<<b<<endl;
            union1(a,b);
            mst_cost+=min;
            i++;
        }
        j++;
    }
    cout<<"minimum spanning tree cost :"<<mst_cost<<endl;
}

void automated_kruskal_veb(int universe_size,int v1, int e1){
    clock_t start, end;
    double cpu_time_used;     
    start = clock();
    
    veb* veb1 = new veb(universe_size);
    int e2=e1;
    for(int i=0;i<=v1;i++){
        parent[i]+=i;
        size[i]=1;
    }
    // cout<<"e1 "<<e1;
    
    for(int i=0;i<v1;i++){
        int u,v,weight;
        u=i;v=i+1; weight=rand()%universe_size;
        //   cout<<u<<" "<<v<<" "<<weight<<" "<<endl;
        if(m.find(weight)==m.end()){
            m[weight].push_front({u,v});
            veb1->insert(veb1,weight);
        }
        else{
            forward_list<pair<int,int>> f;
            f=m[weight];
            f.push_front({u,v});
            m[weight]=f;
        }

    }

    srand(time(0));
    for(int i=0;i<e2;i++){
        int u,v,weight;

        //insert weight in veb tree        
         u=rand()%v1;v=rand()%v1; weight=rand()%universe_size;
        //     cout<<u<<" "<<v<<" "<<weight<<" "<<endl;

        if(m.find(weight)==m.end()){
            m[weight].push_front({u,v});
            veb1->insert(veb1,weight);
        }
        else{
            forward_list<pair<int,int>> f;
            f=m[weight];
            f.push_front({u,v});
            m[weight]=f;
        }

    }

    long long mst_cost=0;
    int i=0;
    int j=0;

    while(i<v1-1 && j<e1){ 
        int min=veb1->minimum();
    
        //taking out one edge which has min weight
        forward_list<pair<int,int>> list;
        list=m[min];
        pair<int,int> edge=list.front();//contains the edge with minm weight
        list.pop_front();


        //checking if there are more edges with min weight
        if(list.empty()){
      //      cout<<"min :"<<min<<endl;
            veb1->vebdelete(veb1,min);
            m.erase(min);//also delete that weight from veb tree
        }
        else{
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
        //      cout<<a<<" -> "<<b<<endl;
            union1(a,b);
            mst_cost+=min;
            i++;
        }
        j++;
    }

    cout<<"minimum spanning tree cost :"<<mst_cost<<endl;
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cpu_time_used*=1000;
    cout<<cpu_time_used;
    ofstream outfile1,outfile2;
    outfile1.open("edges_veb.txt",std::ios_base::app);
    outfile2.open("time_veb.txt",std::ios_base::app);
    outfile1<<e1<<" ";
    outfile2<<cpu_time_used<<" ";

    outfile1.close();
    outfile2.close();
}

int main(int argc, char**argv){
    // int universe_size=8192;
    // int vertices=1000; 
    // int edges=stoi(argv[1]);
    // cout<<edges<<endl;
    // automated_kruskal_veb(universe_size,vertices,edges);
    kruskal_veb();  
}
