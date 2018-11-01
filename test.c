#include <LEDA/core/list.h>
#include <LEDA/geo/point.h>
#include <LEDA/geo/circle.h>
#include <vector>

using namespace leda;
using namespace std;

circle f1(){
  int n = l.length();
  int i=0;
  list<point> l2;
  for(i=0;i<n;i++){
    point p = l.pop();
    if(!(C.inside(p)||C.contains(p))){
      C = circle(p);
      C = f2(l2,p);
    }
    l2.push(p);
  }
  return C;
}

circle f2(){
  int n = l.length();
  int i=0;
  list<point> l2;
  for(i=0;i<n;i++){
    q=l.pop();
    if(i==0){
      point cent = midpoint(p,q);
      C=circle(cent,p);
    }
    if(!(C.inside(q)||C.contains(q))){
      C = f3(l2,p,q);
    }
    l2.push(q);
  }
  return C;
}

circle f3(){
  int n = l.length();
  int i=0;
  point cent = midpoint(p,q);
  C = circle(cent,p);
  for(i=0;i<n;i++){
    r=l.pop();
    if(!(C.inside(r)||C.contains(r))){
      C = circle(p,q,r);
    }
  }
  return C;
}

int main()
{
  point a(2,4);
  point b(3,5);
  point c(1,6);
  circle C(a,b,c);
  if(C.inside(a)|| C.contains(a)){
    std:: cout << 1<<std::endl;
  }
  list<point> l;
  l.push(a);
  l.push(b);
  l.push(c);
  std::cout<<l<<" + "<<l.pop()<<" + " << l;
  C= circle(a);
  cout<<C.center();
  return 0;
}