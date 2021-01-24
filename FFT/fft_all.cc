// Submission link : https://www.codechef.com/viewsolution/32525279

#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint unsigned
#define pii pair<int,int>
#define pll pair<ll,ll>
#define IT iterator
#define PB push_back
#define fi first
#define se second
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define CLR(a,v) memset(a,v,sizeof(a));
#define CPY(a,b) memcpy(a,b,sizeof(a));
#define debug puts("wzpakking")
#define y1 ysghysgsygsh
using namespace std;

const int mo=998244353;
const int FFTN=1<<18;
#define poly vector<int>
namespace FFT{
	int w[FFTN+5],W[FFTN+5],R[FFTN+5];
	int power(int x,int y){
		int s=1;
		for (;y;y/=2,x=1ll*x*x%mo)
			if (y&1) s=1ll*s*x%mo;
		return s;
	}
	void FFTinit(){
		W[0]=1;
		W[1]=power(3,(mo-1)/FFTN);
		For(i,2,FFTN) W[i]=1ll*W[i-1]*W[1]%mo;
	}
	int FFTinit(int n){
		int L=1;
		for (;L<=n;L<<=1);
		For(i,0,L-1) R[i]=(R[i>>1]>>1)|((i&1)?(L>>1):0);
		return L;
	}
	int A[FFTN+5],B[FFTN+5];
	ull p[FFTN+5];
	void DFT(int *a,int n){
		For(i,0,n-1) p[R[i]]=a[i];
		for (int d=1;d<n;d<<=1){
			int len=FFTN/(d<<1);
			for (int i=0,j=0;i<d;i++,j+=len) w[i]=W[j];
			for (int i=0;i<n;i+=(d<<1))	
				for (int j=0;j<d;j++){
					int y=p[i+j+d]*w[j]%mo;
					p[i+j+d]=p[i+j]+mo-y;
					p[i+j]+=y;
				}
			if (d==1<<15)
				For(i,0,n-1) p[i]%=mo;
		}
		For(i,0,n-1) a[i]=p[i]%mo;
	}
	void IDFT(int *a,int n){
		For(i,0,n-1) p[R[i]]=a[i];
		for (int d=1;d<n;d<<=1){
			int len=FFTN/(d<<1);
			for (int i=0,j=FFTN;i<d;i++,j-=len) w[i]=W[j];
			for (int i=0;i<n;i+=(d<<1))	
				for (int j=0;j<d;j++){
					int y=p[i+j+d]*w[j]%mo;
					p[i+j+d]=p[i+j]+mo-y;
					p[i+j]+=y;
				}
			if (d==1<<15)
				For(i,0,n-1) p[i]%=mo;
		}
		int val=power(n,mo-2);
		For(i,0,n-1) a[i]=p[i]*val%mo;
	}
	poly Norm(poly a){
		for (;a.size()&&a.back()==0;a.pop_back());
		return a;
	}
	poly Plus(const poly &a,const poly &b){
		int sza=a.size()-1,szb=b.size()-1;
		poly ans(max(sza,szb)+1);
		For(i,0,sza) ans[i]=a[i];
		For(i,0,szb) ans[i]=(ans[i]+b[i])%mo;
		return ans;
	}
	poly Minus(const poly &a,const poly &b){
		int sza=a.size()-1,szb=b.size()-1;
		poly ans(max(sza,szb)+1);
		For(i,0,sza) ans[i]=a[i];
		For(i,0,szb) ans[i]=(ans[i]+mo-b[i])%mo;
		return ans;
	}
	poly Mul(const poly &a,const poly &b){
		int sza=a.size()-1,szb=b.size()-1;
		poly ans(sza+szb+1);
		if (sza<=30||szb<=30){
			For(i,0,sza) For(j,0,szb)
				ans[i+j]=(ans[i+j]+1ll*a[i]*b[j])%mo;
			return ans; 
		}
		int L=FFTinit(sza+szb);
		For(i,0,L-1) A[i]=(i<=sza?a[i]:0);
		For(i,0,L-1) B[i]=(i<=szb?b[i]:0);
		DFT(A,L); DFT(B,L);
		For(i,0,L-1) A[i]=1ll*A[i]*B[i]%mo;
		IDFT(A,L);
		For(i,0,sza+szb) ans[i]=A[i];
		return ans; 
	}
	void Getinv(int *a,int *b,int n){
		if (n==1){
			//assert(a[0]!=0);
			b[0]=power(a[0],mo-2);
			return;
		}
		int nn=(n+1)/2;
		Getinv(a,b,nn);
		int L=FFTinit(2*n);
		For(i,0,L-1) A[i]=(i<n?a[i]:0);
		For(i,0,L-1) B[i]=(i<nn?b[i]:0);
		DFT(A,L); DFT(B,L);
		For(i,0,L-1) A[i]=1ll*B[i]*(2+mo-1ll*A[i]*B[i]%mo)%mo;
		IDFT(A,L);
		For(i,0,n-1) b[i]=A[i]; 
	}
	poly getinv(poly a,int n){
		int *b=new int[n];
		int *c=new int[n];
		int sz=a.size();
		For(i,0,n-1) b[i]=(i<sz?a[i]:0);
		For(i,0,n-1) c[i]=0;
		vector<int> ans(n);
		Getinv(b,c,n);
		For(i,0,n-1) ans[i]=c[i];
		delete[] b;
		delete[] c;
		return ans;
	}
	poly divide(poly a,poly b){
		int sza=a.size(),szb=b.size();
		if (sza<szb) return poly(0);
		poly b0=b,a0=a;
		reverse(b0.begin(),b0.end());
		reverse(a0.begin(),a0.end());
		a0.resize(sza-szb+1);
		b0=Mul(getinv(b0,sza-szb+1),a0);
		b0.resize(sza-szb+1);
		reverse(b0.begin(),b0.end());
		return b0;
	}
	poly modulo(poly a,poly b){
		poly ans=Minus(a,Mul(divide(a,b),b));
		ans.resize(b.size()-1);
		return ans;
	}
	int Cipolla(int x){
		//assert(power(x,(mo-1)/2)==1);
		int a=1;
		for (;;++a)
			if (power((1ll*a*a+mo-x)%mo,(mo-1)/2)==mo-1)
				break;
		//cout<<a<<' '<<x<<endl;
		int w=(1ll*a*a+mo-x)%mo,T=(mo+1)/2;
		pii v1(1,0),v2(a,1);
		for (;T;){
			if (T&1){
				int val1=(1ll*v1.fi*v2.fi+1ll*w*v1.se%mo*v2.se)%mo;
				int val2=(1ll*v1.fi*v2.se+1ll*v1.se*v2.fi)%mo;
				v1=pii(val1,val2);
			} 
			if (T/=2){
				int val1=(1ll*v2.fi*v2.fi+1ll*w*v2.se%mo*v2.se)%mo;
				int val2=(1ll*v2.fi*v2.se+1ll*v2.se*v2.fi)%mo;
				v2=pii(val1,val2);
			} 
		}
		//cout<<v1.fi<<' '<<v1.se<<endl;
		return v1.fi;
	}
	void Getsqrt(int *a,int *b,int n){
		if (n==1){
			//assert(a[0]!=0);
			b[0]=Cipolla(a[0]);
			if (b[0]>mo-b[0]) b[0]=mo-b[0];
			return;
		}
		int nn=(n+1)/2;
		Getsqrt(a,b,nn);
		int *c=new int[n];
		For(i,0,n-1) c[i]=0;
		Getinv(b,c,n);
		int L=FFTinit(2*n);
		For(i,0,L-1) A[i]=(i<n?a[i]:0);
		For(i,0,L-1) B[i]=(i<n?c[i]:0);
		DFT(A,L); DFT(B,L);
		For(i,0,L-1) A[i]=1ll*A[i]*B[i]%mo;
		IDFT(A,L);
		For(i,0,n-1) b[i]=1ll*(b[i]+A[i])*(mo+1)/2%mo;
		delete[] c;
	}
	poly getsqrt(poly a,int n){
		int *b=new int[n];
		int *c=new int[n];
		int sz=a.size();
		For(i,0,n-1) b[i]=(i<sz?a[i]:0);
		For(i,0,n-1) c[i]=0;
		vector<int> ans(n);
		Getsqrt(b,c,n);
		For(i,0,n-1) ans[i]=c[i];
		delete[] b;
		delete[] c;
		return ans;
	}
	
