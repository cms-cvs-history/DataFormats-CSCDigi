/**\testCSCWireDigis.cc to be copied to testCSCDigis.cc before compiling
 *
 * Test suit for CSCWireDigis.
 *
 * $Date$
 * $Revision$
 *
 * \author N. Terentiev, CMU
 */


static const char CVSId[] = "$Id$";

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/CSCDigi/interface/CSCWireDigi.h>
#include <DataFormats/CSCDigi/interface/CSCWireDigiCollection.h>
#include <DataFormats/MuonDetId/interface/CSCDetId.h>

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
  CPPUNIT_ASSERT (sizeof(CSCWireDigi::PersistentPacking)==sizeof(CSCWireDigi::PackedDigiType));
  CPPUNIT_ASSERT(sizeof(CSCWireDigi::ChannelPacking)==sizeof(int));
  printf("\n");
  printf("I'm in testDigiPacking()   \n");
}


void testCSCDigis::testDigiCollectionPut(){

  printf("\n");
  printf("I'm in testDigiCollectionPut() \n");

// Filling collection

       CSCWireDigiCollection digiCollection;

  for(int endcp=1; endcp<3; endcp++)
   for(int stn=1; stn<5; stn++)
    for(int rng=1; rng<4; rng++)
     for(int csc=1; csc<37; csc++)
      for(int pln=1; pln<7; pln++) {

       CSCDetId cscdetid(endcp,stn,rng,csc,pln);

       std::vector<CSCWireDigi> digivec;
       for (int i=10; i<11; ++i){
           CSCWireDigi::PackedDigiType pd;
           pd.wire=i;
           pd.tbin=5;

           CSCWireDigi digi(pd);
           digivec.push_back(digi);
        }

        digiCollection.put(std::make_pair(digivec.begin(), digivec.end()),cscdetid);

      } // end of for(int endcp=1 ...for(int pln=1 ...) {


// Reading collection back

        int count1=0;
        CSCWireDigiCollection::DigiRangeIterator detUnitIt;
        for (detUnitIt=digiCollection.begin();
             detUnitIt!=digiCollection.end();
           ++detUnitIt){

           const CSCDetId& id = (*detUnitIt).first;

           const CSCWireDigiCollection::Range& range = (*detUnitIt).second;
           for (CSCWireDigiCollection::const_iterator digiIt = 
	        range.first; digiIt!=range.second;
	      ++digiIt){

              count1++;
              CPPUNIT_ASSERT((*digiIt).getWireGroup()==10);
              CPPUNIT_ASSERT((*digiIt).getBeamCrossingTag()==5);
 printf("endcap station ring csc plane wire tbin: %3d %3d %3d %3d %3d %3d  %3d\n",id.endcap(),id.station(),id.ring(),id.chamber(),id.layer(),(*digiIt).getWireGroup(),(*digiIt).getBeamCrossingTag());

    }// for digis in layer
   }// end of for (detUnitIt=...

    printf("count1:  %3d \n", count1);
}

