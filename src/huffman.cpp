#include "huffman.h"
#include <fstream>

std::unordered_map<char, int> getFrequency(const std::string &filename)
{
  std::ifstream file(filename, std::ios::binary);
  std::unordered_map<char, int> freq;

  char ch;
  while (file.get(ch))
  {
    freq[ch]++;
  }
  
  file.close();
  return freq;
}
