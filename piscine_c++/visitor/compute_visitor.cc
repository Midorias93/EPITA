#include "compute_visitor.hh"

#include <string>

#include "add.hh"
#include "div.hh"
#include "leaf.hh"
#include "mul.hh"
#include "node.hh"
#include "sub.hh"
#include "tree.hh"

void visitor::ComputeVisitor::visit(const tree::Tree& e)
{
    if (std::stoi(e.get_value()) == 0)
        return;
}

void visitor::ComputeVisitor::visit(const tree::Node& e)
{
    if (std::stoi(e.get_value()) == 0)
        return;
}

void visitor::ComputeVisitor::visit(const tree::AddNode& e)
{
    visitor::ComputeVisitor a = visitor::ComputeVisitor();
    visitor::ComputeVisitor b = visitor::ComputeVisitor();
    e.get_lhs()->accept(a);
    e.get_rhs()->accept(b);
    this->value_ = a.get_value() + b.get_value();
}

void visitor::ComputeVisitor::visit(const tree::SubNode& e)
{
    visitor::ComputeVisitor a = visitor::ComputeVisitor();
    visitor::ComputeVisitor b = visitor::ComputeVisitor();
    e.get_lhs()->accept(a);
    e.get_rhs()->accept(b);
    this->value_ = a.get_value() - b.get_value();
}

void visitor::ComputeVisitor::visit(const tree::MulNode& e)
{
    visitor::ComputeVisitor a = visitor::ComputeVisitor();
    visitor::ComputeVisitor b = visitor::ComputeVisitor();
    e.get_lhs()->accept(a);
    e.get_rhs()->accept(b);
    this->value_ = a.get_value() * b.get_value();
}

void visitor::ComputeVisitor::visit(const tree::DivNode& e)
{
    visitor::ComputeVisitor a = visitor::ComputeVisitor();
    visitor::ComputeVisitor b = visitor::ComputeVisitor();

    e.get_lhs()->accept(a);
    e.get_rhs()->accept(b);

    if (b.get_value() == 0)
        throw std::overflow_error("Divide by zero exception");

    this->value_ = a.get_value() / b.get_value();
}

void visitor::ComputeVisitor::visit(const tree::Leaf& e)
{
    this->value_ = std::stoi(e.get_value());
}

int visitor::ComputeVisitor::get_value()
{
    return this->value_;
}
