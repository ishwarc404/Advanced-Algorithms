#include <cstdint>
#include <iostream>

namespace suffix_array {

  template<typename Indexes, typename String>
  void radixpass(
    const Indexes& input_offsets,
    Indexes& output_offsets,
    const String &data,
    const uint64_t shift,
    const uint64_t input_size,
    const uint64_t alphabet_size
  ) {
    Indexes cpt(alphabet_size+1);
    for(uint64_t i = 0; i < input_size; ++i) {
      uint64_t character = data[input_offsets[i]+shift];
      ++cpt[character];
    }

    uint64_t somme = 0;
    for(uint64_t i = 0; i <= alphabet_size; ++i) {
      uint64_t freq = cpt[i];
      cpt[i] = somme;
      somme += freq;
    }

    for(uint64_t i = 0; i < input_size; ++i) {
      uint64_t character = data[input_offsets[i]+shift];
      uint64_t pos = cpt[character];
      output_offsets[pos] = input_offsets[i];
      ++cpt[character];
    }
}

}
