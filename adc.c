#include <xc.h>
unsigned short read_adc() {
    GO = 1;
    while (GO);
    return ADRESL | (ADRESH << 8);
}

void init_adc() {
    CHS3 = 0;
    CHS2 = 1;
    CHS1 = 0;
    CHS0 = 0;

    GO = 0;
    ADON = 1;
    VCFG1 = 0;
    VCFG0 = 0;

    PCFG3 = 1;
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 0;

    ADFM = 1;

    ADCS2 = 0;
    ADCS2 = 1;
    ADCS2 = 0;

    ACQT2 = 1;
    ACQT1 = 0;
    ACQT0 = 0;
}
