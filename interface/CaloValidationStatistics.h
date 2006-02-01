#ifndef CaloSimAlgos_CaloValidationStatistics_h
#define CaloSimAlgos_CaloValidationStatistics_h

/** For validation purposes.  This program
    calculates mean and RMS of a distribution

  \Author Rick Wilkinson
*/
#include <string>
#include <iosfwd>

class CaloValidationStatistics
{
public:
  CaloValidationStatistics(std::string name, float expectedMean, float expectedRMS);

  void addEntry(float value);

  std::string name() const {return name_;}

  float mean() const;

  float RMS() const;

  float expectedMean() const {return expectedMean_;}

  float expectedRMS() const {return expectedRMS_;}

  int nEntries() const {return n_;}

private:

  std::string name_;
  float expectedMean_;
  float expectedRMS_;
  float sum_;
  float sumOfSquares_;
  int n_;
};

std::ostream & operator<<(std::ostream & os, const CaloValidationStatistics & stat);

#endif

