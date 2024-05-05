#include "print_visitor.hh"

#include <iostream>
#include <string>

#include "add.hh"
#include "div.hh"
#include "leaf.hh"
#include "mul.hh"
#include "node.hh"
#include "sub.hh"
#include "tree.hh"

void visitor::PrintVisitor::visit(const tree::Tree& e)
{
    if (std::stoi(e.get_value()) == 0)
        return;
}

void visitor::PrintVisitor::visit(const tree::Node& e)
{
    if (std::stoi(e.get_value()) == 0)
        return;
}

void visitor::PrintVisitor::visit(const tree::AddNode& e)
{
    visitor::PrintVisitor a = visitor::PrintVisitor();
    visitor::PrintVisitor b = visitor::PrintVisitor();

    std::cout << "(";
    e.get_lhs()->accept(a);
    std::cout << " + ";
    e.get_rhs()->accept(b);
    std::cout << ")";
}

void visitor::PrintVisitor::visit(const tree::SubNode& e)
{
    visitor::PrintVisitor a = visitor::PrintVisitor();
    visitor::PrintVisitor b = visitor::PrintVisitor();

    std::cout << "(";
    e.get_lhs()->accept(a);
    std::cout << " - ";
    e.get_rhs()->accept(b);
    std::cout << ")";
}

void visitor::PrintVisitor::visit(const tree::MulNode& e)
{
    visitor::PrintVisitor a = visitor::PrintVisitor();
    visitor::PrintVisitor b = visitor::PrintVisitor();

    std::cout << "(";
    e.get_lhs()->accept(a);
    std::cout << " * ";
    e.get_rhs()->accept(b);
    std::cout << ")";
}

void visitor::PrintVisitor::visit(const tree::DivNode& e)
{
    visitor::PrintVisitor a = visitor::PrintVisitor();
    visitor::PrintVisitor b = visitor::PrintVisitor();

    std::cout << "(";
    e.get_lhs()->accept(a);
    std::cout << " / ";
    e.get_rhs()->accept(b);
    std::cout << ")";
}

void visitor::PrintVisitor::visit(const tree::Leaf& e)
{
    std::cout << std::stoi(e.get_value());
}

int visitor::PrintVisitor::get_value()
{
    return this->value_;
}
