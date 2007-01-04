#include "SimCalorimetry/CaloSimAlgos/interface/CaloCorrelatedNoisifier.h"
#include "CalibFormats/CaloObjects/interface/CaloSamples.h"
#include "CLHEP/Matrix/Vector.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Matrix.h"

int main()
{

  CaloCorrelatedNoisifier noisifier1(10);
 
  DetId detId;

  noisifier1.setDiagonal(1);
  noisifier1.setOffDiagonal(1, -0.2);
  noisifier1.setOffDiagonal(2, -0.1);

  std::cout <<  "Test of input methods: \n" << noisifier1.covmatrix() << std::endl;

  HepSymMatrix input (10);
  for (int k = 0; k < 10; k++) {
    for (int kk = k; kk < 10; kk++) {
      input[k][kk] = 
	kk == k ? 1 
	: kk == k+1 ? -0.2 
	: kk == k+2 ? -0.1 
	: 0.;
    }
  }
  std::cout << std::endl << "Initial correlations:" << std::endl << input;

  CaloCorrelatedNoisifier noisifier(input);
  
  std::cout << std::endl << "Noisifier correlations :" << std::endl <<  noisifier.covmatrix() << std::endl;

  HepVector means (10); for (int k = 0; k < 10; k++) means[k] = 0.;
  HepSymMatrix cov (10, 0);

  int nTotal = 4000000;
  for (int i=0; i<nTotal; i++) {
    CaloSamples samples (detId, 10);
    noisifier.noisify(samples);
    for (int ii = 0; ii < 10; ii++) {
      means [ii] += samples [ii];
      for (int ij = ii; ij < 10; ij++) {
	cov [ii][ij] += samples[ii] * samples [ij];
      }
    }
    
  }

  for (int k = 0; k < 10; k++) {
    means[k] = means[k] / nTotal;
  }
  std::cout << "Means:" << means << std::endl;

  for (int k = 0; k < 10; k++) {
    for (int kk = k; kk < 10; kk++) {
      cov[k][kk] = cov[k][kk] / nTotal;
    }
  }
  std::cout << std::endl << "Covariances:" << cov << std::endl;

  HepSymMatrix corr (10, 0);
  for (int k = 0; k < 10; k++) {
    for (int kk = k; kk < 10; kk++) {
      corr [k][kk] = cov[k][kk] / sqrt (cov[k][k]*cov[kk][kk]);
    }
  }
  std::cout << std::endl << "Correlations:" << corr << std::endl;

  HepSymMatrix input2 (10, 0);
  for (int k = 0; k < 10; k++) {
    for (int kk = k; kk < 10; kk++) {
      for (int ix = 0; ix < 10; ix++) {
	input2 [k][kk] += input[k][ix]*input[ix][kk];
      }
    }
  }
  std::cout << std::endl << "SQUARE of initial matrix:" << std::endl << input2;
}




