#include <iostream>
#include <vector>
#include <LEDA/core/list.h>
#include <LEDA/geo/point.h>
#include <LEDA/geo/circle.h>
#include <time.h> 
#include <chrono>
#define Debug(x) cout << "> " << #x << " : " << x << "\n";
#define For(i,a,b) for(int i=(a);i<(b);i++)
using namespace leda;
using namespace std;

// int rand();
circle trivial(list<point> l){
  int n = l.length();
  cout<<n<<endl;
  std::vector<point> v;
  // Debug(n)
  for(int i = 0; i < n; i++) v.push_back(l.pop());
  circle smallestC;double rmin = 1000000.0;
  for(int i = 0; i < n-2; i++){
    for(int j = i+1; j < n-1; j++){
      for(int k = j+1; k < n; k++){
        if(orientation(v[i],v[j],v[k])==0){
          continue;
        }
        circle CC = circle(v[i],v[j],v[k]);
        int flag = 1;
        // cout << i << " " << j << " " << k<<"\n";
        // cout << CC<<"\n";
        for(int m = 0; m < n; m++){
          if(CC.outside(v[m])){ 
            flag = 0;
            break;
          }
        }
        if(flag){
          if(CC.radius() < rmin){
            rmin = CC.radius();
            smallestC = CC;
          }
        }
      }
    }
  }
  for(int i = 0; i < n-2; i++){
    for(int j = i+1; j < n-1; j++){
    	point cent = midpoint(v[i],v[j]);
        circle CC = circle(cent,v[i]);
        int flag = 1;
        // cout << i << " " << j << " " << k<<"\n";
        // cout << CC<<"\n";
        for(int m = 0; m < n; m++){
          if(CC.outside(v[m])){ 
            flag = 0;
            break;
          }
        }
        if(flag){
          if(CC.radius() < rmin){
            rmin = CC.radius();
            smallestC = CC;
          }
        }
    }
  }
  return smallestC;
}

circle f3(list<point> l, point p, point q){
  int n = l.length();
   //Debug(n)
   //Debug(p)
   //Debug(q)
  int i=0;
  point r;
  point cent = midpoint(p,q);
  circle C = circle(cent,p);
  for(i=0;i<n;i++){
    r=l.pop();
    if(orientation(p,q,r)==0) continue;
    if(!C.inside(r)){
    	//cout<<r<<endl;
      C = circle(p,q,r);
    }
  }
  return C;
}

circle f2(list<point> l, point p){
  int n = l.length();
  // Debug(n)
  // Debug(p)
  int i=0;
  point q;
  circle C;
  list<point> l2;
  for(i=0;i<n;i++){
    q=l.pop();
    if(i==0){
      point cent = midpoint(p,q);
      C=circle(cent,p);//circle with center cent passing thru p
      l2.push(q);
      continue;
    }
    if(!C.inside(q)){
      C = f3(l2,p,q);
    }
    l2.push(q);
  }
  return C;
}

circle f1(list<point> l){
  int n = l.length();
  int i=0;
  list<point> l2;
  circle C;
  for(i=0;i<n;i++){
    point p = l.pop();
    if(i==0){
      C = circle(p);
      l2.push(p);
      continue;
    }
    if(!C.inside(p) ){
      C = circle(p);
      C = f2(l2,p);
    }
    l2.push(p);
  }
  cout << C<<" is randm circle\n";
  return C;
}


int main(){
  srand (time(NULL));
  list<point> l; 
  int npoints = 100;
  for(int i=0; i< npoints; i++){
    int a = rand();
    int b = rand();
    point p(a,b);
    l.push(p);
  }
  l.permute();
  //cout<<l<<endl;
  cout << "There are "<< npoints << " randomly generated points.\n\n";
  auto t1 = std::chrono::high_resolution_clock::now();
  circle C = f1(l);
  auto t2 = std::chrono::high_resolution_clock::now();
  
  
  cout << " The random smallest circle is  : \n";
  cout<<C.center()<<" "<<C.radius()<<endl;


  //auto t11 = std::chrono::high_resolution_clock::now();
  //circle AC = trivial(l);
  //auto t21 = std::chrono::high_resolution_clock::now();
  
  
 // cout << "\n The actual smallest circle is  : \n";
 // cout<<AC.center()<<" "<<AC.radius()<<endl;
 // cout << "It passes thru : "<< AC<<"\n\n";

  std::cout << "Randomized Algo took "
            << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()
            << " microseconds\n";

 /* std::cout << "Trivial O(n^4) took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t21-t11).count()
            << " milliseconds\n";
  // // point p1,p2,p3;
  // point p1(1,2),p2(3,7),p3(6,13);
  // circle CC = circle(p1,p2,p3);
  // cout << CC.center() << " is center and radius is " << CC.radius() << "\n";
  // point org(0,0);

  // cout << CC.inside(org);
  // cout << CC.outside(org);
  // cout << CC.contains(p1);
  /*C=circle(l.pop(),l.pop(),l.pop());
  point a = l.pop();
  if(C.inside(a)){
      cout<<C<<endl;
  }*/
  return 0;
}
