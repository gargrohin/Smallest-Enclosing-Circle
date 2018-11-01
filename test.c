#include <LEDA/core/list.h>
#include <LEDA/geo/point.h>
#include <LEDA/geo/circle.h>
#include <cstdlib>
int rand();

using namespace leda;
using namespace std;

circle f3(list<point> l, point p, point q){
  int n = l.length();
  int i=0;
  point r;
  point cent = midpoint(p,q);
  circle C = circle(cent,p);
  for(i=0;i<n;i++){
    r=l.pop();
    if(!C.inside(r)){
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
    if(!C.inside(p)){
      C = circle(p);
      C = f2(l2,p);
    }
    l2.push(p);
  }
  return C;
}


int main()
{
  list<point> l;
  for(int i=0; i< 20; i++){
    int a = rand()%20;
    int b = rand()%20;
    point p(a,b);
    l.push(p);
  }
  l.permute();
  cout<<l<<endl;
  circle C = f1(l);
  cout<<C.center()<<" "<<C.radius()<<endl;
  /*C=circle(l.pop(),l.pop(),l.pop());
  point a = l.pop();
  if(C.inside(a)){
      cout<<C<<endl;
  }*/
  return 0;
}