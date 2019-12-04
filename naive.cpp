#include <iostream>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

const int row[] = { -1, -1, -1, 0, 1, 0, 1, 1};
const int col[] = { -1, 1, 0, -1, -1, 1, 0, 1};

int count = 0;

struct weirdTree
{
  bool isLeaf;
  unordered_map<char, weirdTree*> character;
  weirdTree(){ isLeaf = false; }
};

 void insert(weirdTree*& root, string str)
{
  weirdTree* curr = root;
  for(char ch : str)
  {
    if(curr->character.find(ch) == curr->character.end())
      curr->character[ch] = new weirdTree();
    curr = curr->character[ch];
  }
  curr->isLeaf = true;
}

inline bool isSafe(int x, int y, bool processed[][5], char board[][5], char ch)
{
  return (x >= 0 && x < 5) && (y >= 0 && y < 5) && !processed[x][y] && (board[x][y] == ch);
}

 void searchBoggle(weirdTree *root, char board[][5], int i, int j, bool processed[][5], string path, unordered_set<string> &result)
{
  if(root->isLeaf)
    result.insert(path);
  processed[i][j] = true;
  for(auto it : root->character)
  {
    for(int k = 0; k < 8; k++)
    {
      if(isSafe(i + row[k], j + col[k], processed, board, it.first))
        searchBoggle(it.second, board, i+ row[k], j+ col[k], processed, path + it.first, result);
    }
  }
  processed[i][j] = false;
}
 void searchBoggle(char board[][5], vector<string> words)
{
  weirdTree* root = new weirdTree();
  for(string word: words)
    insert(root, word);
  unordered_set<string> result;
  bool processed[5][5];
  string s;
    for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 5; j++)
      {
        char ch = board[i][j];
        if(root->character[ch])
        {
          s = ch;
          searchBoggle(root->character[ch], board, i, j, processed, s, result);
        }
      }
    }
    for(string word: result)
    {
      cout << word << " ";
      count++;
    }
}
int main()
{
  auto time = clock();
  vector<string> words;
  ifstream fDict("dict.txt");
  string str;
  while(fDict >> str)
    words.push_back(str);
  char board[5][5] =
  {
    {'o' , 'o' , 'n' , 'w', 'z'},
    {'t', 'a', 'e', 'g', 'e'},
    {'s','f','i','m','u'},
    {'i', 'k', 'c', 'i', 't'},
    {'i', 'h', 'm', 'n' , 's'}
  };
  searchBoggle(board, words);

  time = clock() - time;
  cout << "Elapsed Time: " << (long double)time/CLOCKS_PER_SEC << " seconds " << endl;
  cout << "Count: " << count;
  return 0;
}
