/*Dane Lowrey
 *Gelfond Lab 501
 *April 14 2015
 *Lab 10
*/




#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cin;
using std::cout;
using std::vector;
using std::ostream_iterator;
using std::endl;
using std::remove;


int
user_number(const char *prompt)
{
  cout<<prompt;
  int user_number;
  cin>>user_number;
  return user_number;
  
}

int
selection()
{
  cout<<"WHAT WOULD YOU LIKE TO DO"<<endl;
  cout<<"1) Prepend"<<endl<<"2) Append"<<endl;
  cout<<"3) Delete an item"<<endl<<"4) Check for item"<<endl;
  cout<<"5) Count the number of items"<<endl<<"6) Print list"<<endl;
  cout<<"7) Sort list in ascending order"<<endl<<"8) Remove duplicates"<<endl;
  cout<<"9) Quit"<<endl;
  int user_input;
  cin>>user_input;
  return user_input;
}


int
main(int argc, const char *argv[])
{
  vector<int> xs;
  int user_input;

  while((user_input = selection()) != 9){ 
    if(user_input == 1){
      xs.insert(xs.begin(),user_number("What number would you like to append?: "));
    }else if(user_input == 2){
      xs.insert(xs.end(),user_number("What number would you like to prepend?: "));
    }else if(user_input == 3){
      xs.erase(find(xs.begin(),xs.end(),user_number("What number would you like to erase?: "))); 
    }else if(user_input == 4){
      if(find(xs.begin(),xs.end(),user_number("What number would you like to check for?: "))!=xs.end()){
        cout<<"The number exists in the list"<<endl;
      }else{
        cout<<"The number does not exist in the list"<<endl;
      }
    }else if(user_input == 5){
      cout<<"There are "<<xs.size()<<" numbers in the list"<<endl;
    }else if(user_input == 6){
      copy(xs.begin(),xs.end(),ostream_iterator<int>(cout," "));
      cout<<endl;
    }else if(user_input == 7){
      sort(xs.begin(),xs.end());
    }else if(user_input == 8){
      sort(xs.begin(),xs.end());
      xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }

  }
  
  cout<<endl;
  return 0;

}

