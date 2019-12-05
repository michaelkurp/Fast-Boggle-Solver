#include<set>
#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
#include "game.h"
using namespace std;

class BoggleSolver{
private:
  const int row[8] = { -1, -1, -1, 0, 1, 0, 1, 1};
  const int col[8] = { -1, 1, 0, -1, -1, 1, 0, 1};
  bool processed[5][5] {};
  vector<string> words;
  set<string> result;
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
  inline bool safetyDance(int x, int y, char board[][5], char ch)
  {
    return (x >= 0 && x < 5) && (y >= 0 && y < 5) && !processed[x][y] && (board[x][y] == ch);
  }
  void dfsTomfoolery(weirdTree* root, char board[][5], int i, int j, string path)
  {
    if(root->isLeaf)
      result.insert(path);
    processed[i][j] = true;
    for(auto it : root -> character)
    {
      for(int k = 0; k < 8; k++)
      {
        if (safetyDance(i + row[k], j + col[k], board, it.first))
          dfsTomfoolery(it.second, board, i + row[k], j + col[k], path + it.first);
      }
    }
    processed[i][j] = false;
  }
  void searchBoggle(char board[][5])
  {
    weirdTree* root = new weirdTree();
    for(string word: words)
      insert(root, word);
    string s;
    for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 5; j++)
      {
        char ch = board[i][j];
        if(root->character[ch])
        {
          s = ch;
          dfsTomfoolery(root->character[ch], board, i , j, s);
        }
      }
    }
  }
public:
  BoggleSolver(string str)
  {
    ifstream fDict(str);
    string input;
    while(fDict >> input)
      words.push_back(input);
  }
  set<string> solve(Boggle boggle)
  {
    vector<char> temp;
    temp.reserve(25);
    temp = boggle.getValues();

    char parsedBoard[5][5];
    int count = 0;
    for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 5; j++)
      {
        parsedBoard[i][j] = tolower(temp[count]);
        count++;
      }
    }
    searchBoggle(parsedBoard);
    return result;
  }
};
