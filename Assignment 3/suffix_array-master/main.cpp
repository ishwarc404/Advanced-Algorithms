#include "suffix_array.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv; 
  
 
  vector<uint64_t> input_indexes = {0, 1, 2, 4};
  int size = input_indexes.size();
  vector<uint64_t> output_indexes(size);
  vector<uint64_t> data = {1, 0, 1, 0, 2};
  int alphabet_size = 3;
  
  suffix_array::radixpass(
    input_indexes,
    output_indexes,
    data,
    0, 
    size,
    alphabet_size
  );
 
  for(auto v: output_indexes) {
    cout << v << "\n";

  }

}


