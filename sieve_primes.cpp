
const int N = 1e6+10;   //Can compute upto N = 1e7
bool prime[N+3];
vector<int> primes;
void sieve(){
 
  memset(prime , true , sizeof prime );
 
  prime[0] = false , prime[1] = false;
  prime[2] = true;
 
  for(int x=2;x*x<=N;x++){
    if(prime[x] == true){
      for(int i=x*x;i<=N;i+=x)
        prime[i] = false;
    }
  }
 
  //for(int x=0;x<N;x++)
  //  if(prime[x])
  //      primes.pb(x);
 
} 
