#include <DataFormats/CSCDigi/interface/CSCWireDigi.h>
#include <DataFormats/CSCDigi/interface/CSCWireDigiCollection.h>
#include <DataFormats/CSCDigi/interface/CSCRPCDigi.h>
#include <DataFormats/CSCDigi/interface/CSCRPCDigiCollection.h>
#include <DataFormats/CSCDigi/interface/CSCStripDigi.h>
#include <DataFormats/CSCDigi/interface/CSCStripDigiCollection.h>
#include <DataFormats/CSCDigi/interface/CSCComparatorDigi.h>
#include <DataFormats/CSCDigi/interface/CSCComparatorDigiCollection.h>
#include <FWCore/EDProduct/interface/Wrapper.h>
#include <vector>
#include <map>

namespace{ 
  namespace {

  CSCWireDigi cWD_;
  CSCRPCDigi  cRD_;
  CSCStripDigi cSD_;
  CSCComparatorDigi cCD_;

  CSCWireDigi::PersistentPacking ppWD_;
  CSCRPCDigi::PersistentPacking ppRD_;

  std::vector<CSCWireDigi>  vWD_;
  std::vector<CSCRPCDigi>   vRD_;
  std::vector<CSCStripDigi>  vSD_;
  std::vector<CSCComparatorDigi>  vCD_;

  std::vector<std::vector<CSCWireDigi> >  vvWD_; 
  std::vector<std::vector<CSCRPCDigi>  >  vvRD_;
  std::vector<std::vector<CSCStripDigi> >  vvSD_; 
  std::vector<std::vector<CSCComparatorDigi> >  vvCD_; 

  CSCWireDigiCollection clWD_;
  CSCRPCDigiCollection  clRD_;
  CSCStripDigiCollection clSD_;
  CSCComparatorDigiCollection clCD_;
    
  edm::Wrapper<CSCWireDigiCollection> wWD_;
  edm::Wrapper<CSCRPCDigiCollection> wRD_;
  edm::Wrapper<CSCStripDigiCollection> wSD_;
  edm::Wrapper<CSCComparatorDigiCollection> wCD_;

  }
}
