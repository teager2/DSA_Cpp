#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec1{0,1,2,3,4,5,6,7,8,9};

    std::vector<int> vec2(10); // vector with size 100
    for(int i; i<vec2.size();++i ){
        vec2[i] = i*i;
    }

    std::vector<int> vec3{12};

    std::cout << "vec1 ";
    for(auto &i : vec1){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "vec2 ";
    for(auto &i : vec2){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "vec3 ";
    for(auto &i : vec3){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}