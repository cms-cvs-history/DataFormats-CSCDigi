/**\testCSCDigis.cc
 *
 * Test suit for CSCWireDigis.
 * Based on DTDigi
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


class testCSCDigis: public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(testCSCDigis);

  CPPUNIT_TEST(testDigiPacking);
  CPPUNIT_TEST(testDigiCollectionInsert);
  CPPUNIT_TEST(testDigiCollectionPut);

  CPPUNIT_TEST_SUITE_END();

public:


  void setUp(){}
  void tearDown(){}  
  void testDigiPacking();
  void testDigiCollectionInsert();
  void testDigiCollectionPut();
}; 

///registration of the test so that the runner can find it
CPPUNIT_TEST_SUITE_REGISTRATION(testCSCDigis);


void testCSCDigis::testDigiPacking(){
  CPPUNIT_ASSERT (sizeof(CSCWireDigi::PersistentPacking)==sizeof(CSCWireDigi::PackedDigiType));
  CPPUNIT_ASSERT(sizeof(CSCWireDigi::ChannelPacking)==sizeof(int));
}


void testCSCDigis::testDigiCollectionPut(){

  CSCDetId layer(2,7,8,1,244);

  CSCWireDigiCollection digiCollection;

  std::vector<CSCWireDigi> digivec;
  for (int i=0; i<10; ++i){
    CSCWireDigi::PackedDigiType pd;
    pd.wire=1+i;
    pd.tbin=5;

    CSCWireDigi digi(pd);
    digivec.push_back(digi);
  }

  digiCollection.put(std::make_pair(digivec.begin(), digivec.end()),layer);
    
  CSCWireDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt=digiCollection.begin();
       detUnitIt!=digiCollection.end();
       ++detUnitIt){

    int i=0;
    for (CSCWireDigiCollection::const_iterator digiIt = 
	  detUnitIt->second.first;
	  digiIt!=detUnitIt->second.second;
	 ++digiIt){

      

      CPPUNIT_ASSERT((*digiIt).getWireGroup()==1+i);
      CPPUNIT_ASSERT((*digiIt).getBeamCrossingTag()==5);
      i++;
      
    }// for digis in layer
   }// for layers

}

void testCSCDigis::testDigiCollectionInsert(){

  CSCWireDigi::PackedDigiType pd;
  pd.wire=1;
  pd.tbin=4;


  CSCWireDigi digi(pd);


  CSCDetId layer(2,7,8,1,244);

  CSCWireDigiCollection digiCollection;

  digiCollection.insertDigi(layer,digi);

  //  CSCWireDigiCollection::DetUnitIds layers = digiCollection.layers();

//   for (CSCWireDigiCollection::DetUnitIds::const_iterator layerIt = layers.begin();
//        layerIt!= layers.end(); ++layerIt){

  CSCWireDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt=digiCollection.begin();
       detUnitIt!=digiCollection.end();
       ++detUnitIt){

    for (CSCWireDigiCollection::const_iterator digiIt =
          detUnitIt->second.first;
          digiIt!=detUnitIt->second.second;
         ++digiIt){


      CPPUNIT_ASSERT((*digiIt).getWireGroup()==1);
      CPPUNIT_ASSERT((*digiIt).getBeamCrossingTag()==4);


    }// for digis in layer
   }// for layers
}
