#include <iostream>
#include "huffman.h"

int main()
{
  auto freq = getFrequency("../test.txt");

  for (auto &pair : freq)
  {
    std::cout << pair.first << ":" << pair.second << "\n";
  }

  return 0;
}