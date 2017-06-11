#pragma once  
#include<utility>  
using namespace std;  
  
template<typename K,int M>  
struct BTreeNode  
{  
    K _keys[M];                         //M是孩子的个数，keys是关键值数组，多开辟一个便于处理  
    BTreeNode<K, M> *_subs[M + 1];      //孩子指针数组  
    BTreeNode<K, M> *_parent;           //指向父亲的指针  
    size_t _size;                       //记录关键值的个数   
  
    BTreeNode()  
        :_parent(NULL)  
        , _size(0)  
    {  
        for (int i = 0; i < M; i++)  
        {  
            _keys[i] = K();  
            _subs[i] = NULL;  
        }  
        _subs[M] = NULL;  
    }  
};  
  
  
template<typename K,int M>  
class BTree  
{  
    typedef BTreeNode<K, M> Node;  
public:  
    BTree()  
        :_root(NULL)  
    {}  
  
    pair<Node*,int>  Find(const K& key)  
    {  
        Node* cur = _root;  
        Node* parent = NULL;  
        while (cur)  
        {  
            int i = 0;  
            while (i<(int)cur->_size)  
            {  
                if (cur->_keys[i] < key)  
                {  
                    i++;  
                }  
                else if (cur->_keys[i]>key)  
                {  
                    break;  
                }  
                else  
                {  
                    return  pair<Node*, int>(cur,i);      //已经存在了  
                }  
            }  
            parent = cur;  
            cur = cur->_subs[i];  
        }  
        return  pair<Node*, int>(parent, -1);      //没找到，返回-1  
    }  
  
    bool Insert(const K& key)  
    {  
        if (_root==NULL)       //如果是空树的话  
        {  
            _root = new Node;  
            _root->_keys[0] = key;  
            _root->_size++;  
            _root->_parent = NULL;  
        }  
        //如果不是空树的话，先找这个key存在还是不存在  
        pair<Node*, int>  product= Find(key);  
        if (product.second != -1)       //表示这个key已经存在了  
        {  
            return false;               //已经存在，插入失败  
        }  
  
        Node* cur = product.first;  
        Node* sub = NULL;  
        K newKey = key;  
        while (1)                 
        {  
            _InsertKey(cur, newKey, sub);             //将关键值插入  
            if (cur->_size == M)                   //如果key已经大于M-1,则需要分裂  
            {  
                Node* tmp = new Node;              //创建一个分裂后的结点  
                int mid = cur->_size / 2;        //找到keys数组的中间位置的下标  
                int j = 0;  
                int i = mid+1;                     //从中间位置的下一个位置开始复制  
                for (; i <(int)cur->_size; ++i, ++j)  
                {  
                    tmp->_keys[j] = cur->_keys[i];        //将关键字复制到tmp中  
                    tmp->_subs[j] = cur->_subs[i];        //将孩子也复制到tmp中  
                    if (tmp->_subs[j])                    //如果孩子不为空，则让它指向分裂的结点  
                        tmp->_subs[j]->_parent= tmp;  
                    cur->_keys[i] = K();  
                    cur->_subs[i] = NULL;  
                    tmp->_size++;  
                }  
                //将最后一个右孩子也复制过来  
                tmp->_subs[j] = cur->_subs[i];  
                if (tmp->_subs[j])  
                    tmp->_subs[j]->_parent = tmp;  
                cur->_subs[i] = NULL;  
  
                newKey = cur->_keys[mid];  
                cur->_keys[mid] = K();  
                sub = tmp;  
                cur->_size = mid;  
  
                if (cur == _root)                //如果分裂的结点是根节点  
                {  
                    _root = new Node;  
                    _root->_keys[0] = newKey;  
                    _root->_subs[0] = cur;  
                    _root->_subs[1] = sub;  
                    cur->_parent = _root;  
                    sub->_parent = _root;  
                    _root->_size = 1;  
                    return true;  
                }  
                cur = cur->_parent;  
            }  
            else                                //不需要分裂，已经平衡  
                break;  
        }  
        return true;  
    }  
  
