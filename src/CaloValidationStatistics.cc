#include "SimCalorimetry/CaloSimAlgos/interface/CaloValidationStatistics.h"
#include <cmath>
#include <iostream>

CaloValidationStatistics::CaloValidationStatistics(std::string name, float expectedMean, float expectedRMS) 
:  name_(name),
   expectedMean_(expectedMean),
   expectedRMS_(expectedRMS),
   sum_(0.),
   sumOfSquares_(0.),
   weightedSum_(0.),
   sumOfWeights_(0.),
   n_(0)
{
}


void CaloValidationStatistics::addEntry(float value, float weight) {
  sum_ += value;
  sumOfSquares_ += (value*value);
  weightedSum_ += value*weight;
  sumOfWeights_ += weight;
  ++n_;
}


float CaloValidationStatistics::mean() const {
  return sum_/n_;
}


float CaloValidationStatistics::RMS() const {
  float numerator = n_ * sumOfSquares_ - sum_*sum_;
  int denominator = n_ * (n_-1);
  return std::sqrt(numerator/denominator);
}

 
float CaloValidationStatistics::weightedMean() const  {
  return weightedSum_ / sumOfWeights_;
}


std::ostream& operator<<(std::ostream & os,const CaloValidationStatistics & stat) {
   
  os << "OVAL " << stat.name() 
     << " Mean: " << stat.mean() 
     << " (expect " << stat.expectedMean()
		 << ")  RMS: " << stat.RMS()
     << " (expect " << stat.expectedRMS() << ")"
     << " for " << stat.nEntries() << " entries ";
  return os;
}


