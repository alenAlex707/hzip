#include "huffman.h"
#include <fstream>
#include <queue>

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

Node *buildTree(std::unordered_map<char, int> freq)
{
  std::priority_queue<Node *, std::vector<Node *>, Compare> pq;
  for (auto &pair : freq)
  {
    Node *newNode = new Node(pair.first, pair.second);
    pq.push(newNode);
  }

  while (pq.size() > 1)
  {
    Node *first = pq.top();
    pq.pop();
    Node *second = pq.top();
    pq.pop();
    Node *X = new Node('\0', first->freq + second->freq);
    X->left = first;
    X->right = second;
    pq.push(X);
  }

  return pq.top();
}

void generateCodes(Node *node, std::string code, std::unordered_map<char, std::string> &table)
{
  if (node == nullptr)
    return;
  if (node->right == nullptr && node->left == nullptr)
  {
    table[node->ch] = code;
    return;
  }
  generateCodes(node->left, code + "0", table);
  generateCodes(node->right, code + "1", table);
}