#include "format_numerical_data.hh"

#include <iomanip>
#include <iostream>

FormatNumericalData::FormatNumericalData(const std::string& prefix,
                                         const std::string& suffix,
                                         int precision,
                                         bool scientific_notation,
                                         bool display_plus)
    : prefix(prefix)
    , suffix(suffix)
    , precision(precision)
    , scientific_notation(scientific_notation)
    , display_plus(display_plus)
{}

std::ostream& FormatNumericalData::formatOs(std::ostream& os) const
{
    if (this->precision >= 0)
        os << std::setprecision(this->precision);
    if (this->scientific_notation)
        os << std::scientific;
    if (this->display_plus)
        os << std::showpos;
    return os;
}
