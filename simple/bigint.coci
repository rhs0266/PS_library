//  COCI 2008/2009 > Contest #2 5번, https://www.acmicpc.net/problem/2963

struct bigint {
   vector<int> digits;
   
   bigint( int x ) {
      digits.push_back( x );
   }
   
   void output() {
      int n = digits.size();
      printf( "%d", digits[--n] );
      while( n > 0 ) printf( "%09d", digits[--n] );
      printf( "\n" );
   }

   void operator += (const bigint &b ) {
      int carry = 0;
      for( int i = 0; i < digits.size() || i < b.digits.size() || carry; ++i ) {
         int x = carry;
         if( i < digits.size() ) x += digits[i];
         if( i < b.digits.size() ) x += b.digits[i];
         carry = x >= 1000000000;
         if( carry ) x -= 1000000000;
         
         if( i < digits.size() ) digits[i] = x;
         else digits.push_back( x );
      }
   }
};
