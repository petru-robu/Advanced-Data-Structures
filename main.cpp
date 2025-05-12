#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>
#include "./structures/splay-trees.h"
#include "./structures/skip-lists.h"
#include "./structures/BTree.h"

std::ofstream fout("output.txt");
void test_splay(std::string file_path)
{
    std::ifstream fin(file_path);
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
            splay_tree.search(x);
        }
        else if(tip == 4)
        {
            splay_tree.largest_below(x);
        }
        else if(tip == 5)
        {
            splay_tree.smallest_above(x);
        }
        else if(tip == 6)
        {
            fin>>y;
            std::vector<int> range = splay_tree.sorted_range(x, y);
        }
    }
}
void test_skip(std::string file_path)
{
    std::ifstream fin(file_path);
    SkipList lista;
    int Q, op, a, b;
    fin >> Q;
    // cout<<Q<<"\n";
    while (Q--)
    {
        fin >> op;
        if (op == 1)
        {
            fin >> a;
            lista.insert(a);
        }
        if (op == 2)
        {
            fin >> a;
            lista.remove(a);
        }
        if (op == 3)
        {
            fin >> a;
            lista.contains(a);
        }
        if (op == 4)
        {
            fin >> a;
            lista.findLargestLessThanOrEqual(a);
        }
        if (op == 5)
        {
            fin >> a;
            lista.findSmallestGreaterThanOrEqual(a);
        }
        if (op == 6)
        {
            fin >> a >> b;
            std::vector<int> range = lista.findRange(a, b);
        }
        // cout<<op<<" "<<a<<"\n";
        // lista.printList();
    }
}

void test_btree(std::string file_path)
{
    std::ifstream fin(file_path);
    BTree t(32);
    int Q;
    fin >> Q;
    while (Q--) 
    {
        int task;
        fin >> task;
        if (task == 1) 
        {
            int k;
            fin >> k;
            t.insert(k);
        }
        else if (task == 2) 
        {
            int k;
            fin >> k;
            t.remove(k);
        }
        else if (task == 3) 
        {
            int k;
            fin >> k;
            t.search(k);
        }
        else if (task == 4)
        {
            int x;
            fin >> x;
            t.largestSmallerThanX(x);
        }
        else if (task == 5) 
        {
            int x;
            fin >> x;
            t.smallestLargerThanX(x);
        }
        else if (task == 6) 
        {
            int x, y;
            fin >> x >> y;
            t.traverse(x, y);
        }
    }
}


std::vector<std::string> input_files = {
        "./tests/insertion_heavy0.in",
        "./tests/insertion_heavy1.in",
        "./tests/insertion_heavy2.in",
        "./tests/insertion_heavy3.in",
        "./tests/insertion_heavy4.in",
        "./tests/remove_heavy0.in",
        "./tests/remove_heavy1.in",
        "./tests/remove_heavy2.in",
        "./tests/remove_heavy3.in",
        "./tests/remove_heavy4.in",
        "./tests/search_heavy0.in",
        "./tests/search_heavy1.in",
        "./tests/search_heavy2.in",
        "./tests/search_heavy3.in",
        "./tests/search_heavy4.in",
        "./tests/average0.in",
        "./tests/average1.in",
        "./tests/average2.in",
        "./tests/average3.in",
        "./tests/average4.in"
    };


int main()
{
    std::ofstream fout("output.txt");
    for (const auto& x : input_files) 
    {
        std::cout << "---Processing file: " << x << " ---" << std::endl;
        fout << "---Processing file: " << x << " ---" << std::endl;
        // Time test_splay
        auto start_splay = std::chrono::high_resolution_clock::now();
        test_splay(x);
        auto end_splay = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_splay = end_splay - start_splay;
        std::cout << "test_splay time: " << std::fixed << std::setprecision(10) << duration_splay.count() << " seconds" << std::endl;

        // Time test_skip
        auto start_skip = std::chrono::high_resolution_clock::now();
        test_skip(x);
        auto end_skip = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_skip = end_skip - start_skip;
        std::cout << "test_skip time: " << std::fixed << std::setprecision(10) << duration_skip.count() << " seconds" << std::endl;
        fout << "test_skip time: " << std::fixed << std::setprecision(10) << duration_skip.count() << " seconds" << std::endl;

        // Time test_btree
        auto start_btree = std::chrono::high_resolution_clock::now();
        test_btree(x);
        auto end_btree = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_btree= end_btree - start_btree;
        std::cout << "test_btree time: " << std::fixed << std::setprecision(10) << duration_btree.count() << " seconds" << std::endl;
        fout << "test_skip time: " << std::fixed << std::setprecision(10) << duration_skip.count() << " seconds" << std::endl;
    }
    return 0;
}