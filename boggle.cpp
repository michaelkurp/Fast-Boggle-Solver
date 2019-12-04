#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <ctime>
#include <unordered_set>
#include "bogglesolver.h"
#include "game.h"
#include <unistd.h>
using namespace std;


const char rocket[] =
"           _\n\
          /^\\\n\
          |-|\n\
          |B|\n\
          |O|\n\
          |G|\n\
          |G|\n\
          |L|\n\
         /|E|\\\n\
        / | | \\\n\
       |  | |  |\n\
        `-\"\"\"-`\n\
";
int main()
{
  for (int i = 0; i < 50; i ++) printf("\n"); // jump to bottom of console
  {
    printf("%s", rocket);
    int j = 300000;
    for (int i = 0; i < 50; i ++) {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.92); // so sleep less each time
        printf("\n"); // move rocket a line upward
    }
  }
  cout << R"(
 ____  __.____ ___._______________________
|    |/ _|    |   \   \______   \______   \
|      < |    |   /   ||       _/|     ___/
|    |  \|    |  /|   ||    |   \|    |
|____|__ \______/ |___||____|_  /|____|
        \/                    \/

)" << '\n';
  usleep(100000);

  srand(time(NULL));
  auto time = clock();
  Boggle boggle;
  BoggleSolver genius("dict.txt");
  unordered_set<string> answers = genius.solve(boggle);
  time = clock() - time;

  cout << boggle;

  unsigned int score = 0;

  cout << "Found the following " << answers.size() << " words:" << endl;
  for(string s : answers)
  {
    cout << s << " ";
  }
  return 0;
}
