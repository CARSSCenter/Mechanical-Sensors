#ifndef __PCAP_TYPES_H_
#define __PCAP_TYPES_H_

#include <stdint.h>
#include <stdbool.h>

union pcap_opcode_nvram_t
{
    unsigned int opcode;
    struct __attribute__((packed))
    {
        unsigned int data : 8;
        unsigned int addr : 10;
        unsigned int op_code : 6;
    } nvram;
};

union pcap_opcode_config_t
{
    unsigned int opcode;
    struct __attribute__((packed))
    {
        unsigned int data : 8;
        unsigned int addr : 6;
        unsigned int op_code : 10;
    } config;
};

union pcap_opcode_result_t
{
    unsigned short opcode;
    struct __attribute__((packed))
    {
        unsigned short data : 8;
        unsigned short addr : 6;
        unsigned short op_code : 2;
    } result;
};

union pcap_opcode_command_t
{
    unsigned char opcode;
    struct __attribute__((packed))
    {
        unsigned char op_code : 8;
    } command;
};

union pcap_opcode_testread_t
{
    unsigned short opcode;
    struct __attribute__((packed))
    {
        unsigned short fixed : 8;
        unsigned short op_code : 8;
    } testread;
};

typedef struct __pcap_config_t
{
    uint8_t OLF_CTUNE : 2;
    uint8_t OLF_FTUNE : 4;
    uint8_t I2C_A : 2;

    uint8_t OX_RUN : 3;
    bool OX_DIV4;
    bool OX_DIS;

    bool RDCHG_EXT_EN;
    bool RDCHG_INT_EN;
    uint8_t RDCHG_INT_SEL0 : 2;
    uint8_t RDCHG_INT_SEL1 : 2;

    bool RCHG_SEL;
    bool RDCHG_EXT_PERM;
    bool RDCHG_PERM_EN;
    uint8_t RDCHG_OPEN : 2;
    bool AUX_CINT;
    bool AUX_PD_DIS;

    bool C_FLOATING;
    bool C_DIFFERENTIAL;
    bool C_COMP_INT;
    bool C_COMP_EXT;
    bool C_REF_INT;

    bool C_DC_BALANCE;
    bool CY_PRE_LONG;
    bool CY_DIV4_DIS;
    bool CY_HFCLK_SEL;
    bool C_PORT_PAT;
    bool CY_PRE_MR1_SHORT;

    uint8_t C_PORT_EN : 6;

    uint16_t C_AVRG : 13;

    uint32_t CONV_TIME : 23;

    uint16_t DISCHARGE_TIME : 10;
    uint8_t C_TRIG_SEL : 3;
    uint8_t C_STARTONPIN : 2;

    uint16_t PRECHARGE_TIME : 10;
    uint8_t C_FAKE : 4;

    uint16_t FULLCHARGE_TIME : 10;
    uint8_t C_REF_SEL : 5;

    uint8_t C_G_EN : 6;
    bool C_G_OP_EXT;
    bool C_G_OP_RUN;

    uint8_t C_G_TIME : 4;
    uint8_t C_G_OP_ATTN : 2;
    uint8_t C_G_OP_VU : 2;

    uint8_t C_G_OP_TR : 3;
    bool R_CY;

    uint16_t R_TRIG_PREDIV : 10;
    uint8_t R_AVRG : 2;
    uint8_t R_TRIG_SEL : 3;

    uint8_t R_STARTONPIN : 2;
    bool R_FAKE;
    bool R_PORT_EN_IREF;
    bool R_PORT_EN_IMES;
    uint8_t R_PORT_EN : 2;


    bool PG0xPG2;
    bool PG1xPG3;
    uint8_t DSP_SPEED : 2;
    uint8_t DSP_MOFLO_EN : 2;

    uint8_t WD_DIS;

    uint8_t DSP_FF_IN : 4;
    uint8_t DSP_STARTONPIN : 4;

    uint8_t DSP_START_EN : 3;
    bool PG4_INTN_EN;
    bool PG5_INTN_EN;

    uint8_t PI0_CLK_SEL : 3;
    bool PI0_PDM_SEL;
    uint8_t PI0_RES : 2;
    bool PI0_TOGGLE_EN;
    bool PI1_TOGGLE_EN;

    uint8_t PI1_CLK_SEL : 3;
    uint8_t PI1_PDM_SEL : 1;
    uint8_t PI1_RES : 2;

    uint8_t PG_PU : 4;
    uint8_t PG_DIR_IN : 4;

    // unsigned char AMS_INT_REG:4;        // Mandatory : 7
    bool AUTOSTART;
    bool BG_PERM;
    bool DSP_TRIG_BG;
    bool INT_TRIG_BG;

    uint8_t CDC_GAIN_CORR;

    uint8_t BG_TIME : 8;

    uint8_t PULSE_SEL0 : 4;
    uint8_t PULSE_SEL1 : 4;

    uint8_t C_SENSE_SEL;

    uint8_t R_SENSE_SEL;

    bool C_MEDIAN_EN;
    bool R_MEDIAN_EN;
    bool HS_MODE_SEL;
    bool EN_ASYNC_READ;
    bool ALARM0_SELECT;
    bool ALARM1_SELECT;

    bool RUNBIT;

    uint8_t MEM_LOCK : 4;

    uint16_t SERIAL_NUMBER;

    uint8_t MEM_CTRL;

} pcap_config_t;

typedef struct _pcap04_result_t
{
	uint32_t res0;
	uint32_t res1;
	uint32_t res2;
} pcap04_result_t;

#endif //__PCAP_TYPES_H_
