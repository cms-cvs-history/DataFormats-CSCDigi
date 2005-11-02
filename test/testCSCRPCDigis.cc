/**\testCSCRPCDigis.cc to be copied to testCSCDigis.cc before compiling
 *
 * Test suit for CSCRPCDigis.
 * Based on testDTDigis.cc
 *
 * $Date$
 * $Revision$
 *
 * \author N. Terentiev, CMU
 */


static const char CVSId[] = "$Id$";

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/CSCDigi/interface/CSCRPCDigi.h>
#include <DataFormats/CSCDigi/interface/CSCRPCDigiCollection.h>
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
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
  void testDigiCollectionPut();
}; 

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testCSCDigis);

void testCSCDigis::testDigiPacking(){
  CPPUNIT_ASSERT (sizeof(CSCRPCDigi::PersistentPacking)==sizeof(CSCRPCDigi::PackedDigiType));
  CPPUNIT_ASSERT(sizeof(CSCRPCDigi::ChannelPacking)==sizeof(int));
  printf("\n");
  printf("I'm in testDigiPacking()   \n");
}


void testCSCDigis::testDigiCollectionPut(){

  printf("\n");
  printf("I'm in testDigiCollectionPut() \n");

// Filling collection

       CSCRPCDigiCollection digiCollection;

  for(int region=1; region<2; region++)
   for(int rng=1; rng<2; rng++)
    for(int stn=1; stn<2; stn++)
     for(int sct=1; sct<2; sct++)
      for(int layer=1; layer<2; layer++) 
       for(int subsct=1; subsct<2; subsct++)
        for(int roll=1; roll<2; roll++)
                                               {
       RPCDetId rpcdetid(region,rng,stn,sct,layer,subsct,roll);

       std::vector<CSCRPCDigi> digivec;
       for (int i=10; i<11; ++i){
           CSCRPCDigi::PackedDigiType pd;
           pd.strip=i;
           pd.tbin=3;

           CSCRPCDigi digi(pd);
           digivec.push_back(digi);
        }

        digiCollection.put(std::make_pair(digivec.begin(), digivec.end()),rpcdetid);

      } // end of for(int region=1 ...for(int roll=1 ...) {


// Reading collection back

        int count1=0;
        CSCRPCDigiCollection::DigiRangeIterator detUnitIt;
        for (detUnitIt=digiCollection.begin();
             detUnitIt!=digiCollection.end();
           ++detUnitIt){

           const RPCDetId& id = (*detUnitIt).first;

           const CSCRPCDigiCollection::Range& range = (*detUnitIt).second;
           for (CSCRPCDigiCollection::const_iterator digiIt = 
	        range.first; digiIt!=range.second;
	      ++digiIt){

              count1++;
              CPPUNIT_ASSERT((*digiIt).getStrip()==10);
              CPPUNIT_ASSERT((*digiIt).getBx()==3);
 printf("region ring station sector layer subsector roll strip tbin: %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",id.region(),id.ring(),id.station(),id.sector(),id.layer(),id.subsector(),id.roll(),(*digiIt).getStrip(),(*digiIt).getBx());

    }// for digis in layer
   }// end of for (detUnitIt=...

    printf("count1:  %3d \n", count1);
}

