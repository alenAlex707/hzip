#include "huffman.h"
#include <fstream>
#include <queue>
#include <iostream>

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

void generateCodes(Node *treenode, std::string code, std::unordered_map<char, std::string> &table)
{
  if (treenode == nullptr)
    return;
  if (treenode->right == nullptr && treenode->left == nullptr)
  {
    table[treenode->ch] = code;
    return;
  }
  generateCodes(treenode->left, code + "0", table);
  generateCodes(treenode->right, code + "1", table);
}

void encode(const std::string inFile, std::string outFile, std::unordered_map<char, std::string> table)
{
  std::ifstream file(inFile, std::ios::binary);
  std::ofstream out(outFile, std::ios::binary);
  std::unordered_map<char, int> freq;

  char ch;
  int buffer{};
  int bitCount{};

  while (file.get(ch))
  {
    std::string code = table[ch];
    for (int i{}; i < code.length(); i++)
    {
      buffer = (buffer << 1) | (code[i] - '0');
      bitCount++;
      if (bitCount == 8)
      {
        out.put(static_cast<char>(buffer));
        buffer = 0;
        bitCount = 0;
      }
    }
  }
  if (bitCount > 0)
  {
    buffer = buffer << (8 - bitCount);
    out.put(static_cast<char>(buffer));
  }
  file.close();
}
