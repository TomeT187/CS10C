#include "Jug.h"
#include <iomanip>
#include <iostream>


Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
 : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA)
{    
}

int Jug::solve(string &solution){
    //check if inputs are valid
    createGraph();
    Dijkstra();
    State curr = states[state_number(0,N, Ca,Cb)];
    std::cout << curr.a << " " << curr.b << std::endl;
    while(curr.previous != infinity){
        std::cout << curr.a << " " << curr.b << std::endl;
        curr = states[curr.previous];
    }
    //end node is at states[state_number(0,N)]
    //trace back from end node to states[state_number(0,0)]
    //
    return -1;
}

void Jug::createGraph(){
    for(unsigned a=0;a<=Ca;++a) {
    for(unsigned b=0;b<=Cb;++b) {
      // Compute action fill A.  A will have Ca gallons. B unchanged
      // Compute action fill B.  A unchanged, B will have Cb gallons
      unsigned fillA = state_number(Ca,b, Ca,Cb);
      unsigned fillB = state_number(a,Cb, Ca,Cb);

      // For the empties... just set the appropriate amount to zero
      unsigned emptyA = state_number(0,b, Ca,Cb);
      unsigned emptyB = state_number(a,0, Ca,Cb);

      // For the transfers, we can only pour in as much as we have
      // in the "from" jug OR as much room as we have in the "to" jug
      unsigned transferFromA = std::min(a, Cb-b);
      unsigned AtoB = state_number(a-transferFromA,b+transferFromA, Ca,Cb);
      unsigned transferFromB = std::min(b, Ca-a);
      unsigned BtoA = state_number(a+transferFromB,b-transferFromB, Ca,Cb);

      // Note: We can use emplace_back here (look it up!)
      states.push_back(State(a,b, fillA,fillB, emptyA,emptyB, AtoB,BtoA));
    }
  }
}

void Jug::Dijkstra(){
    states[0].distance = 0;
    states[0].previous = infinity;

    while(!allVisisted(states)){
        unsigned distance = infinity;
        unsigned current = infinity;
        for(unsigned i=0;i<states.size();++i) {
            if (states[i].distance < distance &&  !states[i].visited) {
            distance = states[i].distance;
            current = i;
            }
        }
        if (distance == infinity) {
            // Appropriate here to quit
            return;
        }

        // To start with, the start node should be selected since it
        // has distance 0
        states[current].visited = true;

        // We need to look at each of the six actions... And see if it
        // takes us a shorter distance than we've seen before.  I demonstrate
        // with the "fillA" action, but you have to do all six paths out
        // of this node.  EVEN THE ONES THAT LEAD RIGHT BACK TO IT!!
        unsigned fillA = states[current].fillA;
        unsigned fillB = states[current].fillB;
        unsigned emptyA = states[current].emptyA;
        unsigned emptyB = states[current].emptyB;
        unsigned AtoB = states[current].AtoB;
        unsigned BtoA = states[current].BtoA;

        // The distance there is our current distance PLUS the cost
        // of doing a fillA
        unsigned fillA_distance = distance + cfA;
        unsigned fillB_distance = distance + cfB;
        unsigned emptyA_distance = distance + ceA;
        unsigned emptyB_distance = distance + ceB;
        unsigned AtoB_distance = distance + cpAB;
        unsigned BtoA_distance = distance + cpBA; 

        // We compare the distance we have saved there with the distance
        // that we get with this visit.  If it is shorter, we update
        // the distance AND the previous
        if (fillA_distance < states[fillA].distance) {
            
            states[fillA].distance = fillA_distance;
            states[fillA].previous = current;
        }
        if (fillB_distance < states[fillB].distance) {
            
            states[fillB].distance = fillB_distance;
            states[fillB].previous = current;
        }
        if (emptyA_distance < states[emptyA].distance) {
            
            states[emptyA].distance = emptyA_distance;
            states[emptyA].previous = current;
        }
        if (emptyB_distance < states[emptyB].distance) {
            
            states[emptyB].distance = emptyB_distance;
            states[emptyB].previous = current;
        }
        if (AtoB_distance < states[AtoB].distance) {
            
            states[AtoB].distance = AtoB_distance;
            states[AtoB].previous = current;
        }
        if (BtoA_distance < states[BtoA].distance) {
            
            states[BtoA].distance = BtoA_distance;
            states[BtoA].previous = current;
        }
    }
}

bool Jug::allVisisted(const vector<State>& states){
    for(unsigned int i = 0; i < states.size(); i++){
        if(states[i].visited == false){
            return false;
        }
    }
    return true;
}

unsigned Jug::state_number(unsigned a, unsigned b, unsigned Ca, unsigned Cb) {
  // Simple error handling.  In the program you'll never be out of
  // bounds
  if (a > Ca || b > Cb) {
    throw std::runtime_error("domain error");
  }

  return a*(Cb+1)+b;
}