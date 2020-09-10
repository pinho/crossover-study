#ifndef _SET_COVERING_PROBLEM_DECODER_H
#define _SET_COVERING_PROBLEM_DECODER_H 1

#include <vector>
#include <core/ga/encoding.h>

class Decoder {
public:
  static std::vector<unsigned int> solution(const Chrom &chrom) {
    std::vector<unsigned int> result;
    for (size_t i=0; i < chrom.size(); i++) {
      if (chrom.at(i)) result.push_back(i+1);
    }
    return result;
  }
};

#endif