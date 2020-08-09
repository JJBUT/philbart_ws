#include <nrg_gas_source_localization/nrg_sl_utils.h>

#include <random>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>

namespace pf{
std::vector<double> uniform_rn(int count){   
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};  
    std::uniform_real_distribution<double> dist (0, 1.0);
    
    //TODO can I make this return double instead of auto for clarity
    auto gen = [&dist, &mersenne_engine]()  
    {
        return dist(mersenne_engine);
    };

    std::vector<double> rnv(count);
    std::generate(rnv.begin(), rnv.end(), gen);

    return rnv;
}

double uniform_rn(){   
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random doubles
    std::uniform_real_distribution<double> dist (0, 1.0);
    
    return dist(mersenne_engine);
}

void transform(double source_local_test_point[3], const double test_point[3], const double source[3], const double& rotation){
    double temp_local[3];

    // Translation
    temp_local[0] = test_point[0] - source[0];
    temp_local[1] = test_point[1] - source[1];
    temp_local[2] = test_point[2] - source[2];

    // Rotation
    double R[3][3] = {};
    R[0][0] = cos(rotation);
    R[0][1] = -sin(rotation);
    R[1][0] = sin(rotation);
    R[1][1] = cos(rotation);
    R[2][2] = 1.0;

    // Recreate np.dot(local,R)
    for (size_t i = 0; i < 3; i++){ // Traverse the vector
        source_local_test_point[i]=0;
        for (size_t j = 0; j < 3; j++){ //Traverse the columns of the matrix
            source_local_test_point[i]+= temp_local[j] * R[j][i];
        }
    }
    return;
}

double gaussian(double x, double mu, double sigma){
    return ( 1/(std::sqrt(2*M_PI)*sigma) )*std::exp( -0.5*std::pow((x-mu)/sigma, 2) );
}

std::vector< std::vector<double> > read_data( std::string input_file_path ){
    std::vector< std::vector<double> > measurements;

    std::ifstream filein( input_file_path );
    if ( filein.is_open() ){
        std::string line; 
        while(std::getline( filein, line )){
            std::istringstream buffer(line);
            std::vector<double> line{std::istream_iterator<double>( buffer ),
                                     std::istream_iterator<double>()};
            measurements.push_back(line);
        }
        filein.close();
        return measurements;
    }
    std::cout<<"read_data() provided bad file handle ;/\n";
}

} //END of pf namespace
