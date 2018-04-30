#include <cstdlib>
#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>

using namespace std;

int main() 
{
  int n_thousand = 0; 
  int sum = 0;
  vector<int> primes;  
  typedef vector<int>::iterator vi;
  vector<int> mx( 1000, 1 ); // 1 is for prime, range is [0;999]
  bool fin = false;  
  
  while ( !fin )
  {
    int floor = n_thousand * 1000;
    int ceiling =  ( n_thousand + 1 ) * 1000 - 1;
    
    // (1) sieve    
    if ( n_thousand == 0 )
    {
      mx[0] = mx[1] = 0;
      
      for( int d=2; d<sqrt(ceiling); d++ )
        for ( int i=d*d; i<=ceiling; i+=d )
          mx[i] = 0;
    }
    else
      for ( vi pp = primes.begin(); pp != primes.end(); ++pp )
      {
        int prime = *pp;
        int sqr = prime * prime;
                
        if ( sqr > ceiling )
          break;
        
        int start = ( (floor-1) / prime + 1 ) * prime;
        
        for ( int i = max( sqr, start ) % 1000; i <= 999; i += prime )
          mx[i] = 0;
      }

    // (2) aggregate
    for ( int i = 0; i <= 999; ++i )
      if ( mx[i] != 0 ) // is prime
      {
        int newprime = n_thousand*1000 + i;
        primes.push_back( newprime );
        sum += newprime;
        
        // fin condition
        if ( primes.size() == 1000 )
        {
          fin = true;
          break;
        }
      }
      
    ++n_thousand;
    mx.assign( 1000, 1 );
  }
  
  cout << sum;
  
  return 0;
}

