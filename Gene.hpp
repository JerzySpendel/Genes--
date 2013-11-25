/* 
 * File:   Gene.hpp
 * Author: jurek
 *
 * Created on November 24, 2013, 12:02 PM
 */

#ifndef GENE_HPP
#define	GENE_HPP

template <typename T>
class Gene{
private:
    T value;
public:
    Gene();
    Gene(const T&);
    Gene(const Gene<T>&);
    virtual void encode();
    virtual void decode();
    virtual T getValue() const;
    virtual void setValue(T);
};
template <typename T>
Gene<T>::Gene(){}

template <typename T>
Gene<T>::Gene(const T& value){
    this->value = value;
}

template <typename T>
Gene<T>::Gene(const Gene<T>& g){
    this->value = g.getValue();
}

template <typename T>
T Gene<T>::getValue() const{
    return this->value;
}

template <typename T>
void Gene<T>::setValue(T val){
    this->value = val;
}

template <typename T>
void Gene<T>::encode(){}

template <typename T>
void Gene<T>::decode() {}
#endif	/* GENE_HPP */

