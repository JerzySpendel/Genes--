/* 
 * File:   Chromosome.h
 * Author: jurek
 *
 * Created on November 24, 2013, 3:54 PM
 */

#ifndef CHROMOSOME_H
#define	CHROMOSOME_H
#include <vector>
#include <iostream>
#include <random>
#include "Gene.hpp"

template <typename T>

class Chromosome{
private:
    std::vector< Gene<T> > genes;
public:
    enum flags {ONE_POINT, TWO_POINT};
    Chromosome<T>();
    Chromosome<T>(const std::vector< Gene<T> >&);
    void setGenes(const std::vector< Gene<T> >&);
    Chromosome<T>** CrossOverOnePoint(const Chromosome<T>&, int);
    Chromosome<T>** CrossOverTwoPoint(const Chromosome<T>&, int*);
    Chromosome<T>** CrossOver(const Chromosome<T>&, int);
    
    
    const std::vector< Gene<T> >& genesSet() const;
    Gene<T> geneAt(int) const;
};

template <typename T>
Chromosome<T>::Chromosome(){
    
}

template <typename T>
Chromosome<T>::Chromosome(const std::vector<Gene<T> >& genes){
    this->genes = genes;
}

template <typename T>
void Chromosome<T>::setGenes(const std::vector<Gene<T> >& genes){
    this->genes = genes;
}

template <typename T>
Chromosome<T>** Chromosome<T>::CrossOverOnePoint(const Chromosome<T>& ch, int point){
    std::vector< Gene<T> > genesSet1;
    std::vector< Gene<T> > genesSet2;
    
    for(int i=0;i<point;i++){
        genesSet1.push_back(this->geneAt(i));
    }
    
    for(int i=point;i<this->genes.size();i++){
        genesSet1.push_back(ch.geneAt(i));
    }
    
    for(int i=0;i<point;i++){
        genesSet2.push_back(ch.geneAt(i));
    }
    
    for(int i=point;i<this->genes.size();i++){
        genesSet2.push_back(this->genes.at(i));
    }
    
    Chromosome<T>* ch1 = new Chromosome<T>(genesSet1);
    Chromosome<T>* ch2 = new Chromosome<T>(genesSet2);
    
    Chromosome<T>** chromosomes = new Chromosome<T>*[2]{ch1, ch2};
    return chromosomes;
}

template <typename T>
Chromosome<T>** Chromosome<T>::CrossOverTwoPoint(const Chromosome<T>& ch, int* points){
    std::vector< Gene<T> > genesSet1;
    std::vector< Gene<T> > genesSet2;
    
    int point_one = points[0];
    int point_two = points[1];
    
    for(int i=0;i<point_one;i++){
        genesSet1.push_back(this->geneAt(i));
        genesSet2.push_back(ch.geneAt(i));
    }
    for(int i=point_one;i<point_two;i++){
        genesSet1.push_back(ch.geneAt(i));
        genesSet2.push_back(this->geneAt(i));
    }
    for(int i=point_two;i<ch.genesSet().size();i++){
        genesSet1.push_back(this->geneAt(i));
        genesSet2.push_back(ch.geneAt(i));
    }
    Chromosome<T>* ch1 = new Chromosome<T>(genesSet1);
    Chromosome<T>* ch2 = new Chromosome<T>(genesSet2);
    Chromosome<T>** chs = new Chromosome<T>*[2]{ch1,ch2};
    
    delete[] points;
    return chs;
    
}

template <typename T>
Chromosome<T>** Chromosome<T>::CrossOver(const Chromosome<T>& ch, int flag){
    srand(time(NULL));
    int size = this->genesSet().size();
    
    if(flag == Chromosome::ONE_POINT){
        int point_one = (rand() % size) + 1;
        while(true){
            point_one = (rand() % size) + 1;
            if(point_one > 0 && point_one < size){
                break;
            }
        }
        
        return this->CrossOverOnePoint(ch, point_one);
    }
    
    if(flag == Chromosome::TWO_POINT){
        int point_one = (rand() % size) + 1;
        int point_two = (rand() % size) + 1;
        while(true){
            point_one = (rand() % size) + 1;
            if(point_one > 0 && point_one < size-2){
                break;
            }
        }
        while(true){
            point_two = (rand() % size) + 1;
            if(point_two > point_one+1){
                break;
            }
        }
        
        return this->CrossOverTwoPoint(ch, new int[2]{point_one, point_two});
    }
    
}
template <typename T>
const std::vector< Gene<T> >& Chromosome<T>::genesSet() const{
    return this->genes;
}

template <typename T>
Gene<T> Chromosome<T>::geneAt(int n) const{
    return this->genes.at(n);
}
#endif	/* CHROMOSOME_H */

