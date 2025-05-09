#include <bits/stdc++.h>
#include "./structures/splay-trees.h"

void test_splay()
{
    std::ifstream fin("./tests/input_1.txt");
    std::ofstream fout("output.txt");    

    SplayTree splay_tree;
    int Q;
    fin>>Q;

    while(Q--)
    {
        int tip, x, y;
        fin>>tip>>x;


        if(tip == 1)
        {
            splay_tree.insert(x);
        }
        else if(tip == 2)
        {
            splay_tree.remove(x);
        }
        else if(tip == 3)
        {
            if(splay_tree.search(x))
                fout<<1<<'\n';
            else
                fout<<0<<'\n';
        }
        else if(tip == 4)
        {
            int lb = splay_tree.largest_below(x);
            fout<<lb<<'\n';
        }
        else if(tip == 5)
        {
            int sa = splay_tree.smallest_above(x);
            fout<<sa<<'\n';
        }
        else if(tip == 6)
        {
            fin>>y;
            std::vector<int> range = splay_tree.sorted_range(x, y);

            for(auto &x: range)
                fout<<x<<' ';
            fout<<'\n';
        }
    }
}



int main()
{   
    test_splay();
    return 0;
}