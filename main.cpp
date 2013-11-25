/* 
 * File:   main.cpp
 * Author: jurek
 *
 * Created on November 23, 2013, 6:52 PM
 */

#include <vector>
#include <iostream>
#include "Gene.hpp"
#include "Chromosome.h"
#include "Population.hpp"
using namespace std;
/*
 * 
 */

double fit(const Chromosome<int>&);
int main(int argc, char** argv) {
    vector< Gene<int> > geny1;
    vector< Gene<int> > geny2;
    
    geny1.push_back(7); geny1.push_back(5);
    geny2.push_back(2); geny2.push_back(2);
    
    Chromosome<int> ch1(geny1);
    Chromosome<int> ch2(geny2);
    Population<int> pop;
    pop.addChromosome(ch1);
    pop.addChromosome(ch2);
    pop.setFitnessFunction(fit);
    
    pop.Evolve();
    cout << pop.getChromosomes().size();
    
    return 0;
}


double fit(const Chromosome<int>& ch){
    double points = 0;
    int size = ch.genesSet().size();
    for(int i=0;i<ch.genesSet().size();i++){
        points += (double) ch.geneAt(i).getValue();
    }
    cout << "Punkty: " << points << endl;
    return points;
}

