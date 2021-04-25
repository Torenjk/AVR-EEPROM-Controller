static uint8_t* EE_CONTROL_REG = 0x3F; //EECR 
static uint8_t* EE_DATA = 0x40; //EEDR
static uint8_t* EE_AD_LOW =0x41; //EEARL
static uint8_t* EE_AD_HIGH =0x42; //EEARH
static uint8_t* S_REG = 0x5F; //SREG AVR STATUS

uint8_t EE_READ_UNSEC(uint8_t adress_low, uint8_t adress_high){//Should only be used for debugging!
    *EE_CONTROL_REG = 0x0; //Reset flags
    *EE_AD_LOW = adress_low;
    *EE_AD_HIGH = adress_high;
    *EE_CONTROL_REG |= (1 << 0); //Shift to read
    return *EE_DATA;
}

uint8_t EE_READ_SAFE(uint8_t adress_low, uint8_t adress_high){
    if(adress_low == NULL) return NULL; //invalid
    if(adress_high == NULL) return NULL; //invalid
    if(0xFF < adress_low) return NULL; //Adress low out of Range
    if(0x4 < adress_high) return NULL; //Adress high out of Range
    *EE_CONTROL_REG = 0x0; //Reset EEPE Bit
    *EE_AD_LOW = adress_low;
    *EE_AD_HIGH = adress_high;
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

void SET_RI_STATUS(bool ri_enable){ //Set ready interrupt enable
    //Todo: First check if I in SREG is set
    if (ri_enable){
        *S_REG |= (1 << 7); //Set I in SREG
        *EE_CONTROL_REG |= (1 << 3); //Set EERIE to 1
    } else if (!ri_enable){
        *EE_CONTROL_REG &= ~(1 << 3); //Set EERIE to 0
    }
}


/*
The following functions should only be called in the following scenarios:
- You are writing to EEPROM by hand or by 3rd party
*/

void EE_SET_WRITE(bool w_enable){ //For external calls
    if(w_enable){
        *EE_CONTROL_REG |= 0x0; //Reset
        *EE_CONTROL_REG = (1 << 2); //Set EEMPE to enable Write
    }
    if(!w_enable){
        *EE_CONTROL_REG = 0x0; //Disable EEMPE and Reset
    }
}

void SET_MASTER_WRITE(bool mw_enable){ //For external calls


}


uint8_t SET_PRG_MODE(uint8_t mode){ //Function will return the set mode, 5 == Errorcode
    if(mode >= 4 || mode < 0 ) return 5;
        switch (mode){
             case 0: *EE_CONTROL_REG = 0x0; //Atomic Operation
             case 1: *EE_CONTROL_REG = (1 << 4); //00010000 Erase only
             case 2: *EE_CONTROL_REG = (1 << 5); //00100000 Write only
             case 3: *EE_CONTROL_REG = 0x30; //00110000 Reserved
        }
    if(mode == *EE_CONTROL_REG){
        return *EE_CONTROL_REG;
    } else {
        return 5; //Error
    }
}



int main(){

    return 0;
}
