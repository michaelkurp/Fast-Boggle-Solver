#include <vector>
#include <string>
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
  //Boggle boggle("DYFSFBDKOLISLYVGDVWWTJCOM");
  Boggle boggle;
  BoggleSolver genius("dict.txt");
  set<string> answers = genius.solve(boggle);
  time = clock() - time;

  cout << boggle << endl;

  unsigned int score = 0;

  cout << "Found the following " << answers.size() << " words:" << endl;
  unsigned int count = 0;
  for(string s : answers)
  {
    unsigned int wordLen = s.length();
    if(wordLen >= 8) score += 11;
    else if (wordLen == 7) score += 5;
    else if (wordLen == 6) score += 3;
    else if (wordLen == 5) score += 2;
    else if (wordLen >= 3) score += 1;
    else;
    cout << s << " ";
    if (++count % 10 == 0) cout << endl;
  }
  cout << endl;
  cout << "Elapsed Time: " << (long double)time/CLOCKS_PER_SEC << " seconds" << endl;
  cout << "Score: " << score << endl;
  return 0;
}
