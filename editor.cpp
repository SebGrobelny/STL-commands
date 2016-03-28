//Authors: Sebastian Grobelny Nicki Padar
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

void replace(string &line2, vector <string> &limerick);
void insert(string &line2, vector <string> &limerick);
void find(string &line2, vector <string> &limerick);
void del(string &line2, vector <string> &limerick);
void erase(string &line2, vector <string> &limerick);
void copy(string &line2, vector <string> &limerick);
void move(string &line2, vector <string> &limerick);

void replace(string &line2, vector <string> &limerick)
{
  string command, start, end, text, lineno;
  int start1, end1, lineno1, desirednum = 0;
  istringstream iss(line2);

  iss >> command >> lineno >> start >> end; 

  text = line2.substr(8);

  lineno1 = atoi(lineno.c_str());
  start1 = atoi(start.c_str());
  end1 = atoi(end.c_str());

  for (vector<string>::iterator s = limerick.begin(); s != limerick.end(); s++)
  {

    if (desirednum == lineno1) //when it reaches the correct line number
    {
      s->replace(start1, end1 - start1, text, 0, text.size());
    } //if

  desirednum++;
  } //for
} //replace()

void insert(string &line2, vector <string> &limerick)
{
  string command, lineno, start, text;
  int lineno1, start1, desirednum = 0;

  istringstream iss(line2);

  iss >> command >> lineno >> start;
  text = line2.substr(6);//getline(iss, text); //text to insert

  lineno1 = atoi(lineno.c_str());
  start1 = atoi(start.c_str());

  for (vector<string>::iterator s = limerick.begin(); s != limerick.end(); s++)
  {

    if (desirednum == lineno1) //when it reaches the correct line number
    {
      s->insert(start1, text, 1, text.size()); //figure out syntax
    } //if

  desirednum++;
  } //for
} // insert()

void find(string &line2, vector <string> &limerick)
{
  string f, command;
  vector <int> it;
  int linenum = -1;

  istringstream iss(line2);
  iss >> command >> f;
  cout << f;

  for (vector<string>::iterator s = limerick.begin(); s != limerick.end(); s++)
  {
    it.push_back(s -> find(f));
  } //for

  for (vector<int>::iterator i = it.begin(); i != it.end(); i++)
  {			
    linenum++;

    if (*i >= 0)
      cout << " " << linenum; 

  } //for

 // cout << endl;
} //find()

void del(string &line2, vector <string> &limerick)
{
  string num1, num2, command;
  istringstream iss(line2);
  int linenumber = 0, n1, n2;

  iss >> command >> num1 >> num2;

  n1 = atoi(num1.c_str());
  n2 = atoi(num2.c_str());

  vector <string>::iterator s = limerick.begin();

  while(s != limerick.end())
  {

    if (linenumber <= n2 && linenumber >= n1)
    {
      s = limerick.erase(s);
      linenumber++;
    } //if

    else //else
    {
      s++;
      linenumber++;
    } //else
  } //while
} //del()

void erase(string &line2, vector <string> &limerick)
{
  string text, command;

  text = line2.substr(2);

  for (vector<string>::iterator s = limerick.begin(); s != limerick.end(); s++)
  {

    if (s->find(text) != string::npos)
    {
      s->erase(s->find(text), text.size());

      if (s->size() == 0)
        s = limerick.erase(s);
    } //if
  } //for
} //erase()

void copy(string &line2, vector <string> &limerick)
{
  string command, start, end, destination;
  int start1, end1, destination1;

  istringstream iss(line2);
  iss >> command >> start >> end >> destination;

  start1 = atoi(start.c_str());
  end1 = atoi(end.c_str());
  destination1 = atoi(destination.c_str());

  vector<string>::iterator itr1 = limerick.begin() + start1;
  vector<string>::iterator itr2 = limerick.begin() + end1 + 1;
  vector<string>::iterator itr3 = limerick.begin() + destination1;

  vector<string> tempV(itr1, itr2);
  limerick.insert(itr3, tempV.begin(), tempV.end());
} //copy()

void move(string &line2, vector <string> &limerick)
{
  string command, start, end, destination;
  int start1, end1, destination1;

  istringstream iss(line2);
  iss >> command >> start >> end >> destination;

  start1 = atoi(start.c_str());
  end1 = atoi(end.c_str());
  destination1 = atoi(destination.c_str());

  vector<string>::iterator itr1 = limerick.begin() + start1;
  vector<string>::iterator itr2 = limerick.begin() + end1 + 1;
  vector<string>::iterator itr3 = limerick.begin() + destination1;

  vector<string> tempV(itr1, itr2);
  limerick.insert(itr3, tempV.begin(), tempV.end());

  limerick.erase(itr1, itr2);
  //limerick.erase(itr2);
  
} //move()

int main(int argc, const char **argv)
{
  ifstream inf(argv[1]);  //limerick
  ifstream inf2(argv[2]); //commands
  ofstream outf(argv[3]); //result file
  string line;
  string line2;
  vector<string> limerick;
  vector<string> s2;

  while(getline(inf, line))
  {
    limerick.push_back(line);
  } //while

  while(getline(inf2, line2))
  {	
    char command;
    istringstream iss(line2);
    iss >> command;

    switch (command)
    {
      case 'I' : insert(line2, limerick); break; //insert
      case 'R' : replace(line2, limerick); break; //replace
      case 'F' : find(line2, limerick); break; //find
      case 'D' : del(line2, limerick); break; //delete lines
      case 'E' : erase(line2, limerick); break; //erase words
      case 'C' : copy(line2, limerick); break; //copy
      case 'M' : move(line2, limerick); break; //move
    } //swtich
  } //while

	//for (vector<string>::iterator s = limerick.begin(); s != limerick.end(); s++)
	//{
		//cout << *s << endl;
	//}

  for (vector<string>::iterator p = limerick.begin(); p!= limerick.end(); p++)
  {
    outf << *p << endl;
  } //for

  return 0;
} //main
