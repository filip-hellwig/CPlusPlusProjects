#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <sstream>

int main(int argc, char *argv[])
{

  std::vector<int> sizes =
  { 10000,
    100000,
    1000000 };

  std::mt19937 rng;

  for(auto size: sizes)
    {
      std::vector<int> data;

      std::generate_n(std::back_insert_iterator<std::vector<int>>{data}, size,
                      std::ref(rng));

      std::ostringstream fileName;
      fileName << "sort_data_" << size << ".bin";

      std::ofstream ofs{fileName.str(), std::fstream::binary};
      for(auto i: data)
        ofs.write(reinterpret_cast<char*>(&i), sizeof(i));

      ofs.flush();

      std::cout << data.size() << std::endl;

    }


  return 0;
}
