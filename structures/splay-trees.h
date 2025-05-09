/*
Splay Trees
Operations to support:
1.insert(value)
2.delete(value)
3.test if value in set
4.greatest number below a value
5.lowest number above a value
6.all numbers in range [x, y] in sorted order 
*/

#include <bits/stdc++.h>

class Node
{
public:
    int val;
    Node *left, *right;
    Node(int val): val(val), left(nullptr), right(nullptr) {}
};

class SplayTree
{
private:
    Node* root;

    void rotateRight(Node*& node)
    {
        Node* temp = node->left;
        node->left = temp->right;

        temp->right = node;
        node = temp;
    }

    void rotateLeft(Node*& node) 
    {
        Node* temp = node->right;
        node->right = temp->left;

        temp->left = node;
        node = temp;
    }

    void splay(Node*& node, int key) 
    {
        if(node == nullptr || node->val == key)
            return;

        if(key < node->val) 
        {
            if(!node->left)
            {
                return;
            }

            if(key < node->left->val) 
            {
                //Zig-Zig case
                if(node->left->left)
                    splay(node->left->left, key);

                rotateRight(node);
            } 
            else if(key > node->left->val) 
            {
                //Zig-Zag case
                if(node->left->right)
                    splay(node->left->right, key);

                if(node->left->right)
                    rotateLeft(node->left);
            }

            if(node->left)
                rotateRight(node);
        } 
        else 
        {
            if(node->right == nullptr) 
                return;

            if(key > node->right->val) 
            {
                //Zag-Zag case
                if(node->right->right)
                    splay(node->right->right, key);

                rotateLeft(node);
            } 
            else if(key < node->right->val) 
            {
                //Zag-Zig case
                if(node->right->left)
                    splay(node->right->left, key);

                if(node->right->left)
                    rotateRight(node->right);
            }

            if(node->right)
                rotateLeft(node);
        }
    }

    void postOrder(Node* node) 
    {
        if(!node)
        {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        std::cout<<node->val<<' ';
    }

    void levelOrder(Node* node) 
    {
        if(!node)
        {
            return;
        }

        std::queue<Node*> q;
        q.push(node);

        while(!q.empty()) 
        {
            Node* curr = q.front(); 
            q.pop();

            std::cout<<curr->val<<' ';

            if (curr->left) 
                q.push(curr->left);
               
            if (curr->right) 
                q.push(curr->right); 
        }
    }

    void sorted_range_helper(Node* node, int x, int y, std::vector<int>& result) 
    {
        if (!node) 
            return;
    
        if (node->val > x)
            sorted_range_helper(node->left, x, y, result);
        
        if (node->val >= x && node->val <= y)
            result.push_back(node->val);
    
        if (node->val < y)
            sorted_range_helper(node->right, x, y, result);
    }

public:
    SplayTree(): root(nullptr) {}
 
    void post_order() 
    {
        postOrder(root);
        std::cout<<'\n';
    }

    void level_order() 
    {
        levelOrder(root);
        std::cout<<'\n';
    }

    void insert(int key) 
    {
        if (!root) 
        {
            root = new Node(key);
            return;
        }
    
        Node* node = root;
        Node* parent = nullptr;
    
        //BST standard insertion
        while(node) 
        {
            parent = node;

            if (key < node->val)
                node = node->left;
            else if (key > node->val)
                node = node->right;
            else
                break; //key already present
        }
    
        if(!node) 
        {
            //add the key in right place
            Node* newNode = new Node(key);

            if (key < parent->val)
                parent->left = newNode;
            else
                parent->right = newNode;
        }

        splay(root, key);
    }

    Node* search(int key) 
    {
        //splay the tree
        splay(root, key);

        //key should be at the top
        if (root != nullptr && root->val == key) 
            return root;
        else 
            return nullptr;
    }

    void remove(int key)
    {
        if(root == nullptr)
            return;

        //splay the tree
        splay(root, key);

        //key not in tree
        if(root->val != key)
            return;

        Node* temp = root;
        if(!root->left)
        {
            root = root->right;
        }
        else
        {
            //combine the left and right subtrees
            Node* leftTree = root->left;
            Node* rightTree = root->right;

            Node* maxNode = leftTree;
            while(maxNode->right)
                maxNode = maxNode->right;
            
            splay(leftTree, maxNode->val);
            leftTree->right = rightTree;

            root = leftTree;
        }
        delete temp;
    }

    int largest_below(int key)
    {
        Node* node = root;
        int ans = -1;

        while(node)
        {
            if(node->val == key)
            {
                return node->val;
            }
            else if(node->val < key)
            {
                ans = node->val;
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        return ans;
    }
    
    int smallest_above(int key)
    {
        Node* node = root;
        int ans = -1;

        while(node)
        {
            if(node->val == key)
            {
                return node->val;
            }
            else if(node->val > key)
            {
                ans = node->val;
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return ans;
    }

    std::vector<int> sorted_range(int x, int y) 
    {
        std::vector<int> result;
        sorted_range_helper(root, x, y, result);
    
        return result;
    }
};