#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>
#include "./structures/splay-trees.h"
#include "./structures/skip-lists.h"

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
void test_skip(std::string file_path){
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
            fout << lista.contains(a) << " \n";
        }
        if (op == 4)
        {
            fin >> a;
            fout << lista.findLargestLessThanOrEqual(a) << " \n";
        }
        if (op == 5)
        {
            fin >> a;
            fout << lista.findSmallestGreaterThanOrEqual(a) << "\n";
        }
        if (op == 6)
        {
            fin >> a >> b;
            std::vector<int> range = lista.findRange(a, b);
            for (auto val : range)
            {
                fout << val << " ";
            }
            fout << "\n";
        }
        // cout<<op<<" "<<a<<"\n";
        // lista.printList();
    }
}


int main()
{
    std::vector < std::string > input_files;
    for(int i=1;i<=20;i++){
        std::string file_path="grade_test" + std::to_string(i) + ".in";
        input_files.push_back(file_path);
    }
    for (const auto& x : input_files) {
        std::cout << "--- Processing file: " << x << " ---" << std::endl;

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
    }
    return 0;
}