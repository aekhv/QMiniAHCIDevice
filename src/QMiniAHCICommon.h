/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCICOMMON_H
#define QMINIAHCICOMMON_H

#include "stdint.h"

// ATA device register LBA mode
#define ATA_DEVICE_LBA_MODE         0x40

// ATA command codes
#define ATA_CMD_IDENTIFY_DEVICE     0xEC
#define ATA_CMD_READ_SECTORS_EXT    0x24
#define ATA_CMD_READ_DMA_EXT        0x25
#define ATA_CMD_WRITE_SECTORS_EXT   0x34
#define ATA_CMD_WRITE_DMA_EXT       0x35
#define ATA_CMD_RECALIBRATE         0x10
#define ATA_CMD_STANDBY_IMMEDIATE   0xE0
#define ATA_CMD_SMART               0xB0

// SMART LBA signature
#define ATA_SMART_LBA1_SIGNATURE    0x4F
#define ATA_SMART_LBA2_SIGNATURE    0xC2

// SMART feature register values
#define ATA_FEATURE_SMART_READ_DATA     0xD0
#define ATA_FEATURE_SMART_RETURN_STATUS 0xDA

// SATA device signature
#define	SATA_DEVICE_SIGNATURE       0x00000101

// SATA device presence detected and PHY communication established
#define SATA_DEVICE_DETECTED        3

