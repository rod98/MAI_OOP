#include <cstdlib>
#include <iostream>
#include "figure.h"
#include "triangle.h"
#include "TNTree.h"
#include <random>

int main(int argc, char** argv) {
    TNTree<Figure> tree;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < 10; i++) {
        int side = distribution(generator);
        //int side = 10 - i;

        tree.push(std::shared_ptr<Figure>(new Triangle(side, side, side)));
    }
    tree.PrintTree();

    std::cout << "Sort -------------" << std::endl;

    //tree.sort();
    tree.sort_parallel();
    std::cout << "Done -------------" << std::endl;

    tree.PrintTree();


    return 0;
}
