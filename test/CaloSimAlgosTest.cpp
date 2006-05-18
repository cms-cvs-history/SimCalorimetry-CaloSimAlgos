#include "SimCalorimetry/CaloSimAlgos/interface/CaloCorrelatedNoisifier.h"
#include "CalibFormats/CaloObjects/interface/CaloSamples.h"

int main()
{

  CaloCorrelatedNoisifier noisifier(10);
 
  DetId detId;
  CaloSamples samples(detId, 10);

  noisifier.setDiagonal(1);
  noisifier.setOffDiagonal(1, -0.2);

  noisifier.noisify(samples);
  std::cout << samples << std::endl;
}

