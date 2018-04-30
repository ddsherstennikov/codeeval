#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>

#include <string>
#include <vector>

#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char**argv) 
{
  int F, B, N, f, b;
  string line;  
  ifstream fs;
  
  fs.open( argv[1], ios_base::in );
  if (!fs.is_open())
  {
    cout << "file not found";
    return -1;
  }
  
  while ( getline( fs, line ) ) 
  {
    istringstream iss(line);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));

    f = F = atoi(tokens[0].c_str());
    b = B = atoi(tokens[1].c_str());
    N = atoi(tokens[2].c_str());

    for( int i=1; i<=N; ++i ) 
    {
      if ( i==f && i==b ) { cout << "FB"; f+=F; b+=B; }
      else if ( i==f ) { cout << "F"; f+=F; }
      else if ( i==b ) { cout << "B"; b+=B; }
      else cout << i;

      if ( i<N ) cout << " ";
    }
    
    cout << endl;
  }
  
  return 0;
}