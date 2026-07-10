#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <string>

struct Node
{
  char ch;
  int freq;
  Node *left;
  Node *right;

  Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {} // constructor
};

struct Compare
{
  bool operator()(Node *a, Node *b)
  {
    return a->freq > b->freq;
  }
};

std::unordered_map<char, int> getFrequency(const std::string &filename);
Node *buildTree(std::unordered_map<char, int> freq);

#endif