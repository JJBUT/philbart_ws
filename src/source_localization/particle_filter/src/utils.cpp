#include "random"

#include "utils.h"

namespace sl
{
std::vector<double> uniform_dist(int count)
{
    std::vector<double> rnv;    //"random number vector"
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    rnv.resize(count);
    for (size_t i = 0; i < count; i++)
    {
        rnv[i]= distribution(mt);
    }
    

    return rnv;
}

} //end sl::