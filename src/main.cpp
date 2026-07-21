#include <iostream>
#include <map>
#include "huffman.h"

int main()
{
  std::string infile = "../test.txt";
  std::string outfile = "../outputest.txt";
  auto freq = getFrequency(infile);
  auto tree = buildTree(freq);

  std::unordered_map<char, std::string> table;

  generateCodes(tree, "", table);
  for (auto &pair : table)
  {
    std::cout << pair.first << ":" << pair.second << std::endl;
  }

  encode(infile, outfile, table);

  return 0;
}