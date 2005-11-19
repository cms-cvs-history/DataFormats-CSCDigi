/**\testCSCStripDigis.cc to be copied to testCSCDigis.cc before compiling
 *
 * Test suit for CSCStripDigis.
 * Based on testDCSCWireDigis.cc
 *
 * $Date: 2005/11/01 20:40:38 $
 * $Revision: 1.3 $
 *
 * \author M.Schmitt, Northwestern
 */


static const char CVSId[] = "$Id: testCSCDigis.cc,v 1.3 2005/11/01 20:40:38 teren Exp $";

#include <cppunit/extensions/HelperMacros.h>
#include <DataFormats/CSCDigi/interface/CSCStripDigi.h>
#include <DataFormats/CSCDigi/interface/CSCStripDigiCollection.h>
#include <DataFormats/MuonDetId/interface/CSCDetId.h>
#include <stdio.h>
#include <vector>

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
  printf("\n");
  printf("I'm in testDigiPacking()   \n");
}


void testCSCDigis::testDigiCollectionPut(){

  printf("\n");
  printf("I'm in testDigiCollectionPut() \n");

// Filling collection

  CSCStripDigiCollection digiCollection;

  for(int endcp=1; endcp<3; endcp++)
   for(int stn=1; stn<5; stn++)
    for(int rng=1; rng<4; rng++)
     for(int csc=1; csc<37; csc++)
      for(int pln=1; pln<7; pln++) {

       CSCDetId cscdetid(endcp,stn,rng,csc,pln);

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

        digiCollection.put(std::make_pair(digivec.begin(), digivec.end()),cscdetid);

      } // end of for(int endcp=1 ...for(int pln=1 ...) {


// Reading collection back

  int count1=0;
  CSCStripDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt=digiCollection.begin();
       detUnitIt!=digiCollection.end();
       ++detUnitIt){

    const CSCDetId& id = (*detUnitIt).first;

    const CSCStripDigiCollection::Range& range = (*detUnitIt).second;
    for (CSCStripDigiCollection::const_iterator digiIt = 
	   range.first; digiIt!=range.second; ++digiIt){
      count1++;
      CPPUNIT_ASSERT((*digiIt).getStrip()==10);
      printf("endcap station ring csc plane: %3d %3d %3d %3d %3d strip: %3d  ADC: %4d %4d %4d %4d %4d %4d %4d %4d\n",
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
  
  printf("count1:  %3d \n", count1);
}

