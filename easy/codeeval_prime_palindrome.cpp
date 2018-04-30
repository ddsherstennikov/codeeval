/* 
 * File:   main.cpp
 * Author: sdd
 *
 * Created on 10 Январь 2014 г., 16:12
 */

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Write a program to determine the biggest prime palindrome under 1000
int main(int argc, char** argv) 
{
  // 1 is for prime, we`ll be zeroing composits out; range is [0;999]
  vector<int> mx( 1000, 1 );
  
  for( int d=2; d<32; d++ )
    for ( int i=d; i<=999; i+=d )
      mx[i] = 0;
  
  for ( int i = 999; i > 2; --i )
    if ( mx[i] != 0 && (i / 100) == i % 10  )
    {
      cout << i;
      return 0;
    }
  
  return 1;
}

