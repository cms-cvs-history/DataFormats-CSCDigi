/**\testCSCDigis.cc
 *
 * Test suit for CSCDigi.
 * Based on testDTDigis.cc
 *
 * $Date$
 * $Revision$
 *
 * \author N. Terentiev, CMU (for CSCWireDigi and CSCRPCDigi)
 * \author M.Schmitt,    Northwestern (for CSCComparatorDigi and CSCStripDigi)
 */


static const char CVSId[] = "$Id$";

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/MuonDetId/interface/CSCDetId.h>
#include <DataFormats/MuonDetId/interface/RPCDetId.h>

#include <DataFormats/CSCDigi/interface/CSCWireDigi.h>
#include <DataFormats/CSCDigi/interface/CSCWireDigiCollection.h>
                                                                                
#include <DataFormats/CSCDigi/interface/CSCComparatorDigi.h>
#include <DataFormats/CSCDigi/interface/CSCComparatorDigiCollection.h>

#include <DataFormats/CSCDigi/interface/CSCStripDigi.h>
#include <DataFormats/CSCDigi/interface/CSCStripDigiCollection.h>

#include <DataFormats/CSCDigi/interface/CSCRPCDigi.h>
#include <DataFormats/CSCDigi/interface/CSCRPCDigiCollection.h>

#include <stdio.h>

class testCSCDigis: public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(testCSCDigis);
  CPPUNIT_TEST(testDigiPacking);
  CPPUNIT_TEST(testDigiCollectionPut);
  CPPUNIT_TEST_SUITE_END();

public:

  void setUp(){}
  void tearDown(){}  
  void testDigiPacking();

  void fillCSCWireDigi(CSCWireDigiCollection &);
  void fillCSCComparatorDigi(CSCComparatorDigiCollection &);
  void fillCSCStripDigi(CSCStripDigiCollection &);
  void fillCSCRPCDigi(CSCRPCDigiCollection &);

  void readCSCWireDigi(CSCWireDigiCollection &);
  void readCSCComparatorDigi(CSCComparatorDigiCollection &);
  void readCSCStripDigi(CSCStripDigiCollection &);
  void readCSCRPCDigi(CSCRPCDigiCollection &);

  void testDigiCollectionPut();
}; 

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testCSCDigis);

void testCSCDigis::testDigiPacking(){

  CPPUNIT_ASSERT(sizeof(CSCWireDigi::PersistentPacking)==sizeof(CSCWireDigi::PackedDigiType));
  CPPUNIT_ASSERT(sizeof(CSCWireDigi::ChannelPacking)==sizeof(int));

//  CPPUNIT_ASSERT(sizeof(CSCComparatorDigi::PersistentPacking)==sizeof(CSCComparatorDigi::PackedDigiType));
//  CPPUNIT_ASSERT(sizeof(CSCComparatorDigi::ChannelPacking)==sizeof(int));

//  CPPUNIT_ASSERT(sizeof(CSCStripDigi::PersistentPacking)==sizeof(CSCStripDigi::PackedDigiType));
//  CPPUNIT_ASSERT(sizeof(CSCStripDigi::ChannelPacking)==sizeof(int));

  CPPUNIT_ASSERT (sizeof(CSCRPCDigi::PersistentPacking)==sizeof(CSCRPCDigi::PackedDigiType));
  CPPUNIT_ASSERT(sizeof(CSCRPCDigi::ChannelPacking)==sizeof(int));
}

void testCSCDigis::fillCSCWireDigi(CSCWireDigiCollection & collection){

  for(int endcp=1; endcp<3; endcp++)
   for(int stn=1; stn<5; stn++)
    for(int rng=1; rng<4; rng++)
     for(int csc=1; csc<37; csc++)
      for(int pln=1; pln<7; pln++) {
  
       CSCDetId detid(endcp,stn,rng,csc,pln);
                                                                                
       std::vector<CSCWireDigi> digivec;
       for (int i=10; i<11; ++i){
           CSCWireDigi::PackedDigiType pd;
           pd.wire=i;
           pd.tbin=5;
  
           CSCWireDigi digi(pd);
           digivec.push_back(digi);
        }
  
        collection.put(std::make_pair(digivec.begin(),digivec.end()),detid);
  
      } // end of for(int endcp=1 ...for(int pln=1 ...) 
}