    bool Remove(const K& key)  
    {  
        if (_root == NULL)               //树为空树，则删除失败  
        {  
            return false;  
        }  
        pair<Node*, int> product = Find(key);  
        if (product.second == -1)              //如果key不再树中，则删除失败  
        {  
            return false;  
        }  
        Node* cur = product.first;             
        int pos = product.second;                //记录要删除的位置  
        //将判断要删除的关键码所在结点是不是叶子结点，如果不是的话，要先将关键码交换到叶子结点中  
        if (cur->_subs[pos + 1] != NULL)    //如果要删除的关键码的右子树不为空，则是非叶子结点的删除  
        {  
            Node* minkey = cur->_subs[pos + 1];          //用来记录要删除的关键码的右子树的最小的键值  
            while (minkey->_subs[0])  
            {  
                minkey = minkey->_subs[0];  
            }  
            //转换成删除这个最小的关键码  
            cur->_keys[pos] = minkey->_keys[0];  
            cur = minkey;  
            _MoveLeft(cur, 0);           //把交换后的关键码删除掉  
        }  
        else  
            _MoveLeft(cur, pos);  
  
        //判断是否满足B树的条件，不满足的话就要调整  
        int mid =(M+1)/2-1;        //求出关键码个数的下限,关键码最少为M/2-1,向上取整  
        while (1)  
        {  
            if ((int)cur->_size < mid)   //关键码的个数小于上限值，则要进行调整  
            {  
                if (cur == _root)  
                    break;  
                Node* parent = cur->_parent;  
                pos = 0;  
                while (parent->_subs[pos] != cur&&pos < (int)parent->_size)  
                    pos++;  
                if (pos == 0)   //进行左调整  
                    _LeftAdjust(parent, cur, mid, pos);  
                else  
                    _RightAdjust(parent, cur, mid, pos-1);  
                cur = parent;  
            }  
            else                     //如果不小于上限值的话，则表示已经满足B树的条件，则直接退出  
                break;  
        }  
  
        if (_root->_size == 0)         //如果调整之后根的关键码个数已经减为0，则要把当前根删除掉，把他的孩子当做根  
        {  
            Node* del = _root;            //记录要删的这个根  
            _root = _root->_subs[0];  
            if (_root)  
                _root->_parent = NULL;        //将新根的父亲置空  
            delete del;                     
        }  
  
        return true;  
    }  
  
    void InOder()  
    {  
        _InOder(_root);  
    }  
  
    ~BTree()  
    {  
        _Destory(_root);  
    }  
protected:  
    void _LeftAdjust(Node* parent, Node* cur, int mid, int pos)      //当前结点cur在他父亲的左边，cur与他的右兄弟进行调整  
    {  
        //如果cur的右兄弟的关键码的个数已经大于关键码的上限，则就通过收养解决  
        Node* right = parent->_subs[pos+1];       //right指向cur的左兄弟  
        if ((int)right->_size>mid)      //大于关键码的上限，通过收养解决  
        {  
            cur->_size++;  
            cur->_keys[cur->_size - 1] = parent->_keys[pos];       //把父节点的相应关键码下移  
            parent->_keys[pos] = right->_keys[0];                  //把右兄弟的最小关键码上移到父亲关键码位置  
            //把右兄弟的最左孩子移动到cur的最右孩子处  
            cur->_subs[cur->_size] = right->_subs[0];  
            if (right->_subs[0])  
            {  
                right->_subs[0]->_parent = cur;            //让这个孩子的父亲指向cur  
            }  
            right->_subs[0] = right->_subs[1];  
            _MoveLeft(right, 0);                                    //把右兄弟中剩余的关键码向左移动  
        }  
        else              //只能通过合并解决  
            _Merge(parent,cur,right,pos);  
    }  
  
