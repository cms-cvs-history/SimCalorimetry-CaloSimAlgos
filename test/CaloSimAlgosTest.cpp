#include "SimCalorimetry/CaloSimAlgos/interface/CaloCorrelatedNoisifier.h"
#include "CalibFormats/CaloObjects/interface/CaloSamples.h"

int main()
{

  CaloCorrelatedNoisifier noisifier(10);
 
  DetId detId;

  noisifier.setDiagonal(1);
  noisifier.setOffDiagonal(1, -0.2);
  noisifier.setOffDiagonal(2, -0.1);

  std::cout <<  noisifier.matrix() << std::endl;

  CaloSamples samples(detId, 10);
  noisifier.noisify(samples);
  std::cout << samples << std::endl;

  for (int i=0; i<400000; i++) {
    noisifier.noisify(samples);
  }
  std::cout << samples << std::endl;

}

