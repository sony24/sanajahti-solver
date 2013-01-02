#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

const int x_size = 4, y_size = 4;

vector<string> WORDS;
vector<string> found_words;

void recursion(int, int, string, vector<vector<string> >&, vector<vector<bool> >);
void compare(string&);

int main() {
    string line;
  ifstream myfile("C:\\Users\\Roope\\Desktop\\sanajahti\\sanalista2.txt");
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      WORDS.push_back(line);
    }
    myfile.close();
  }

    while(true) {
        vector<vector<string> > INPUT;
        cout << "Anna kirjaimet vaakariveittäin: " << endl;
        string in;
        cin >> in;
        if(in.length() != 16) {
            cout << "pituus ei ollut 16..." << endl;
            continue;
        }
        for(int i = 0; i < 4; i++) {
            vector<string> tmp;
            for(int j = 0; j < 4; j++){
                char letter = in.at(i*4 + j);
                tmp.push_back(string(&letter, 1));
            }
            INPUT.push_back(tmp);
        }
        for(int i = 0; i < 4; i++) {
            cout << "rivi: ";
            for(int j = 0; j < 4; j++){
              cout << INPUT[i][j];
            }
            cout << endl;
        }

      for(int x = 0; x < x_size; x++) {
        for(int y = 0; y < y_size; y++) {
          string empty = "";
          vector<vector<bool> > visited;
          vector<bool> tmp(4, false);
          visited.push_back(tmp);visited.push_back(tmp);visited.push_back(tmp);visited.push_back(tmp);
          visited[x][y] = true;
          recursion(x, y, empty, INPUT, visited);
        }
      }
    }
}

void recursion(int x_start, int y_start, string str, vector<vector<string> >& INPUT, vector<vector<bool> > visited2) {
  
  str.append(INPUT[x_start][y_start]);
  compare(str);
  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      int k = x_start + i;
      int l = y_start + j;

      if(i == 0 && j == 0) {
        continue;
      }
      else if(k < 0 || k >= x_size || l < 0 || l >= y_size) {
        continue;
      }
      else if(visited2[k][l] == false) {
        vector<vector<bool> > visited = visited2;
        visited[k][l] = true;
        recursion(k, l, str, INPUT, visited);
      }
    }
  }
}

void compare(string& str) {
  if(str.length() < 3) {
    return;
  }
  for(int i = 0; i < found_words.size(); i++) {
    if(str.compare(found_words[i]) == 0) {
      return;
    }
  }
  if(binary_search(WORDS.begin(), WORDS.end(), str)) {
      cout << str << endl;
      found_words.push_back(str);
  }
}
