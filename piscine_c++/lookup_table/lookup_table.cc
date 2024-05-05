#include "lookup_table.hh"

std::optional<long> LookupTable::get(int x)
{
    if (!this->table_.contains(x))
        return std::nullopt;
    return this->table_.find(x)->second;
}

void LookupTable::set(int x, long value)
{
    if (this->table_.contains(x))
        return;
    this->table_.insert({ x, value });
}
