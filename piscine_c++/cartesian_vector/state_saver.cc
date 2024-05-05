#include "state_saver.hh"

#include <iomanip>

StateSaver::StateSaver(std::ostream& os)
    : saved_stream_(os)
{
    this->saved_flags_ = os.flags();
    this->saved_precision_ = os.precision();
}

StateSaver::~StateSaver()
{
    this->saved_stream_.flags(this->saved_flags_);
    this->saved_stream_.precision(this->saved_precision_);
}
