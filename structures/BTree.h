#include<bits/stdc++.h>

class BTreeNode {
    int n; // number of keys
    int *key;
    int t; // minimum degree
    BTreeNode* *child;
    bool leaf;

private:
    BTreeNode(int _t, bool _leaf)
    {
        t = _t;
        leaf = _leaf;

        key = new int[2*t-1];
        child = new BTreeNode *[2*t];

        n = 0;
    }

    void splitChild(int i) {
        BTreeNode *y = child[i];
        BTreeNode *z = new BTreeNode(y->t, y->leaf);
        z->n = t - 1;

        // Copy the last (t-1) keys of y to z
        for (int j = 0; j < t-1; j++)
            z->key[j] = y->key[j+t];

        // Copy the last t children of y to z
        if (y->leaf == false)
        {
            for (int j = 0; j < t; j++)
                z->child[j] = y->child[j+t];
        }

        // Reduce the number of keys in y
        y->n = t - 1;

        // Create space for new child
        for (int j = n; j >= i+1; j--)
            child[j+1] = child[j];
        child[i+1] = z;

        // Create space for new key
        for (int j = n-1; j >= i; j--)
            key[j+1] = key[j];
        key[i] = y->key[t-1];

        // Increment count of keys in this node
        n++;
    }

    void insert(int k) {
        int i = n-1;

        if (leaf == true) {
            while (i >= 0 && key[i] > k) {
                key[i+1] = key[i];
                i--;
            }

            // Insert the new key at found location
            key[i+1] = k;
            n++;
        }
        else {
            while (i >= 0 && key[i] > k)
                i--;

            if (child[i+1]->n == 2*t-1) { // Full Node
                splitChild(i+1);

                if (key[i+1] < k)
                    i++;
            }
            child[i+1]->insert(k);
        }
    }

    BTreeNode* search(int k) {
        int i = 0;
        while (i < n && k > key[i])
            i++;

        if (i < n && k == key[i])
            return this;

        if (leaf)
            return NULL;

        return child[i]->search(k);
    }

    int largestSmallesThanX(int x) {
        int result = -1000000000;
        int i = 0;
        while (i < n && x > key[i])
            i++;
        if (i > 0)
            result = key[i-1];

        if (i < n && x == key[i])
            return x;

        if (leaf)
            return result;

        return std::max(result, child[i]->largestSmallesThanX(x));
    }

    int smallestLargerThanX(int x) {
        int result = 1000000000;
        int i = 0;
        while (i < n && x > key[i])
            i++;
        if (i < n)
            result = key[i];

        if (i < n && x == key[i])
            return x;

        if (leaf)
            return result;

        return std::min(result, child[i]->smallestLargerThanX(x));
    }

    void traverse(int x, int y)
    {
        int i;
        for (i = 0; i < n; i++) {
            if (leaf == false)
                child[i]->traverse(x, y);
            //if (key[i] >= x && key[i] <= y)
                //cout << key[i] << " ";
        }

        // Print the subtree rooted with last child
        if (leaf == false)
            child[i]->traverse(x, y);
    }

    void removeFromLeaf (int idx) {
        for (int i=idx+1; i<n; ++i)
            key[i-1] = key[i];
        n--;
    }

    void merge(int idx) {
        BTreeNode *leftChild = child[idx];
        BTreeNode *rightChild = child[idx + 1];

        // Give a key to the child bellow
        leftChild->key[t - 1] = key[idx];

        // Copying the keys from rightChild to leftChild at the end
        for (int i=0; i<rightChild->n; ++i)
            leftChild->key[i + t] = rightChild->key[i];

        // Copying the leftChild pointers from rightChild to leftChild
        if (!leftChild->leaf) {
            for(int i=0; i<=rightChild->n; ++i)
                leftChild->child[i + t] = rightChild->child[i];
        }

        for (int i=idx + 1; i<n; ++i)
            key[i - 1] = key[i];

        for (int i=idx + 2; i<=n; ++i)
            child[i - 1] = child[i];

        // Updating the key count of leftChild and the current node
        leftChild->n += rightChild->n+1;
        n--;

        delete(rightChild);
    }
    
    void removeFromNonLeaf(int i) {

        int k = key[i];

        // If the child BEFORE has enough keys to spare, we steal one
        if (child[i]->n >= t) {
            BTreeNode *cur=child[i];
            while (!cur->leaf)
                cur = cur->child[cur->n];
            int pred = cur->key[cur->n-1];

            key[i] = pred;
            child[i]->remove(pred);
        }

        // If the child AFTER has enough keys to spare, we steal one
        else if (child[i + 1]->n >= t) {
            BTreeNode *cur = child[i + 1];
            while (!cur->leaf)
                cur = cur->child[0];
            int succ = cur->key[0];

            key[i] = succ;
            child[i + 1]->remove(succ);
        }

        // Else the 2 children are to be reunited into one
        else {
            merge(i);
            child[i]->remove(k);
        }
    }