// Identify device structure
#pragma pack(push, 1)
typedef struct {
    // Word 0 (0x00)
    uint16_t word_00;
    // Word 1 (0x01)
    uint16_t word_01;
    // Word 2 (0x02)
    uint16_t word_02;
    // Word 3 (0x03)
    uint16_t word_03;
    // Word 4 (0x04)
    uint16_t word_04;
    // Word 5 (0x05)
    uint16_t word_05;
    // Word 6 (0x06)
    uint16_t word_06;
    // Word 7 (0x07)
    uint16_t word_07;
    // Word 8 (0x08)
    uint16_t word_08;
    // Word 9 (0x09)
    uint16_t word_09;
    // Word 10 (0x0a)
    uint8_t serial_number[20];
    // Word 20 (0x14)
    uint16_t word_14;
    // Word 21 (0x15)
    uint16_t word_15;
    // Word 22 (0x16)
    uint16_t word_16;
    // Word 23 (0x17)
    uint8_t firmware[8];
    // Word 27 (0x1b)
    uint8_t model[40];
    // Word 47 (0x2f)
    uint16_t max_rw_multiple_block_size:8;
    uint16_t word_2f_shall_be_80:8;
    // Word 48 (0x30)
    uint16_t word_30;
    // Word 49 (0x31)
    uint16_t word_31;
    // Word 50 (0x32)
    uint16_t word_32;
    // Word 51 (0x33)
    uint16_t word_33;
    // Word 52 (0x34)
    uint16_t word_34;
    // Word 53 (0x35)
    uint16_t word_35;
    // Word 54 (0x36)
    uint16_t word_36;
    // Word 55 (0x37)
    uint16_t word_37;
    // Word 56 (0x38)
    uint16_t word_38;
    // Word 57 (0x39)
    uint16_t word_39;
    // Word 58 (0x3a)
    uint16_t word_3a;
    // Word 59 (0x3b)
    uint16_t current_rw_multiple_block_size:8;
    uint16_t current_rw_multiple_block_size_is_valid:1;
    uint16_t word_3b_reserved:7;
    // Word 60 (0x3c)
    uint16_t word_3c;
    // Word 61 (0x3d)
    uint16_t word_3d;
    // Word 62 (0x3e)
    uint16_t word_3e;
    // Word 63 (0x3f)
    uint16_t multiword_dma_mode_0_is_supported:1;
    uint16_t multiword_dma_mode_1_is_supported:1;
    uint16_t multiword_dma_mode_2_is_supported:1;
    uint16_t word_3f_reserved_1:5;
    uint16_t multiword_dma_mode_0_is_selected:1;
    uint16_t multiword_dma_mode_1_is_selected:1;
    uint16_t multiword_dma_mode_2_is_selected:1;
    uint16_t word_3f_reserved_2:5;
    // Word 64 (0x40)
    uint16_t word_40;
    // Word 65 (0x41)
    uint16_t word_41;
    // Word 66 (0x42)
    uint16_t word_42;
    // Word 67 (0x43)
    uint16_t word_43;
    // Word 68 (0x44)
    uint16_t word_44;
    // Word 69 (0x45)
    uint16_t word_45;
    // Word 70 (0x46)
    uint16_t word_46;
    // Word 71 (0x47)
    uint16_t word_47;
    // Word 72 (0x48)
    uint16_t word_48;
    // Word 73 (0x49)
    uint16_t word_49;
    // Word 74 (0x4a)
    uint16_t word_4a;
    // Word 75 (0x4b)
    uint16_t word_4b;
    // Word 76 (0x4c)
    uint16_t word_4c;
    // Word 77 (0x4d)
    uint16_t word_4d;
    // Word 78 (0x4e)
    uint16_t word_4e;
    // Word 79 (0x4f)
    uint16_t word_4f;
    // Word 80 (0x50)
    uint16_t major_version;
    // Word 81 (0x51)
    uint16_t minor_version;
    // Word 82 (0x52)
    uint16_t word_52;
    // Word 83 (0x53)
    uint16_t word_53;
    // Word 84 (0x54)
    uint16_t word_54;
    // Word 85 (0x55)
    uint16_t word_55;
    // Word 86 (0x56)
    uint16_t word_56;
    // Word 87 (0x57)
    uint16_t word_57;
    // Word 88 (0x58)
    uint16_t ultra_dma_mode_0_is_supported:1;
    uint16_t ultra_dma_mode_1_is_supported:1;
    uint16_t ultra_dma_mode_2_is_supported:1;
    uint16_t ultra_dma_mode_3_is_supported:1;
    uint16_t ultra_dma_mode_4_is_supported:1;
    uint16_t ultra_dma_mode_5_is_supported:1;
    uint16_t ultra_dma_mode_6_is_supported:1;
    uint16_t word_58_reserved_1:1;
    uint16_t ultra_dma_mode_0_is_selected:1;
    uint16_t ultra_dma_mode_1_is_selected:1;
    uint16_t ultra_dma_mode_2_is_selected:1;
    uint16_t ultra_dma_mode_3_is_selected:1;
    uint16_t ultra_dma_mode_4_is_selected:1;
    uint16_t ultra_dma_mode_5_is_selected:1;
    uint16_t ultra_dma_mode_6_is_selected:1;
    uint16_t word_58_reserved_2:1;
    // Word 89 (0x59)
    uint16_t word_59;
    // Word 90 (0x5a)
    uint16_t word_5a;
    // Word 91 (0x5b)
    uint16_t word_5b;
    // Word 92 (0x5c)
    uint16_t word_5c;
    // Word 93 (0x5d)
    uint16_t word_5d;
    // Word 94 (0x5e)
    uint16_t word_5e;
    // Word 95 (0x5f)
    uint16_t word_5f;
    // Word 96 (0x60)
    uint16_t word_60;
    // Word 97 (0x61)
    uint16_t word_61;
    // Word 98 (0x62)
    uint16_t word_62;
    // Word 99 (0x63)
    uint16_t word_63;
    // Word 100 (0x64)
    uint64_t user_capacity;
    // Word 104 (0x68)
    uint16_t word_68;
    // Word 105 (0x69)
    uint16_t word_69;
    // Word 106 (0x6a)
    uint16_t ls_per_ps:4;
    uint16_t phy_ss_reserved:8;
    uint16_t device_ls_longer_than_256_words:1;
    uint16_t device_has_multiple_ls_per_ps:1;
    uint16_t phy_ss_shall_be_one:1;
    uint16_t phy_ss_shall_be_zero:1;
    // Word 107 (0x6b)
    uint16_t word_6b;
    // Word 108 (0x6c)
    uint16_t word_6c;
    // Word 109 (0x6d)
    uint16_t word_6d;
    // Word 110 (0x6e)
    uint16_t word_6e;
    // Word 111 (0x6f)
    uint16_t word_6f;
    // Word 112 (0x70)
    uint16_t word_70;
    // Word 113 (0x71)
    uint16_t word_71;
    // Word 114 (0x72)
    uint16_t word_72;
    // Word 115 (0x73)
    uint16_t word_73;
    // Word 116 (0x74)
    uint16_t word_74;
    // Word 117 (0x75)
    uint32_t words_per_logical_sector;
    // Word 119 (0x77)
    uint16_t word_77;
    // Word 120 (0x78)
    uint16_t word_78;
    // Word 121 (0x79)
    uint16_t word_79;
    // Word 122 (0x7a)
    uint16_t word_7a;
    // Word 123 (0x7b)
    uint16_t word_7b;
    // Word 124 (0x7c)
    uint16_t word_7c;
    // Word 125 (0x7d)
    uint16_t word_7d;
    // Word 126 (0x7e)
    uint16_t word_7e;
    // Word 127 (0x7f)
    uint16_t word_7f;
    // Word 128 (0x80)
    uint16_t word_80;
    // Word 129 (0x81)
    uint16_t word_81;
    // Word 130 (0x82)
    uint16_t word_82;
    // Word 131 (0x83)
    uint16_t word_83;
    // Word 132 (0x84)
    uint16_t word_84;
    // Word 133 (0x85)
    uint16_t word_85;
    // Word 134 (0x86)
    uint16_t word_86;
    // Word 135 (0x87)
    uint16_t word_87;
    // Word 136 (0x88)
    uint16_t word_88;
    // Word 137 (0x89)
    uint16_t word_89;
    // Word 138 (0x8a)
    uint16_t word_8a;
    // Word 139 (0x8b)
    uint16_t word_8b;
    // Word 140 (0x8c)
    uint16_t word_8c;
    // Word 141 (0x8d)
    uint16_t word_8d;
    // Word 142 (0x8e)
    uint16_t word_8e;
    // Word 143 (0x8f)
    uint16_t word_8f;
    // Word 144 (0x90)
    uint16_t word_90;
    // Word 145 (0x91)
    uint16_t word_91;
    // Word 146 (0x92)
    uint16_t word_92;
    // Word 147 (0x93)
    uint16_t word_93;
    // Word 148 (0x94)
    uint16_t word_94;
    // Word 149 (0x95)
    uint16_t word_95;
    // Word 150 (0x96)
    uint16_t word_96;
    // Word 151 (0x97)
    uint16_t word_97;
    // Word 152 (0x98)
    uint16_t word_98;
    // Word 153 (0x99)
    uint16_t word_99;
    // Word 154 (0x9a)
    uint16_t word_9a;
    // Word 155 (0x9b)
    uint16_t word_9b;
    // Word 156 (0x9c)
    uint16_t word_9c;
    // Word 157 (0x9d)
    uint16_t word_9d;
    // Word 158 (0x9e)
    uint16_t word_9e;
    // Word 159 (0x9f)
    uint16_t word_9f;
    // Word 160 (0xa0)
    uint16_t word_a0;
    // Word 161 (0xa1)
    uint16_t word_a1;
    // Word 162 (0xa2)
    uint16_t word_a2;
    // Word 163 (0xa3)
    uint16_t word_a3;
    // Word 164 (0xa4)
    uint16_t word_a4;
    // Word 165 (0xa5)
    uint16_t word_a5;
    // Word 166 (0xa6)
    uint16_t word_a6;
    // Word 167 (0xa7)
    uint16_t word_a7;
    // Word 168 (0xa8)
    uint16_t word_a8;
    // Word 169 (0xa9)
    uint16_t word_a9;
    // Word 170 (0xaa)
    uint16_t word_aa;
    // Word 171 (0xab)
    uint16_t word_ab;
    // Word 172 (0xac)
    uint16_t word_ac;
    // Word 173 (0xad)
    uint16_t word_ad;
    // Word 174 (0xae)
    uint16_t word_ae;
    // Word 175 (0xaf)
    uint16_t word_af;
    // Word 176 (0xb0)
    uint16_t word_b0;
    // Word 177 (0xb1)
    uint16_t word_b1;
    // Word 178 (0xb2)
    uint16_t word_b2;
    // Word 179 (0xb3)
    uint16_t word_b3;
    // Word 180 (0xb4)
    uint16_t word_b4;
    // Word 181 (0xb5)
    uint16_t word_b5;
    // Word 182 (0xb6)
    uint16_t word_b6;
    // Word 183 (0xb7)
    uint16_t word_b7;
    // Word 184 (0xb8)
    uint16_t word_b8;
    // Word 185 (0xb9)
    uint16_t word_b9;
    // Word 186 (0xba)
    uint16_t word_ba;
    // Word 187 (0xbb)
    uint16_t word_bb;
    // Word 188 (0xbc)
    uint16_t word_bc;
    // Word 189 (0xbd)
    uint16_t word_bd;
    // Word 190 (0xbe)
    uint16_t word_be;
    // Word 191 (0xbf)
    uint16_t word_bf;
    // Word 192 (0xc0)
    uint16_t word_c0;
    // Word 193 (0xc1)
    uint16_t word_c1;
    // Word 194 (0xc2)
    uint16_t word_c2;
    // Word 195 (0xc3)
    uint16_t word_c3;
    // Word 196 (0xc4)
    uint16_t word_c4;
    // Word 197 (0xc5)
    uint16_t word_c5;
    // Word 198 (0xc6)
    uint16_t word_c6;
    // Word 199 (0xc7)
    uint16_t word_c7;
    // Word 200 (0xc8)
    uint16_t word_c8;
    // Word 201 (0xc9)
    uint16_t word_c9;
    // Word 202 (0xca)
    uint16_t word_ca;
    // Word 203 (0xcb)
    uint16_t word_cb;
    // Word 204 (0xcc)
    uint16_t word_cc;
    // Word 205 (0xcd)
    uint16_t word_cd;
    // Word 206 (0xce)
    uint16_t word_ce;
    // Word 207 (0xcf)
    uint16_t word_cf;
    // Word 208 (0xd0)
    uint16_t word_d0;
    // Word 209 (0xd1)
    uint16_t word_d1;
    // Word 210 (0xd2)
    uint16_t word_d2;
    // Word 211 (0xd3)
    uint16_t word_d3;
    // Word 212 (0xd4)
    uint16_t word_d4;
    // Word 213 (0xd5)
    uint16_t word_d5;
    // Word 214 (0xd6)
    uint16_t word_d6;
    // Word 215 (0xd7)
    uint16_t word_d7;
    // Word 216 (0xd8)
    uint16_t word_d8;
    // Word 217 (0xd9)
    uint16_t media_rotation_rate;
    // Word 218 (0xda)
    uint16_t word_da;
    // Word 219 (0xdb)
    uint16_t word_db;
    // Word 220 (0xdc)
    uint16_t word_dc;
    // Word 221 (0xdd)
    uint16_t word_dd;
    // Word 222 (0xde)
    uint16_t transport_major_version;
    // Word 223 (0xdf)
    uint16_t transport_minor_version;
    // Word 224 (0xe0)
    uint16_t word_e0;
    // Word 225 (0xe1)
    uint16_t word_e1;
    // Word 226 (0xe2)
    uint16_t word_e2;
    // Word 227 (0xe3)
    uint16_t word_e3;
    // Word 228 (0xe4)
    uint16_t word_e4;
    // Word 229 (0xe5)
    uint16_t word_e5;
    // Word 230 (0xe6)
    uint64_t max_capacity;
    // Word 234 (0xea)
    uint16_t word_ea;
    // Word 235 (0xeb)
    uint16_t word_eb;
    // Word 236 (0xec)
    uint16_t word_ec;
    // Word 237 (0xed)
    uint16_t word_ed;
    // Word 238 (0xee)
    uint16_t word_ee;
    // Word 239 (0xef)
    uint16_t word_ef;
    // Word 240 (0xf0)
    uint16_t word_f0;
    // Word 241 (0xf1)
    uint16_t word_f1;
    // Word 242 (0xf2)
    uint16_t word_f2;
    // Word 243 (0xf3)
    uint16_t word_f3;
    // Word 244 (0xf4)
    uint16_t word_f4;
    // Word 245 (0xf5)
    uint16_t word_f5;
    // Word 246 (0xf6)
    uint16_t word_f6;
    // Word 247 (0xf7)
    uint16_t word_f7;
    // Word 248 (0xf8)
    uint16_t word_f8;
    // Word 249 (0xf9)
    uint16_t word_f9;
    // Word 250 (0xfa)
    uint16_t word_fa;
    // Word 251 (0xfb)
    uint16_t word_fb;
    // Word 252 (0xfc)
    uint16_t word_fc;
    // Word 253 (0xfd)
    uint16_t word_fd;
    // Word 254 (0xfe)
    uint16_t word_fe;
    // Word 255 (0xff)
    uint8_t checksum_validity_indicator;
    uint8_t checksum;
} ata_identify_device_data_t;
#pragma pack(pop)

static_assert(sizeof(ata_identify_device_data_t) == 512, "Incorrect size!");

#pragma pack(push, 1)
typedef struct {
    uint8_t id;
    uint16_t status;
    uint8_t nominal;
    uint8_t worst;
    uint8_t raw[7];
} ata_smart_attribute_t;
#pragma pack(pop)

static_assert(sizeof(ata_smart_attribute_t) == 12, "Incorrect size!");

#pragma pack(push, 1)
typedef struct {
    uint16_t version;
    ata_smart_attribute_t attribute[30];
    uint8_t reserved[150];
} ata_smart_data_t;
#pragma pack(pop)

static_assert(sizeof(ata_smart_data_t) == 512, "Incorrect size!");

#endif // QMINIAHCICOMMON_H
