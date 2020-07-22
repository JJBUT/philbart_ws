#include "random"
#include "cmath"

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

position transform(const state& source, const position& test_point, const double yaw)
{
    position temp_local;

    // Translation
    temp_local.pos[0]= test_point.pos[0] - source.s[0];
    temp_local.pos[1]= test_point.pos[1] - source.s[1];
    temp_local.pos[2]= test_point.pos[2] - source.s[2];

    // Rotation
    double R[3][3]= {};
    R[0][0]= cos(yaw);
    R[0][1]= -sin(yaw);
    R[1][0]= sin(yaw);
    R[1][1]= cos(yaw);
    R[2][2]= 1;

    // Recreate np.dot(local,R)
    position local;
    for (size_t i = 0; i < 3; i++) // Traverse the vector
    {
        for (size_t j = 0; j < 3; j++) //Traverse the columns of the matrix
        {
            local.pos[i]+= temp_local.pos[j] * R[j][i];
        }
    }
    return local;
}

} //end sl::