	poly Int(poly a){
		int sza=a.size()-1;
		poly ans(sza+2); ans[0]=0;
		For(i,1,sza+1) ans[i]=1ll*a[i-1]*power(i,mo-2)%mo;
		return ans;
	}
	poly Prime(poly a){
		int sza=a.size()-1;
		poly ans(sza);
		For(i,1,sza) ans[i-1]=1ll*a[i]*i%mo;
		return ans;
	}
	poly getLn(poly a,int n){
		assert(a[0]==1);
		if (a.size()>n) a.resize(n);
		poly res=Int(Mul(Prime(a),getinv(a,n)));
		res.resize(n);
		return res;
	}
	
	void Getexp(ull *a,ull *b,int l,int r){
		if (r-l+1<=64){
			For(i,l,r) b[i]%=mo;
			For(i,l,r){
				if (i==0) b[i]=1;
				else b[i]=b[i]%mo*power(i,mo-2)%mo;
				For(j,1,r-i) b[i+j]+=b[i]*a[j]; 
				if ((i&15)==15) For(j,i,r) b[j]%=mo;
			}
			return;
		}
		int len=(r-l+1)/16;
		ull *c[16],*d[16];
		int L=FFTinit(2*len);
		int *arr=new int[L];
		For(i,0,15){
			d[i]=new ull[L];
			For(j,0,L-1) d[i][j]=0;
		}
		For(i,0,14){
			c[i]=new ull[L];
			For(j,0,L-1) arr[j]=a[i*len+j];
			DFT(arr,L);
			For(j,0,L-1) c[i][j]=arr[j];
		}
		For(i,0,15){
			if (i!=0){
				For(j,0,L-1) arr[j]=d[i][j]%mo;
				IDFT(arr,L);
				For(j,0,len-1) b[l+i*len+j]+=arr[len+j];
			}
			Getexp(a,b,l+i*len,l+i*len+len-1);
			if (i!=15){
				L=FFTinit(2*len);
				For(j,0,L-1) arr[j]=(j<len?b[l+i*len+j]:0);
				DFT(arr,L);
				For(j,0,14-i) For(k,0,L-1)
					d[i+j+1][k]+=arr[k]*c[j][k];
			}
		}
		delete[] arr;
		For(i,0,14) delete[] c[i];
		For(i,0,15)	delete[] d[i];
	}
	poly getexp(poly a,int n){
		int m=1,sza=a.size();
		for (;m<=n;m<<=1);
		ull *b=new ull[m],*c=new ull[m];
		For(i,0,m-1) b[i]=(i<sza?1ll*i*a[i]%mo:0);
		For(i,0,m-1) c[i]=0;
		Getexp(b,c,0,m-1);
		vector<int> ans(n);
		For(i,0,n-1) ans[i]=c[i];
		delete[] b;
		delete[] c;
		return ans;
	}
	poly read(){
		int n;
		scanf("%d",&n);
		vector<int> ans(n);
		For(i,0,n-1) scanf("%d",&ans[i]);
		return ans; 
	}
	poly read(int n){
		vector<int> ans(n);
		For(i,0,n-1) scanf("%d",&ans[i]);
		return ans; 
	}
	void write(const poly &a){
		for (auto i:a) printf("%d ",i);
	}
	void writeln(const poly &a){
		for (auto i:a) printf("%d ",i);
		puts("");
	}
}
