#ifndef EXPRTREE_HPP
#define EXPRTREE_HPP


#include <iostream>
#include <cassert>
#include <string>
#include <stack>
#include <deque>
#include <optional>
#include <fstream>
#include <cctype>

using std::string;
using std::deque;
using std::stack;


struct Node {
	string val;
	Node *left = nullptr;
	Node *right = nullptr;

	Node(string &v, Node *l = nullptr, Node *r = nullptr): val{v}, left{l}, right{r} {}
	~Node(){};

	int height(); 

	std::optional<int> eval();
};


deque<string> tokenize(const string &expr); 


Node *parseInfix(deque<string> &tokens);


Node *parsePostfix(deque<string> &tokens);


void getInfixExpression(Node *root, string &output);


void getPostfixExpression(Node *root, string &output);



deque<string> tokenize(const string &expr){
	deque<string> tokens;
    string num;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (isdigit(c)) {
            num += c; 
        } else {
            if (!num.empty()) {
                tokens.push_back(num); 
                num.clear();
            }
            if (isspace(c)) continue; 
            tokens.push_back(string(1, c)); 
        }
    }
    
    if (!num.empty()) {
        tokens.push_back(num);
    }
    
    return tokens;
	

}


Node *parseInfix(deque<string> &tokens){
	Node *aux;

	string token = tokens[0];
	tokens.pop_front();

	if (isdigit(token[0])){
		return new Node(token);
	}
	if (token == "~"){
		aux = new Node(token);
		aux->right = parseInfix(tokens);
		return aux;
	}
	if (token == "("){
		Node* left = parseInfix(tokens);
		std::string op = tokens.front();
        tokens.pop_front();
		Node* right = parseInfix(tokens);
		tokens.pop_front();
		Node* aux = new Node(op);
        aux->left = left;
        aux->right = right;
        return aux;

	}
return nullptr;

}


Node *parsePostfix(deque<string> &tokens){
	deque<Node *> operands;

	Node *aux;
	

	for (string tok : tokens){

		if (isdigit(tok[0])){
			operands.push_back(new Node(tok));
		}
		else if (tok == "~"){
			aux = new Node(tok);
			aux->right = operands[operands.size()-1];
			operands.pop_back();
			operands.push_back(aux);
		}
		else{ // operadores binários
			aux = new Node(tok);
			aux->right = operands[operands.size()-1];
			aux->left = operands[operands.size() -2];
			operands.pop_back();
			operands.pop_back();
			operands.push_back(aux);

		}
	}
	return aux;
	

}


void getInfixExpression(Node *root, string &output){
	if (root ==  nullptr){
		return;
	}
	else if (isdigit(root->val[0])){
		output += root->val;
	}
	else if (root->val == "~"){
		output += root->val;
		getInfixExpression(root->right, output);
	}
	else{
		output += "(";
		getInfixExpression(root->left, output);
		output += root->val;
		getInfixExpression(root->right, output);
		output += ")";
	}
	
}


void getPostfixExpression(Node *root, string &output) {
  if (root == nullptr) {
    return;
  }

  if (root->left != nullptr) {
    getPostfixExpression(root->left, output);
  }
  if (root->right != nullptr) {
    getPostfixExpression(root->right, output);
  }

  if (output.empty()) {
    output += root->val;
  } else {
    output += " " + root->val;
  }
}


int Node::height() {
    if (this == nullptr) {
        return 0;
    }
    int leftHeight = 0;
    int rightHeight = 0;

    if (left != nullptr)
      leftHeight = left->height();
    if (right != nullptr)
      rightHeight = right->height();
    
    if (leftHeight > rightHeight){
      return 1 + leftHeight;
    } else {
      return 1 + rightHeight;
    }
}


std::optional<int> Node::eval() {
    if (isdigit(val[0])) {
        return std::stoi(val);
    }

    if (val == "~") {
        if (right) {
            auto rightVal = right->eval();
            if (rightVal.has_value()) {
                return -rightVal.value();
            }
        }
        return std::nullopt;
    }

    if (left && right) {
        auto leftVal = left->eval();
        auto rightVal = right->eval();

        if (leftVal.has_value() && rightVal.has_value()) {
            int l = leftVal.value();
            int r = rightVal.value();

            if (val == "+") return l + r;
            if (val == "-") return l - r;
            if (val == "*") return l * r;
            if (val == "/") {
                if (r == 0) return std::nullopt;
                return l / r;
            }
        }
    }

    return std::nullopt;
}
#endif