#pragma once
#include <string>
#include <limits>
#include <vector>

using std::string;
using std::vector;

const unsigned infinity = std::numeric_limits<unsigned>::max();

struct State {
  int a; // Amount in jug A
  int b; // Amount in jug B

  // Where to go on each of the six actions
  unsigned fillA;
  unsigned fillB;
  unsigned emptyA;
  unsigned emptyB;
  unsigned AtoB;
  unsigned BtoA;

  // These fields are useful when we do Dijkstra's method
  unsigned previous;
  unsigned distance;
  bool visited;

State(unsigned a,	unsigned b,	unsigned fillA,	unsigned fillB, unsigned emptyA, unsigned emptyB, unsigned AtoB, unsigned BtoA)
    : a(a), b(b), fillA(fillA), fillB(fillB), emptyA(emptyA), emptyB(emptyB), AtoB(AtoB), BtoA(BtoA), previous(infinity),
    distance(infinity), visited(false)
    {
    }
};

class Jug{
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        //~Jug();
        int solve(string &solution);

    private:
        unsigned Ca;
        unsigned Cb;
        unsigned N;
        unsigned cfA;
        unsigned cfB;
        unsigned ceA;
        unsigned ceB;
        unsigned cpAB;
        unsigned cpBA;
        vector<State> states;

        unsigned state_number(unsigned a, unsigned b, unsigned Ca, unsigned Cb);
        void createGraph();
        void Dijkstra();
        bool allVisisted(const vector<State>& states);
};