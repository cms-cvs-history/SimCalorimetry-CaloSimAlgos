#include "SimCalorimetry/CaloSimAlgos/interface/CaloSimParameters.h"
#include<iostream>
  
CaloSimParameters::CaloSimParameters(double simHitToPhotoelectrons, double photoelectronsToAnalog,
                 double samplingFactor, double timePhase,
                 int readoutFrameSize, int binOfMaximum,
                 bool doPhotostatistics, bool syncPhase)
: simHitToPhotoelectrons_(simHitToPhotoelectrons),
  photoelectronsToAnalog_(photoelectronsToAnalog),
  samplingFactor_(samplingFactor),
  timePhase_(timePhase),
  readoutFrameSize_(readoutFrameSize),
  binOfMaximum_(binOfMaximum),
  doPhotostatistics_(doPhotostatistics),
  syncPhase_(syncPhase)
{
}



CaloSimParameters::CaloSimParameters(const edm::ParameterSet & p)
: simHitToPhotoelectrons_( p.getParameter<double>("simHitToPhotoelectrons") ),
  photoelectronsToAnalog_( p.getParameter<double>("photoelectronsToAnalog") ),
  samplingFactor_(0.), //FIXME
  timePhase_( p.getParameter<double>("timePhase") ),
  readoutFrameSize_( p.getParameter<int>("readoutFrameSize") ),
  binOfMaximum_( p.getParameter<int>("binOfMaximum") ),
  doPhotostatistics_( p.getParameter<bool>("doPhotoStatistics") ),
  syncPhase_( p.getParameter<double>("syncPhase") )
{
}


std::ostream & operator<<(std::ostream & os, const CaloSimParameters & p) {
  DetId dummy(0);
  os << "CALO SIM PARAMETERS" << std::endl;
  os << p.simHitToPhotoelectrons(dummy) << " pe per SimHit energy " << std::endl;
  os << p.photoelectronsToAnalog() << " Analog signal to be digitized per pe" << std::endl;
  os << " Incident energy / SimHit Energy " << std::endl;
  return os;
}