void testCSCDigis::fillCSCComparatorDigi(CSCComparatorDigiCollection & collection){

  for(int endcp=1; endcp<3; endcp++)
   for(int stn=1; stn<5; stn++)
    for(int rng=1; rng<4; rng++)
     for(int csc=1; csc<37; csc++)
      for(int pln=1; pln<7; pln++) {
 
       CSCDetId detid(endcp,stn,rng,csc,pln);
 
       std::vector<CSCComparatorDigi> digivec;
       for (int i=10; i<11; ++i){
           int aStrip = i;
           int aComparator = 2;
           CSCComparatorDigi::theComparatorDigi cd;
           cd.strip = aStrip;
           cd.comparator = aComparator;
           CSCComparatorDigi digi(cd);
           digivec.push_back(digi);
        }
 
        collection.put(std::make_pair(digivec.begin(), digivec.end()),detid);
 
      } // end of for(int endcp=1 ...for(int pln=1 ...)
}

void testCSCDigis::fillCSCStripDigi(CSCStripDigiCollection & collection){

  for(int endcp=1; endcp<3; endcp++)
   for(int stn=1; stn<5; stn++)
    for(int rng=1; rng<4; rng++)
     for(int csc=1; csc<37; csc++)
      for(int pln=1; pln<7; pln++) {
 
       CSCDetId detid(endcp,stn,rng,csc,pln);
 
       std::vector<CSCStripDigi> digivec;
       for (int i=10; i<11; ++i){
           int aStrip = i;
           std::vector<int> someADCCounts(8);
           someADCCounts[0] = 9;
           someADCCounts[1] = 11;
           someADCCounts[2] = 23;
           someADCCounts[3] = 51;
           someADCCounts[4] = 102;
           someADCCounts[5] = 88;
           someADCCounts[6] = 48;
           someADCCounts[7] = 19;
           CSCStripDigi::theStripDigi sd;
           sd.strip = aStrip;
           sd.ADCCounts = someADCCounts;
           CSCStripDigi digi(sd);
           digivec.push_back(digi);
        }
 
        collection.put(std::make_pair(digivec.begin(), digivec.end()),detid);
 
      } // end of for(int endcp=1 ...for(int pln=1 ...) 
}

void testCSCDigis::fillCSCRPCDigi(CSCRPCDigiCollection & collection){

  for(int region=1; region<2; region++)
   for(int rng=1; rng<2; rng++)
    for(int stn=1; stn<2; stn++)
     for(int sct=1; sct<2; sct++)
      for(int layer=1; layer<2; layer++)
       for(int subsct=1; subsct<2; subsct++)
        for(int roll=1; roll<2; roll++)
                                               {
       RPCDetId detid(region,rng,stn,sct,layer,subsct,roll);
                                                                                
       std::vector<CSCRPCDigi> digivec;
       for (int i=10; i<11; ++i){
           CSCRPCDigi::PackedDigiType pd;
           pd.strip=i;
           pd.tbin=3;
 
           CSCRPCDigi digi(pd);
           digivec.push_back(digi);
        }
 
        collection.put(std::make_pair(digivec.begin(),digivec.end()),detid);
 
      } // end of for(int region=1 ...for(int roll=1 ...) 
}

void testCSCDigis::readCSCWireDigi(CSCWireDigiCollection & collection){

        int count=0;
        CSCWireDigiCollection::DigiRangeIterator detUnitIt;
        for (detUnitIt=collection.begin();
             detUnitIt!=collection.end();
           ++detUnitIt){
  
           const CSCDetId& id = (*detUnitIt).first;
  
           const CSCWireDigiCollection::Range& range =(*detUnitIt).second;
           for (CSCWireDigiCollection::const_iterator digiIt =
                range.first; digiIt!=range.second;
              ++digiIt){
  
              count++;
              CPPUNIT_ASSERT((*digiIt).getWireGroup()==10);
              CPPUNIT_ASSERT((*digiIt).getBeamCrossingTag()==5);
 printf("CSC Wire - endcap station ring csc plane wire tbin: %3d %3d %3d %3d %3d %3d  %3d\n",id.endcap(),id.station(),id.ring(),id.chamber(),id.layer(),(*digiIt).getWireGroup(),(*digiIt).getBeamCrossingTag());
  
    }// for digis in layer
   }// end of for (detUnitIt=...
    printf("CSC Wire count:  %3d \n", count);
} 

