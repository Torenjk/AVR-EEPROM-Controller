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

uint8_t EE_READ_SAFE(uint8_t adress_low, uint8_t adress_high){
    if(adress_low == NULL) return NULL; //invalid
    if(adress_high == NULL) return NULL; //invalid
    if(0xFF < adress_low) return NULL; //Adress low out of Range
    if(0x4 < adress_high) return NULL; //Adress high out of Range
    *EE_CONTROL_REG = 0; //Reset EEPE Bit
    *EE_ADRESS_LOW = adress_low;
    *EE_ADRESS_HIGH = adress_high;
    *EE_CONTROL_REG |= (1 << 0); //Trigger read
    if(*EE_DATA == NULL)
        {
            chk_integrity();
            return NULL; //invalid result
        } 
    return *EE_DATA;
}

bool chk_integrity(){
    //TODO
}

void EE_SET_WRITE(bool w_enable){//For external calls
    if(w_enable){
        *EE_CONTROL_REG |= 0; //Reset
        *EE_CONTROL_REG = (1 << 2); //Set EEMPE to enable Write
    }
    if(!w_enable){
        *EE_CONTROL_REG = 0; //Disable EEMPE and Reset
    }
}

int main(){

    return 0;
}


