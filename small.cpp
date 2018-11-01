#include <iostream>
#include <vector>
#include <LEDA/core/list.h>
#include <LEDA/geo/point.h>
#include <LEDA/geo/circle.h>
#include <time.h> 
#include <chrono>
using namespace leda;
using namespace std;

// int rand();
circle trivial(list<point> l){
  int n = l.length();
  std::vector<point> v;

  for(int i = 0; i < n; i++) v.push_back(l.pop());

  for(int i = 0; i < n-2; i++){
    for(int j = i+1; j < n-1; j++){
      for(int k = j+1; k < n; k++){
        if(orientation(v[i],v[j],v[k])==0){
          break;
        }
        circle CC = circle(v[i],v[j],v[k]);
        int flag = 1;
        
        for(int m = 0; m < n; m++){
          if(CC.outside(v[m])){ 
            flag = 0;
            break;
          }
        }
        
        if(flag) return CC;
      }
    }
  }
  circle C;
  return C;
}

circle f3(list<point> l, point p, point q){
  int n = l.length();
  int i=0;
  point r;
  point cent = midpoint(p,q);
  circle C = circle(cent,p);
  for(i=0;i<n;i++){
    r=l.pop();
    if(!C.inside(r) && !C.contains(r)){
      C = circle(p,q,r);
    }
  }
  return C;
}

circle f2(list<point> l, point p){
  int n = l.length();
  int i=0;
  point q;
  circle C;
  list<point> l2;
  for(i=0;i<n;i++){
    q=l.pop();
    if(i==0){
      point cent = midpoint(p,q);
      C=circle(cent,p);
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
    }
    if(!C.inside(p) ){
      C = circle(p);
      C = f2(l2,p);
    }
    l2.push(p);
  }
  return C;
}


int main(){
  srand (time(NULL));
  list<point> l; 
  int npoints = 100;
  for(int i=0; i< npoints; i++){
    int a = rand()%20;
    int b = rand()%20;
    point p(a,b);
    l.push(p);
  }
  cout<<l<<endl;
  //l.permute();
  // cout<<l<<endl;
  cout << "There are "<< npoints << " randomly generated points.\n";
  auto t1 = std::chrono::high_resolution_clock::now();
  circle C = f1(l);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "Randomized Algo took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
            << " milliseconds\n";
  
  cout << " The smallest circle is  : \n";
  cout<<C.center()<<" "<<C.radius()<<endl;


  auto t11 = std::chrono::high_resolution_clock::now();
  circle AC = trivial(l);
  auto t21 = std::chrono::high_resolution_clock::now();
  std::cout << "Trivial O(n^4) took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t21-t11).count()
            << " milliseconds\n";
  
  cout << " The actual smallest circle is  : \n";
  cout<<AC.center()<<" "<<AC.radius()<<endl;
  
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