    void _RightAdjust(Node* parent, Node* cur,int mid, int pos)  //当前结点cur在他父亲的右边，cur与他的左兄弟进行调整  
    {  
        Node* left = parent->_subs[pos];          //left指向cur的左兄弟  
        if ((int)left->_size>mid)               //左兄弟的关键码个数大于关键码上限的值  
        {  
            //cur先把最左边的位置空出来，再把父亲结点的相应关键码下移  
            _MoveRight(cur,0);  
            cur->_keys[0] = parent->_keys[pos];      //父亲相应关键码下移  
            parent->_keys[pos] = left->_keys[left->_size-1];    //将左兄弟中的最大关键码上移到父节点位置  
            cur->_subs[0] = left->_subs[left->_size];           //将左兄弟中的最后一个孩子移到cur的左边  
            if (left->_subs[left->_size])  
            {  
                left->_subs[left->_size]->_parent = cur;         //将这个孩子结点的父亲指向cur  
            }  
  
            left->_keys[left->_size - 1] = K();  
            left->_subs[left->_size] = NULL;  
            left->_size--;  
        }  
        else  
            _Merge(parent,left,cur,pos);  
    }  
  
  
    void _Merge(Node* parent,Node* cur,Node* brother,int pos)        //保留cur，合并兄弟结点  
    {  
        int i = cur->_size;     //要插入的位置  
        cur->_keys[i] = parent->_keys[pos];        //先把父亲结点相应的关键码的值移动到左孩子中   
        cur->_subs[i + 1] = brother->_subs[0];      //把右兄弟的最左孩子移动过来  
        if (brother->_subs[0])  
            brother->_subs[0]->_parent = cur;  
        i++;  
        cur->_size++;  
        for (int j = 0; j < (int)brother->_size; ++i, ++j)     //将兄弟结点指针拷贝过来  
        {  
            cur->_keys[i] = brother->_keys[j];  
            cur->_subs[i + 1] = brother->_subs[j + 1];  
            if (brother->_subs[j+1])  
                brother->_subs[j+1]->_parent = cur;  
            cur->_size++;  
        }  
        if (parent->_subs[pos] == brother)  
            parent->_subs[pos] = NULL;  
        else  
            parent->_subs[pos + 1] = NULL;  
  
        _MoveLeft(parent,pos);    
        delete brother;  
    }  
  
    void _Destory(Node* cur)  
    {  
        if (cur == NULL)  
            return;  
        int i = 0;  
        for (i = 0; i < (int)cur->_size; i++)  
        {  
            _Destory(cur->_subs[i]);  
            delete cur->_subs[i];  
        }  
        _Destory(cur->_subs[i]);                  //遍历最右边的孩子  
        delete cur->_subs[i];  
    }  
  
    void _InOder(Node* cur)  
    {  
        if (cur == NULL)  
            return;  
        int i = 0;  
        for (i = 0; i < (int)cur->_size; i++)  
        {  
            _InOder(cur->_subs[i]);  
            cout << cur->_keys[i] << "  ";  
        }  
        _InOder(cur->_subs[i]);                  //遍历最右边的孩子  
    }  
  
    void _InsertKey(Node* cur,const K& key,Node* sub)  
    {  
        int i = cur->_size-1;  
        while (i >= 0)        //将key插入到B树中  
        {  
            if (key < cur->_keys[i])  
            {  
                cur->_keys[i + 1] = cur->_keys[i];  
                cur->_subs[i + 2] = cur->_subs[i+1];  
                --i;  
            }   
            else                                 //key比当前关键值小，则进行插入  
                break;  
        }  
  
        //key是这组keys中最小的，放在第0个位置  
        cur->_keys[i+1] = key;  
        cur->_subs[i+2] = sub;  
        if (sub != NULL)                  //孩子不为空  
            sub->_parent = cur;          //孩子的parent指向cur  
        cur->_size++;  
    }  
  
    void _MoveLeft(Node* cur,int pos)                  //在叶子结点中删除一个关键码  
    {  
        if (cur == NULL)  
            return;  
        int i = 0;  
        for (i = pos; i < (int)cur->_size; ++i)  
        {  
            cur->_keys[i]=cur->_keys[i+1];                 //将要删除的关键码覆盖掉  
            cur->_subs[i+ 1] = cur->_subs[i+ 2];  
        }  
        cur->_size--;                                      
    }  
  
    void _MoveRight(Node* cur,int pos)  
    {  
        int i = cur->_size-1;       //当前结点最右关键码下标  
        for (; i >=pos; --i)  
        {  
            cur->_keys[i+1] = cur->_keys[i];  
            cur->_subs[i+2] = cur->_subs[i+1];  
        }  
        cur->_subs[1] = cur->_subs[0];  
        cur->_size++;  
    }  
private:  
    Node* _root;  
};  