#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class BoggleDie{
public:
  BoggleDie(string input){ f = input; }
  char roll(){ return f[rand() % 6]; }
private:
  string f;
};

class Boggle{
public:
  Boggle(string test)
  {
    for(auto l : test)
      values.push_back(l);
  }
  Boggle()
  {
    for(auto &y : obj)
      values.push_back(y.roll());
    random_shuffle(values.begin(), values.end());
  }
  vector<char> getValues(){ return values;}
friend ostream& operator<<(ostream& out, const Boggle& bb); //sends a text representation of the boggle to the ostream
private:
  vector<char> values;
   BoggleDie obj[25] = { {"AAAFRS"} , {"AAEEEE"} , {"AAFIRS"} , {"ADENNN"} , {"AEEEEM"} , {"AEEGMU"} , {"AEGMNN"},
  {"AFIRSY"} , {"BJKQXZ"} , {"CCENST"} , {"CEIILT"} , {"CEILPT"} , {"CEIPST"} , {"DDHNOT"} , {"DHHLOR"} ,
  {"DHLNOR"} , {"DHLNOR"} , {"EIIITT"} , {"EMOTTT"} , {"ENSSSU"} , {"FIPRSY"} , {"GORRVW"} , {"IPRRRY"} ,
  {"NOOTUW"} , {"OOOTTU"} };
};

ostream& operator<<(ostream& out, const Boggle& bb)
{
  cout << "\u256d";
  for(int i = 0; i < 15; i++)
    cout << "\u2500";
  cout << "\u256e" << '\n';

  for(int i = 1; i < 26; i++)
  {
    if(i == 1 || i == 6 || i == 11 || i == 16 || i == 21)
      cout << "\u2502";
    if(bb.values[i - 1] == 'Q')
      cout << " Qu";
    else
      cout << " " << bb.values[i - 1] << " ";
    if(i % 5 == 0 && i != 0)
      cout << "\u2502" << '\n';
  }
  cout << "\u2570";
  for(int i = 0; i < 15; i++)
    cout << "\u2500";
  cout << "\u256f" << '\n';
}
