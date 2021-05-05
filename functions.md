Function Overview:

EE_READ_UNSEC:
  - Returns the value hold in the given Register
  - Parameters --> 8-Bit low adress, 4 Bit high adress
  - This wont check anything for plausability!

EE_READ_SAFE:
  - Returns the value hold in the given Register
  - Parameters --> 8-Bit low adress, 4 Bit high adress
  - Plausability check on both adresses & the returning data
  - will return NULL if check fails!

EE_READ_BIT:
  - WIll read a specific Bit at a given adress, at a given Position
  - Position is shifted -1 (so ranges from 0 - 7, representing the 8 Bits)
  - access can be safe or unsafe (set by bool "saferead")
  - Parameters --> 8-Bit low adress, 4 Bit high adress, Position which is to be checked, saferead
  - will return NULL if adress is invalid or specified bit is out of range

SET_RI_STATUS
  - Lets you enable/disable the ready interrupt
  - Parameters --> bool enable/disable

EE_SET_WRITE
  - Function only lets you enable writing to the EEPROM but does not actually write to it!
  - The writing Process itself, needs to be implemented/called by you
  - Do not call any of the above read functions as this creates overhead
  - Parameters --> bool enable/disable

SET_MASTER_WRITE
  - Lets you enable/disable the master write
  - After calling, you have to set EEPE to 1 on adress 0x3F within *4 Clock cycles* to write Data!
  - Parameters --> bool enable/disable

SET_PRG_MODE
  - Lets you set the programming mode (see Reference Manual for Details!)
  - mode-checks are implemented (valid modes 0-3)
  - different modes are documented in the Code and in the Reference Manual
  - will return 5 if an invalid code has been passed or if the code did not get set properly
  - will return set code if it has been set properly
  - Parameters --> mode (0 = Atomic, 1 = Erase only, 2 = Write only, 3 = Reserved)
