#pragma once  
#include<utility>  
using namespace std;  
  
template<typename K,int M>  
struct BTreeNode  
{  
    K _keys[M];                         //M�Ǻ��ӵĸ�����keys�ǹؼ�ֵ���飬�࿪��һ�����ڴ���  
    BTreeNode<K, M> *_subs[M + 1];      //����ָ������  
    BTreeNode<K, M> *_parent;           //ָ���׵�ָ��  
    size_t _size;                       //��¼�ؼ�ֵ�ĸ���   
  
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
                    return  pair<Node*, int>(cur,i);      //�Ѿ�������  
                }  
            }  
            parent = cur;  
            cur = cur->_subs[i];  
        }  
        return  pair<Node*, int>(parent, -1);      //û�ҵ�������-1  
    }  
  
    bool Insert(const K& key)  
    {  
        if (_root==NULL)       //����ǿ����Ļ�  
        {  
            _root = new Node;  
            _root->_keys[0] = key;  
            _root->_size++;  
            _root->_parent = NULL;  
        }  
        //������ǿ����Ļ����������key���ڻ��ǲ�����  
        pair<Node*, int>  product= Find(key);  
        if (product.second != -1)       //��ʾ���key�Ѿ�������  
        {  
            return false;               //�Ѿ����ڣ�����ʧ��  
        }  
  
        Node* cur = product.first;  
        Node* sub = NULL;  
        K newKey = key;  
        while (1)                 
        {  
            _InsertKey(cur, newKey, sub);             //���ؼ�ֵ����  
            if (cur->_size == M)                   //���key�Ѿ�����M-1,����Ҫ����  
            {  
                Node* tmp = new Node;              //����һ�����Ѻ�Ľ��  
                int mid = cur->_size / 2;        //�ҵ�keys������м�λ�õ��±�  
                int j = 0;  
                int i = mid+1;                     //���м�λ�õ���һ��λ�ÿ�ʼ����  
                for (; i <(int)cur->_size; ++i, ++j)  
                {  
                    tmp->_keys[j] = cur->_keys[i];        //���ؼ��ָ��Ƶ�tmp��  
                    tmp->_subs[j] = cur->_subs[i];        //������Ҳ���Ƶ�tmp��  
                    if (tmp->_subs[j])                    //������Ӳ�Ϊ�գ�������ָ����ѵĽ��  
                        tmp->_subs[j]->_parent= tmp;  
                    cur->_keys[i] = K();  
                    cur->_subs[i] = NULL;  
                    tmp->_size++;  
                }  
                //�����һ���Һ���Ҳ���ƹ���  
                tmp->_subs[j] = cur->_subs[i];  
                if (tmp->_subs[j])  
                    tmp->_subs[j]->_parent = tmp;  
                cur->_subs[i] = NULL;  
  
                newKey = cur->_keys[mid];  
                cur->_keys[mid] = K();  
                sub = tmp;  
                cur->_size = mid;  
  
                if (cur == _root)                //������ѵĽ���Ǹ��ڵ�  
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
            else                                //����Ҫ���ѣ��Ѿ�ƽ��  
                break;  
        }  
        return true;  
    }  
  
    bool Remove(const K& key)  
    {  
        if (_root == NULL)               //��Ϊ��������ɾ��ʧ��  
        {  
            return false;  
        }  
        pair<Node*, int> product = Find(key);  
        if (product.second == -1)              //���key�������У���ɾ��ʧ��  
        {  
            return false;  
        }  
        Node* cur = product.first;             
        int pos = product.second;                //��¼Ҫɾ����λ��  
        //���ж�Ҫɾ���Ĺؼ������ڽ���ǲ���Ҷ�ӽ�㣬������ǵĻ���Ҫ�Ƚ��ؼ��뽻����Ҷ�ӽ����  
        if (cur->_subs[pos + 1] != NULL)    //���Ҫɾ���Ĺؼ������������Ϊ�գ����Ƿ�Ҷ�ӽ���ɾ��  
        {  
            Node* minkey = cur->_subs[pos + 1];          //������¼Ҫɾ���Ĺؼ��������������С�ļ�ֵ  
            while (minkey->_subs[0])  
            {  
                minkey = minkey->_subs[0];  
            }  
            //ת����ɾ�������С�Ĺؼ���  
            cur->_keys[pos] = minkey->_keys[0];  
            cur = minkey;  
            _MoveLeft(cur, 0);           //�ѽ�����Ĺؼ���ɾ����  
        }  
        else  
            _MoveLeft(cur, pos);  
  
        //�ж��Ƿ�����B����������������Ļ���Ҫ����  
        int mid =(M+1)/2-1;        //����ؼ������������,�ؼ�������ΪM/2-1,����ȡ��  
        while (1)  
        {  
            if ((int)cur->_size < mid)   //�ؼ���ĸ���С������ֵ����Ҫ���е���  
            {  
                if (cur == _root)  
                    break;  
                Node* parent = cur->_parent;  
                pos = 0;  
                while (parent->_subs[pos] != cur&&pos < (int)parent->_size)  
                    pos++;  
                if (pos == 0)   //���������  
                    _LeftAdjust(parent, cur, mid, pos);  
                else  
                    _RightAdjust(parent, cur, mid, pos-1);  
                cur = parent;  
            }  
            else                     //�����С������ֵ�Ļ������ʾ�Ѿ�����B������������ֱ���˳�  
                break;  
        }  
  
        if (_root->_size == 0)         //�������֮����Ĺؼ�������Ѿ���Ϊ0����Ҫ�ѵ�ǰ��ɾ�����������ĺ��ӵ�����  
        {  
            Node* del = _root;            //��¼Ҫɾ�������  
            _root = _root->_subs[0];  
            if (_root)  
                _root->_parent = NULL;        //���¸��ĸ����ÿ�  
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
    void _LeftAdjust(Node* parent, Node* cur, int mid, int pos)      //��ǰ���cur�������׵���ߣ�cur���������ֵܽ��е���  
    {  
        //���cur�����ֵܵĹؼ���ĸ����Ѿ����ڹؼ�������ޣ����ͨ���������  
        Node* right = parent->_subs[pos+1];       //rightָ��cur�����ֵ�  
        if ((int)right->_size>mid)      //���ڹؼ�������ޣ�ͨ���������  
        {  
            cur->_size++;  
            cur->_keys[cur->_size - 1] = parent->_keys[pos];       //�Ѹ��ڵ����Ӧ�ؼ�������  
            parent->_keys[pos] = right->_keys[0];                  //�����ֵܵ���С�ؼ������Ƶ����׹ؼ���λ��  
            //�����ֵܵ��������ƶ���cur�����Һ��Ӵ�  
            cur->_subs[cur->_size] = right->_subs[0];  
            if (right->_subs[0])  
            {  
                right->_subs[0]->_parent = cur;            //��������ӵĸ���ָ��cur  
            }  
            right->_subs[0] = right->_subs[1];  
            _MoveLeft(right, 0);                                    //�����ֵ���ʣ��Ĺؼ��������ƶ�  
        }  
        else              //ֻ��ͨ���ϲ����  
            _Merge(parent,cur,right,pos);  
    }  
  
    void _RightAdjust(Node* parent, Node* cur,int mid, int pos)  //��ǰ���cur�������׵��ұߣ�cur���������ֵܽ��е���  
    {  
        Node* left = parent->_subs[pos];          //leftָ��cur�����ֵ�  
        if ((int)left->_size>mid)               //���ֵܵĹؼ���������ڹؼ������޵�ֵ  
        {  
            //cur�Ȱ�����ߵ�λ�ÿճ������ٰѸ��׽�����Ӧ�ؼ�������  
            _MoveRight(cur,0);  
            cur->_keys[0] = parent->_keys[pos];      //������Ӧ�ؼ�������  
            parent->_keys[pos] = left->_keys[left->_size-1];    //�����ֵ��е����ؼ������Ƶ����ڵ�λ��  
            cur->_subs[0] = left->_subs[left->_size];           //�����ֵ��е����һ�������Ƶ�cur�����  
            if (left->_subs[left->_size])  
            {  
                left->_subs[left->_size]->_parent = cur;         //��������ӽ��ĸ���ָ��cur  
            }  
  
            left->_keys[left->_size - 1] = K();  
            left->_subs[left->_size] = NULL;  
            left->_size--;  
        }  
        else  
            _Merge(parent,left,cur,pos);  
    }  
  
  
    void _Merge(Node* parent,Node* cur,Node* brother,int pos)        //����cur���ϲ��ֵܽ��  
    {  
        int i = cur->_size;     //Ҫ�����λ��  
        cur->_keys[i] = parent->_keys[pos];        //�ȰѸ��׽����Ӧ�Ĺؼ����ֵ�ƶ���������   
        cur->_subs[i + 1] = brother->_subs[0];      //�����ֵܵ��������ƶ�����  
        if (brother->_subs[0])  
            brother->_subs[0]->_parent = cur;  
        i++;  
        cur->_size++;  
        for (int j = 0; j < (int)brother->_size; ++i, ++j)     //���ֵܽ��ָ�뿽������  
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
        _Destory(cur->_subs[i]);                  //�������ұߵĺ���  
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
        _InOder(cur->_subs[i]);                  //�������ұߵĺ���  
    }  
  
    void _InsertKey(Node* cur,const K& key,Node* sub)  
    {  
        int i = cur->_size-1;  
        while (i >= 0)        //��key���뵽B����  
        {  
            if (key < cur->_keys[i])  
            {  
                cur->_keys[i + 1] = cur->_keys[i];  
                cur->_subs[i + 2] = cur->_subs[i+1];  
                --i;  
            }   
            else                                 //key�ȵ�ǰ�ؼ�ֵС������в���  
                break;  
        }  
  
        //key������keys����С�ģ����ڵ�0��λ��  
        cur->_keys[i+1] = key;  
        cur->_subs[i+2] = sub;  
        if (sub != NULL)                  //���Ӳ�Ϊ��  
            sub->_parent = cur;          //���ӵ�parentָ��cur  
        cur->_size++;  
    }  
  
    void _MoveLeft(Node* cur,int pos)                  //��Ҷ�ӽ����ɾ��һ���ؼ���  
    {  
        if (cur == NULL)  
            return;  
        int i = 0;  
        for (i = pos; i < (int)cur->_size; ++i)  
        {  
            cur->_keys[i]=cur->_keys[i+1];                 //��Ҫɾ���Ĺؼ��븲�ǵ�  
            cur->_subs[i+ 1] = cur->_subs[i+ 2];  
        }  
        cur->_size--;                                      
    }  
  
    void _MoveRight(Node* cur,int pos)  
    {  
        int i = cur->_size-1;       //��ǰ������ҹؼ����±�  
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