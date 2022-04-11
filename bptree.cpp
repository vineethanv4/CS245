#include <bits/stdc++.h>

using namespace std;

class Node
{
    bool isLeaf;
    vector<int> keys;
    vector<Node *> ptr;
    friend class bptree;
};

class bptree
{
    int d, t;
    Node *root;
    int ni = 0, nd = 0;
    void insertInternal(int, Node *, Node *);
    Node *findParent(Node *, Node *);
    // void dis(Node *);

public:
    bptree(int d, int t);
    int insert(int);
    void display();
};

bptree::bptree(int datn, int tind)
{
    d = datn;
    t = tind;
    root = nullptr;
}

Node *bptree::findParent(Node *cursor, Node *child)
{
    Node *parent;
    if (cursor->isLeaf || cursor->ptr[0]->isLeaf)
    {
        return (nullptr);
    }
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        if (cursor->ptr[i] == child)
        {
            parent = cursor;
            return parent;
        }
        else
        {
            parent = findParent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

void bptree::insertInternal(int n, Node *cursor, Node *newLeaf)
{
    if (cursor->keys.size() < 2 * t + 1)
    {
        Node *dump = new Node;
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size(); j > i + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i + 1] = newLeaf;
    }
    else
    {
        Node *newinter = new Node;
        cursor->keys.push_back(n);
        Node *dump = new Node;
        newinter->isLeaf = false;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i1 = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size(); j > i1 + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i1 + 1] = newLeaf;
        auto k = cursor->keys.begin() + t + 1;
        for (auto i = k; i != cursor->keys.end(); i++)
        {
            newinter->keys.push_back(*i);
        }

        cursor->keys.erase(k, cursor->keys.end());
        k = cursor->keys.begin() + t;
        int no = *k;
        cursor->keys.erase(k);

        auto it2 = cursor->ptr.begin() + t + 1;
        for (auto i = it2; i != cursor->ptr.end(); i++)
        {
            newinter->ptr.push_back(*i);
        }
        cursor->ptr.erase(it2, cursor->ptr.end());
        if (cursor == root)
        {
            Node *newroot = new Node;

            newroot->keys.push_back(no);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newinter);
            newroot->isLeaf = false;
            root = newroot;
            ni++;
        }
        else
        {
            insertInternal(no, findParent(root, cursor), newinter);
        }
        ni++;
    }
}

int bptree::insert(int n)
{
    if (root == nullptr)
    {
        root = new Node();
        root->keys.push_back(n);
        root->isLeaf = true;
        nd++;
        return (1);
    }
    Node *cursor = root;
    Node *parent;
    while (cursor->isLeaf == false)
    {
        parent = cursor;
        for (int i = 0; i < cursor->keys.size(); i++)
        {
            if (n < cursor->keys[i])
            {
                cursor = cursor->ptr[i];
                break;
            }
            if (i == cursor->keys.size() - 1)
            {
                cursor = cursor->ptr[i + 1];
                break;
            }
        }
    }
    if (cursor->keys.size() < 2 * d)
    {
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
    }
    else
    {
        Node *newLeaf = new Node;
        cursor->keys.push_back(n);
        newLeaf->isLeaf = true;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = cursor->keys.begin() + d;
        for (auto i = it; i != cursor->keys.end(); i++)
        {
            newLeaf->keys.push_back(*i);
        }
        cursor->keys.erase(it, cursor->keys.end());
        if (cursor == root)
        {
            Node *newroot = new Node;

            newroot->keys.push_back(newLeaf->keys[0]);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newLeaf);
            newroot->isLeaf = false;
            root = newroot;
            ni++;
        }
        else
        {
            insertInternal(newLeaf->keys[0], parent, newLeaf);
        }
        nd++;
    }
    return (1);
}

void bptree::display()
{
    cout << ni << " " << nd << " ";
    for (auto i = root->keys.begin(); i != root->keys.end(); i++)
    {
        cout << (*i) << " ";
    }
    cout << endl;
}

/*void bptree::dis(Node *cursor)
{
    for (int i = 0; i < cursor->keys.size(); i++)
    {
        cout << cursor->keys[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        dis(cursor->ptr[i]);
    }
}

void bptree::display()
{
    dis(root);
}*/

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    int d, t;
    cin >> d;
    cin >> t;

    bptree bp(d, t);

    int f;
    while (f != 3)
    {
        cin >> f;
        if (f == 1)
        {
            int j;
            cin >> j;
            bp.insert(j);
        }
        else if (f == 2)
        {
            bp.display();
        }
    }
    return (0);
}