    void borrowFromPrev(int idx) {
        BTreeNode *leftChild=child[idx - 1];
        BTreeNode *rightChild=child[idx];

        // Moving all key in rightChild one step ahead
        for (int i=rightChild->n-1; i>=0; --i)
            rightChild->key[i + 1] = rightChild->key[i];

        // If rightChild is not a leaf, move all its sibling pointers one step ahead
        if (!rightChild->leaf) {
            for(int i=rightChild->n; i>=0; --i)
                rightChild->child[i + 1] = rightChild->child[i];
        }

        // Setting rightChild's first key equal to keys[idx-1] from the current node
        rightChild->key[0] = key[idx-1];

        // Moving leftChild's last sibling as child[idx]'s first sibling
        if(!rightChild->leaf)
            rightChild->child[0] = leftChild->child[leftChild->n];

        // Moving the key from the leftChild to the parent
        key[idx - 1] = leftChild->key[leftChild->n - 1];

        rightChild->n += 1;
        leftChild->n -= 1;
    }

    void borrowFromNext(int idx) {
        BTreeNode *leftChild=child[idx];
        BTreeNode *rightChild=child[idx+1];

        // leftChild is inserted as the last key in leftChild
        leftChild->key[(leftChild->n)] = key[idx];

        // rightChild's first child is inserted as the last child
        if (!(leftChild->leaf))
            leftChild->child[(leftChild->n) + 1] = rightChild->child[0];

        //The first key from rightChild is inserted into keys[idx]
        key[idx] = rightChild->key[0];

        // Moving all keys in rightChild one step behind
        for (int i=1; i<rightChild->n; ++i)
            rightChild->key[i - 1] = rightChild->key[i];

        // Moving the leftChild pointers one step behind
        if (!rightChild->leaf) {
            for(int i=1; i<=rightChild->n; ++i)
                rightChild->child[i - 1] = rightChild->child[i];
        }

        // Increasing and decreasing the key count of child[idx] and child[idx+1]
        leftChild->n += 1;
        rightChild->n -= 1;
    }
    
    void fill(int i) {
        if (i!=0 && child[i-1]->n>=t)
            borrowFromPrev(i);

        else if (i!=n && child[i+1]->n>=t)
            borrowFromNext(i);

        else {
            if (i != n)
                merge(i);
            else
                merge(i-1);
        }
    }

    void remove(int k) {
        int i = 0;
        while (i < n && k > key[i])
            i++;

        // The key to be removed is present in this node
        if (i < n && key[i] == k) {
            if (leaf)
                removeFromLeaf(i);
            else
                removeFromNonLeaf(i);
        }
        else {

            // If this node is a leaf node, then the key isn't in the tree
            if (leaf) {
                // std::cout<<"The key "<<k<<" is does not exist in the tree\n";
                return;
            }
            bool flag = ( (i==n)? true : false );

            // Fill the child if it has less than t keys
            if (child[i]->n < t)
                fill(i);

            if (flag && i > n)
                child[i-1]->remove(k);
            else
                child[i]->remove(k);
        }
    }

    friend class BTree;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BTree {
    BTreeNode* root;
    int t;

public:
    BTree(int _t) {
        root = NULL;
        t = _t;
    }

    bool search(int k) {
        return (root == NULL) ? NULL : (root->search(k) != NULL);
    }

    int largestSmallerThanX(int x) {
        return (root == NULL) ? -1000000000 : root->largestSmallesThanX(x);
    }

    int smallestLargerThanX(int x) {
        return (root == NULL) ? 1000000000 : root->smallestLargerThanX(x);
    }

    void traverse(int x, int y) {
        if (root != NULL)
            root->traverse(x, y);
    }

    void insert(int k) {
        if (root == NULL) {
            root = new BTreeNode(t, true);
            root->key[0] = k;
            root->n = 1;
        }
        else
        {
            // If root is full, then tree grows in height
            if (root->n == 2*t-1)
            {
                // New root
                BTreeNode *s = new BTreeNode(t, false);

                // Make old root as child of new root
                s->child[0] = root;

                // Split the old root
                s->splitChild(0);

                int i = 0;
                if (s->key[0] < k)
                    i++;
                s->child[i]->insert(k);

                // Change root
                root = s;
            }
            else  // If root is not full, call insertNonFull for root
                root->insert(k);
        }
    }

    int min() {
        BTreeNode *x = root;
        while (!x -> leaf) {
            x = x -> child[0];
        }

        return x -> key[0];
    }

    int max() {
        BTreeNode *x = root;
        while (!x -> leaf) {
            x = x -> child[x -> n];
        }

        return x -> key[x -> n - 1];
    }

    void remove(int k)
    {
        if (!root)
        {
            // std::cout<< "The tree is empty\n";
            return;
        }

        // Call the remove function for root
        root->remove(k);

        if (root->n==0)
        {
            BTreeNode *tmp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->child[0];

            // Free the old root
            delete tmp;
        }
    }
};
