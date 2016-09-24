#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::istringstream;
using std::ifstream;


int
main(int argc, const char *argv[])
{
  map<string, map<unsigned int, unsigned int> > table;
  string word,str;
  unsigned int line;
  istringstream stream; 
  ifstream file;

  if(argc > 1){
    file.open(argv[1],ifstream::in);
    while(getline(file,str)){
      stream.str(str);
      ++line;
      while(stream>>word){
        ++table[word][line];
      }
    stream.str("");
    stream.clear();
    }
  }else{

    while(getline(cin,str)){
      stream.str(str);
      ++line;
      while(stream>>word){
        ++table[word][line];
      }
    stream.str("");
    stream.clear();
    }
  }


  for(map<string, map<unsigned int, unsigned int> >::iterator itr = table.begin(); itr != table.end();++itr){
    cout<<endl<<itr->first<<" ";

    for(map<unsigned int, unsigned int>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end();++itr1){
      cout<<itr1->first<<":"<<itr1->second<<" ";
    }
  }
  cout<<endl;
  file.close();
  return 0;
}


