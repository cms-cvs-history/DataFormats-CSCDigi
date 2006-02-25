#ifndef CSCALCTDigi_CSCALCTDigi_h
#define CSCALCTDigi_CSCALCTDigi_h

/**\class CSCALCTDigi
 *
 * Digi for ALCT trigger primitives. 
 *
 * $Date:$
 * $Revision:$
 *
 * \author N. Terentiev, CMU
 */

class CSCALCTDigi{

public:

  typedef unsigned int ChannelType;

  /// Enum, structures

      /// Length of packed fields
  enum packing{
                valid_s     = 1, // ALCT validity (1 - valid ALCT and bits 
                                 // below are meaningful)
                quality_s   = 2, // Quality of a pattern
                accel_s     = 1, // 1-Accelerator pattern, 0-CollisionA or
                                 // Collision B pattern
                pattern_s  = 1, // 1-CollisionB pattern if accel_s=0,
                                 // 0-CollisionA pattern if accel_s=0 
                keywire_s   = 7, // Key Wire group
                bx_s        = 5, // BX - five low bits of BXN counter 
                                 // tagged by the ALCT
                trknmb_s    = 2 // track number (1,2), not a part of ALCT
                                 // data format
  };
      /// The packed digi content  
  struct PackedDigiType {
    unsigned int valid     : valid_s;
    unsigned int quality   : quality_s;
    unsigned int accel     : accel_s;
    unsigned int pattern   : pattern_s;
    unsigned int keywire   : keywire_s;
    unsigned int bx        : bx_s;
    unsigned int trknmb    : trknmb_s;
  };

      /// The packed data as seen by the persistency - should never be used
      /// directly, only by calling data().
      /// Made public to be able to generate lcgdict, SA, 27/4/05
  struct PersistentPacking {
    unsigned int w1;
  };

  /// Constructors

//  explicit CSCALCTDigi (int trknmb, int keywire,int bx, int quality, int pattern, int valid);  // obsolete
  explicit CSCALCTDigi (int valid, int quality, int accel, int pattern, int keywire, int bx, int trknmb); 
  explicit CSCALCTDigi (ChannelType channel); /// from channel
  CSCALCTDigi (PackedDigiType packed_value);  /// from a packed value
  CSCALCTDigi (const CSCALCTDigi& digi);      /// copy
  CSCALCTDigi ();                             /// default

  /// Assignment operator

  CSCALCTDigi& operator=(const CSCALCTDigi& digi);

  /// Gets

      /// all digi content in a packed format
  PackedDigiType packedData() const { return *(data()); }
      /// the channel identifier and the digi number packed together
  ChannelType channel() const ;

      /// return ALCT validity
  int getValid() const;
      /// return quality
  int getQuality() const;
      /// return accel
  int getAccel() const;
      /// return pattern
  int getPattern() const;
      /// return key wire group
  int getKwire() const;
      /// return BX
  int getBx() const;
      /// return track number number
  int getTrknmb() const;

  /// Prints

      /// Print content of digi
  void print() const;
      /// Print the binary representation of the digi
  void dump() const;

private:
  friend class testCSCDigis;

  /// Set, access, repack

//  void set(int trknmb, int keywire,int bx, int quality, int pattern, int valid);      /// set data words
  void set(int valid, int quality, int accel, int pattern, int keywire, int bx, int trknmb); /// set data words
  void setData(PackedDigiType p);     /// set from a PackedDigiType
  PackedDigiType* data();             /// access to the packed data
  const PackedDigiType* data() const; /// const access to the packed data
  struct ChannelPacking {
    unsigned int valid     : valid_s;
    unsigned int quality   : quality_s;
    unsigned int accel     : accel_s;
    unsigned int pattern   : pattern_s;
    unsigned int keywire   : keywire_s;
    unsigned int bx        : bx_s;
    unsigned int trknmb    : trknmb_s;
  };                                 /// repack the channel number to an int

  PersistentPacking persistentData;

};

#include<iostream>
  /// needed by COBRA
inline std::ostream & operator<<(std::ostream & o, const CSCALCTDigi& digi) {
  return o << " " << digi.getValid()
           << " " << digi.getQuality()
           << " " << digi.getAccel()
           << " " << digi.getPattern()
           << " " << digi.getKwire()
           << " " << digi.getBx()
           << " " << digi.getTrknmb();
}
#endif
