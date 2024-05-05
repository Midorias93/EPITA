#include "formatted_vector.hh"

#include "format_numerical_data.hh"
#include "state_saver.hh"
#include "vector.hh"

FormattedVector::FormattedVector(double x, double y)
    : FormatNumericalData("[ ", " ]", 12, true, true)
    , Vector(x, y)
{}

FormattedVector::FormattedVector(Vector vec)
    : FormatNumericalData("[ ", " ]", 12, true, true)
    , Vector(vec)
{}

std::ostream& operator<<(std::ostream& os, const FormattedVector& vect)
{
    StateSaver savestate = StateSaver(os);
    vect.formatOs(os);
    return os << vect.prefix << vect.get_x() << " , " << vect.get_y()
              << vect.suffix;
}
