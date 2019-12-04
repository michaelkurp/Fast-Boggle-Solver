#include <iostream>
#include<set>
#include<string>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<fstream>
#include "game.h"
using namespace std;


struct weirdTree
{
  bool isWord;
  unordered_map<char, weirdTree*> character;
  weirdTree(){ isWord = false; }
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
  curr->isWord = true;
}


class BoggleSolver{
public:
  const vector<int> row { -1, -1, -1, 0, 1, 0, 1, 1};
  const vector<int> col { -1, 1, 0, -1, -1, 1, 0, 1};
  vector<string> words;
  unordered_set<string> result;

  inline bool isSafe(int x, int y, bool processed[][5], char board[][5], char ch)
  {
    return (x >= 0 && x < 5) && (y >= 0 && y < 5) && !processed[x][y] && (board[x][y] == ch);
  }

   void searchBoggle(weirdTree* root, char board[][5], int i, int j, bool processed[][5], string path)
  {
    if(root->isWord)
    {
      result.insert(path);
      cout << path;
    }
    processed[i][j] = true;
    for(auto it : root->character)
    {
      for(int k = 0; k < 8; k++)
      {
        if(isSafe(i + row[k], j + col[k], processed, board, it.first))
          searchBoggle(it.second, board, i+ row[k], j+ col[k], processed, path + it.first);
      }
    }
    processed[i][j] = false;
  }
 void searchBoggle(char board[][5])
  {


    weirdTree* root = new weirdTree();
    for(string word: words)
    {
      insert(root, word);
    }
    bool processed[5][5];
    string s;
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; j < 5; j++)
        {
          char ch = board[i][j];
          if(root->character.find(ch) != root->character.end())
          {
            s = ch;
            searchBoggle(root->character[ch], board, i, j, processed, s);
          }
        }
      }
      for(string word: result)
      {
        cout << word << " ";
      }
  }
  BoggleSolver(string str)
  {
    ifstream fDict(str);
    string input;
    while(fDict >> input)
      words.push_back(input);
  }
  unordered_set<string> solve(Boggle boggle)
  {

    vector<char> temp = boggle.getValues();
    char parsedBoard[5][5];
    int count = 0;
    for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 5; j++)
      {
        parsedBoard[i][j] = temp[count];
        count++;
      }
    }



    searchBoggle(parsedBoard);

    return result;
  }

};
