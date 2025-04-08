#include "exprtree.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        char mode;
        std::cin.get(mode);
        std::cin.ignore();

        std::string expr;
        std::getline(std::cin, expr);

        deque<string> tokens = tokenize(expr);
        Node *root = nullptr;
        std::string convertedExpr;
        std::optional<int> result;

        if (mode == 'I') {
            root = parseInfix(tokens);
            getPostfixExpression(root, convertedExpr);
            } else if (mode == 'P') {
            root = parsePostfix(tokens);
            getInfixExpression(root, convertedExpr);
            
        }

        
        int height = root->height();
        result = root->eval();

        if (result.has_value()) {
            std::cout << convertedExpr << std::endl;
            std::cout << height << " " << result.value() << std::endl;
        } else {
            std::cout << convertedExpr << std::endl;
            std::cout << height << " ?" << std::endl;
        }
       

        delete root;
    }

    return 0;
}