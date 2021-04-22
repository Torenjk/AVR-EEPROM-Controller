/*
AVR EEPROM Controller
*/

static uint8_t* EE_CONTROL_REG = 0x3F; //EECR 
static uint8_t* EE_DATA = 0x40; //EEDR
static uint8_t* EE_ADRESS_LOW =0x41; //EEARL
static uint8_t* EE_ADRESS_HIGH =0x42; //EEARH

uint8_t EE_READ_UNSEC(uint8_t adress_low, uint8_t adress_high){//Should only be used for debugging!
    *EE_CONTROL_REG = 0; //Reset flags
    *EE_ADRESS_LOW = adress_low;
    *EE_ADRESS_HIGH = adress_high;
    *EE_CONTROL_REG |= (1 << 0); //Shift to read
    return **EE_DATA;
}