void testCSCDigis::readCSCComparatorDigi(CSCComparatorDigiCollection & collection){

  int count=0;
  CSCComparatorDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt=collection.begin();
       detUnitIt!=collection.end();
       ++detUnitIt){
 
    const CSCDetId& id = (*detUnitIt).first;
                                                                                                                    
    const CSCComparatorDigiCollection::Range& range = (*detUnitIt).second;
    for (CSCComparatorDigiCollection::const_iterator digiIt =
           range.first; digiIt!=range.second; ++digiIt){
      count++;
      CPPUNIT_ASSERT((*digiIt).getComparator()==2);
      CPPUNIT_ASSERT((*digiIt).getStrip()==10);
      printf("CSC Comparator - endcap station ring csc plane strip comparator: %3d %3d %3d %3d %3d %3d  %3d\n",id.endcap(),id.station(),id.ring(),id.chamber(),id.layer(),(*digiIt).getStrip(),(*digiIt).getComparator());
 
    }// for digis in layer
  }// end of for (detUnitIt=...
   
  printf("CSC Comparator count:  %3d \n", count);
 
}

void testCSCDigis::readCSCStripDigi(CSCStripDigiCollection & collection){

  int count=0;
  CSCStripDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt=collection.begin();
       detUnitIt!=collection.end();
       ++detUnitIt){
 
    const CSCDetId& id = (*detUnitIt).first;
 
    const CSCStripDigiCollection::Range& range = (*detUnitIt).second;
    for (CSCStripDigiCollection::const_iterator digiIt =
           range.first; digiIt!=range.second; ++digiIt){
      count++;
      CPPUNIT_ASSERT((*digiIt).getStrip()==10);
      printf("CSC Strip - endcap station ring csc plane: %3d %3d %3d %3d %3d strip: %3d  ADC: %4d %4d %4d %4d %4d %4d %4d %4d\n",
             id.endcap(),id.station(),id.ring(),id.chamber(),id.layer(),
             (*digiIt).getStrip(),
             (*digiIt).getADCCounts()[0],
             (*digiIt).getADCCounts()[1],
             (*digiIt).getADCCounts()[2],
             (*digiIt).getADCCounts()[3],
             (*digiIt).getADCCounts()[4],
             (*digiIt).getADCCounts()[5],
             (*digiIt).getADCCounts()[6],
             (*digiIt).getADCCounts()[7]);
 
    }// for digis in layer
  }// end of for (detUnitIt=...
   
  printf("CSC Strip count:  %3d \n", count);
}

void testCSCDigis::readCSCRPCDigi(CSCRPCDigiCollection & collection){

        int count=0;
        CSCRPCDigiCollection::DigiRangeIterator detUnitIt;
        for (detUnitIt=collection.begin();
             detUnitIt!=collection.end();
           ++detUnitIt){
 
           const RPCDetId& id = (*detUnitIt).first;
 
           const CSCRPCDigiCollection::Range& range = 
(*detUnitIt).second;
           for (CSCRPCDigiCollection::const_iterator digiIt =
                range.first; digiIt!=range.second;
              ++digiIt){
 
              count++;
              CPPUNIT_ASSERT((*digiIt).getStrip()==10);
              CPPUNIT_ASSERT((*digiIt).getBx()==3);
 printf("RPC - region ring station sector layer subsector roll strip tbin: %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",id.region(),id.ring(),id.station(),id.sector(),id.layer(),id.subsector(),id.roll(),(*digiIt).getStrip(),(*digiIt).getBx());
 
    }// for digis in layer
   }// end of for (detUnitIt=...
 
    printf("RPC count:  %3d \n", count); 
}

void testCSCDigis::testDigiCollectionPut(){

/************           Filling collections             *****************/

       CSCWireDigiCollection wiredigiCollection;
       fillCSCWireDigi(wiredigiCollection);

       CSCComparatorDigiCollection comparatordigiCollection;
       fillCSCComparatorDigi(comparatordigiCollection);

       CSCStripDigiCollection stripdigiCollection;
       fillCSCStripDigi(stripdigiCollection);


       CSCRPCDigiCollection rpcdigiCollection;
       fillCSCRPCDigi(rpcdigiCollection);

/************           Reading collections             *****************/

       readCSCWireDigi(wiredigiCollection);
       readCSCComparatorDigi(comparatordigiCollection);
       readCSCStripDigi(stripdigiCollection);
       readCSCRPCDigi(rpcdigiCollection);
}
