# AVR-EEPROM-Controller
Controller for integrated EEPROM on AVR IC's

Basic functions for interaction with EEPROM.

Do not use in Bootloader, I did not implement Flash-Write checks.

Currently limited to AT328P! But i plan to make it intercompatible.

TODO:
- [x] Read unsafe
- [ ] Write unsafe
- [x] Read safe
- [ ] Write safe
- [ ] enable external RW (Master)
- [ ] Get size function
- [ ] Portability for the whole family
- [ ] Change Port Zero-Sets to Bitwise operations
