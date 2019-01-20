#include <cstdlib>
#include <iostream>
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "TNTree.h"
#include <random>

int main(int argc, char** argv) {
    TNTree<Figure> tree_triangle;
    typedef std::function<void (void)> command;
    TNTree<command> tree_cmd;;

	command cmd_insert = [&]() {
		std::cout << "Command: Create triangles" << std::endl;
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 10);

		for (int i = 0; i < 10; i++) {
			int side = 10 - i; //distribution(generator);
			tree_triangle.push(std::shared_ptr<Figure>(new Square(side)));
		}
	};

	command cmd_print = [&]() {
        std::cout << "Command: Print tree" << std::endl;
        std::cout << tree_triangle << std::endl;
    };

    command cmd_reverse = [&]() {
        std::cout << "Command: Reverse tree" << std::endl;
        
        TNTree<Figure> tree_tmp;
        while(!tree_triangle.empty())
			tree_tmp.push(tree_triangle.pop_last());
        while(!tree_tmp.empty())
			tree_triangle.push(tree_tmp.pop());
    };

    tree_cmd.push(std::shared_ptr<command> (&cmd_print, [](command*) {
    })); // using custom deleter
    tree_cmd.push(std::shared_ptr<command> (&cmd_reverse, [](command*) {
    })); // using custom deleter
    tree_cmd.push(std::shared_ptr<command> (&cmd_print, [](command*) {
    })); // using custom deleter
    tree_cmd.push(std::shared_ptr<command> (&cmd_insert, [](command*) {
    })); // using custom deleter


    while (!tree_cmd.empty()) {
        std::shared_ptr<command> cmd = tree_cmd.pop();
        std::future<void> ft = std::async(*cmd);      
        ft.get();
        //std::thread(*cmd).detach();
    }


    return 0;
}
