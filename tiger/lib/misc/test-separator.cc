/**
 ** Test code for misc/separator.hh features.
 */

#include <iostream>
#include <sstream>
#include <vector>

#include <algorithm>
#include <misc/contract.hh>
#include <misc/separator.hh>

int main()
{
  {
    std::vector<int> v(4);
    std::ranges::fill(v, 51);

    std::ostringstream s;
    s << misc::separate(v, ", ");
    assertion(s.str() == "51, 51, 51, 51");
  }

  {
    std::vector<int> v(4);
    std::ranges::fill(v, 51);

    std::ostringstream s;
    s << misc::separate(v, std::make_pair(",", " "));
    assertion(s.str() == "51, 51, 51, 51");
  }

  {
    int p = 51;
    std::vector<int*> v(4);
    std::ranges::fill(v, &p);

    std::ostringstream s;
    s << misc::separate(v, ", ");
    assertion(s.str() == "51, 51, 51, 51");
  }
}
