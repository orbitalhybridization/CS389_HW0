#include <iostream>
#include <random>
#include <chrono>
#include <cassert>
#include <string>

//with random number generator code from
//https://stackoverflow.com/questions/686353/random-float-number-generation (Andreas DM)

//std::chrono object construction and library-specific type casting from
//https://en.cppreference.com/w/cpp/chrono/duration

using objects_vector = std::vector<double>;

/////////////////////////////////////
//Create a list of 'size' floating point numbers in the range [-bound,bound]

objects_vector generate_random_list(unsigned int size, float bound){

    //create engine for random number generator
    std::default_random_engine e;

    std::uniform_real_distribution<> dis(-bound,bound);
    objects_vector vector(size,0.0);
    
    for(unsigned int i=0;i<size;i++) {
        vector.push_back(dis(e));
    }
    return vector;
}

//////////////////////////////
//Update position by velocity, one time-step
void update_coords(objects_vector& xs, objects_vector& ys, objects_vector& zs, const objects_vector& vx, const objects_vector& vy, const objects_vector& vz) {
    
    for(unsigned int i=0;i<xs.size();i++) {
        xs[i] = xs[i] + vx[i];
        ys[i] = ys[i] + vy[i];
        zs[i] = zs[i] + vz[i];
    }
}

/////////////////////////////
//Main
int main(int argc, char** argv) {
    
    if(argc != 3) {
        std::cerr << "Required arguments: vector_length(N) and iterations_num(M)" << std::endl;
    return -2;
    }
    
    if(atoi(argv[1]) <= 0 or atoi(argv[2]) <= 0) {
        std::cerr << "Vector length and number of iterations must be greater than 0!" << std::endl;
        return -2;
    };   

    const unsigned int size = atoi(argv[1]);
    const unsigned int iters = atoi(argv[2]);

    double mean = 0;
    
    //run 20 times for each number of iterations
    for(unsigned int i=0;i<20;i++){
        //random number generator
        
        objects_vector xs = generate_random_list(size,1000.);
        objects_vector ys = generate_random_list(size,1000.);
        objects_vector zs = generate_random_list(size,1000.);
        objects_vector vx = generate_random_list(size,1.);
        objects_vector vy = generate_random_list(size,1.);
        objects_vector vz = generate_random_list(size,1.);
       
        auto begin = std::chrono::system_clock::now();
        
        for(unsigned int i=0;i<iters;i++){
            
            update_coords(xs,ys,zs,vx,vy,vz);

        };

        auto end = std::chrono::system_clock::now();
    
        double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    
        double microseconds = duration / (size * iters);

        float chksum = accumulate(xs.begin(),xs.end(),0) + accumulate(ys.begin(),ys.end(),0) + accumulate(zs.begin(),zs.end(),0);

        std::cout << "Mean time per coordinate: " << microseconds << "us" << std::endl;
        std::cout << "Final checksum is: " << chksum << std::endl;   
        mean = mean + microseconds;
    }
    mean = mean / 20.0;
    std::cout << "Total mean: " << mean << std::endl;
return 0;
}


