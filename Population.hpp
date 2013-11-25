/* 
 * File:   Population.hpp
 * Author: jurek
 *
 * Created on November 24, 2013, 5:39 PM
 */

#ifndef POPULATION_HPP
#define	POPULATION_HPP
#include <vector>
#include <random>
#include "Chromosome.h"
template <typename T>
void swap(T*,T*);

template <typename T>
class Population {
private:
    std::vector< Chromosome<T> > population;
    double (*fitness)(const Chromosome<T>&);
public:
    Population<T>();
    Population<T>(const std::vector< Chromosome<T> >&);
    void addChromosome(const Chromosome<T>);
    void addChromosomeSet(const std::vector< Chromosome<T> >&);
    void setFitnessFunction(double (*fit)(const Chromosome<T>&));
    void Sort();
    void Evolve();
    
    std::vector< Chromosome<T> > getChromosomes() const;
};

template <typename T>
class Pair{
private:
    Chromosome<T> chr;
    double fit;
    
public:
    Pair<T>(const Chromosome<T>&, double);
    bool comp(const Pair<T>&) const;
    double getFitness() const;
    Chromosome<T> getChromosome() const;
};
#endif	/* POPULATION_HPP */

template <typename T>
Population<T>::Population(){}

template <typename T>
Population<T>::Population(const std::vector<Chromosome<T> >& pop){
    this->population = pop;
}

template <typename T>
void Population<T>::addChromosome(const Chromosome<T> ch){
    this->population.push_back(ch);
}

template <typename T>
void Population<T>::addChromosomeSet(const std::vector<Chromosome<T> >& chs){
    for(int i=0;i<chs.size();i++){
        this->population.push_back(chs.at(i));
    }
}

template <typename T>
void Population<T>::setFitnessFunction(double(*fit)(const Chromosome<T>&)){
    this->fitness = fit;
}

template <typename T>
void Population<T>::Sort(){
    std::vector< Pair<T> > pairs;
    for(int i=0;i<this->population.size();i++){
        Pair<T> pair(this->population.at(i), this->fitness(this->population.at(i)));
        pairs.push_back(pair);
    }
    
    //Bubble sorting
    for(int i=pairs.size()-1;i>0;i--){
        for(int j=0;j<i;j++){
            double v1 = pairs.at(j).getFitness();
            double v2 = pairs.at(j+1).getFitness();
            if(v2 > v1){
                swap< Pair<T> >(&pairs.at(j), &pairs.at(j+1)); 
            }
        }
    }
    
    this->population.clear();
    for(int i=0;i<pairs.size();i++){
        this->population.push_back(pairs.at(i).getChromosome());
    }
}

template <typename T>
void Population<T>::Evolve(){
    this->Sort();
    std::vector< Chromosome<T> > children;
    for(int i=0;i<this->population.size();i+=2){
        Chromosome<T>** childrenArr = this->population.at(i).CrossOver(this->population.at(i+1), Chromosome<T>::ONE_POINT);
        for(int i=0;i<2;i++){
            children.push_back(*(childrenArr[i]));
        }
        delete[] childrenArr;
    }
    for(int i=0;i<children.size();i++){
        this->population.push_back(children.at(i));
    }
}

template <typename T>
std::vector< Chromosome<T> > Population<T>::getChromosomes() const{
    return this->population;
}


//PAIR DEFINITION

template <typename T>
Pair<T>::Pair(const Chromosome<T>& ch, double f){
    this->chr = ch;
    this->fit = f;
}

template <typename T>
bool Pair<T>::comp(const Pair<T>& pair) const{
    if(this->getFitness() > pair.getFitness()){
        return true;
    }
}

template <typename T>
double Pair<T>::getFitness() const{
    return this->fit;
}

template <typename T>
Chromosome<T> Pair<T>::getChromosome() const{
    return this->chr;
}


template <typename T>
void swap(T* a, T* b){
    T temp = *a;
    *a = *b;
    *b = temp;
}