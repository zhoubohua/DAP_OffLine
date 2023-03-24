/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "flash_blob.h"

static const uint32_t flash_code[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x03004601, 0x28200E00, 0x0940D302, 0xE0051D00, 0xD3022810, 0x1CC00900, 0x0880E000, 0xD50102C9,
    0x43082110, 0x48424770, 0x60414940, 0x60414941, 0x60012100, 0x22F068C1, 0x60C14311, 0x06806940,
    0x483ED406, 0x6001493C, 0x60412106, 0x6081493C, 0x47702000, 0x69014836, 0x43110542, 0x20006101,
    0xB5104770, 0x69014832, 0x43212404, 0x69016101, 0x431103A2, 0x49336101, 0xE0004A30, 0x68C36011,
    0xD4FB03DB, 0x43A16901, 0x20006101, 0xB530BD10, 0xFFB6F7FF, 0x68CA4926, 0x431A23F0, 0x240260CA,
    0x690A610C, 0x0E0006C0, 0x610A4302, 0x03E26908, 0x61084310, 0x4A214823, 0x6010E000, 0x03ED68CD,
    0x6908D4FB, 0x610843A0, 0x060068C8, 0xD0030F00, 0x431868C8, 0x200160C8, 0xB570BD30, 0x1CC94D14,
    0x68EB0889, 0x26F00089, 0x60EB4333, 0x612B2300, 0xE0174B15, 0x431C692C, 0x6814612C, 0x68EC6004,
    0xD4FC03E4, 0x0864692C, 0x612C0064, 0x062468EC, 0xD0040F24, 0x433068E8, 0x200160E8, 0x1D00BD70,
    0x1F091D12, 0xD1E52900, 0xBD702000, 0x45670123, 0x40023C00, 0xCDEF89AB, 0x00005555, 0x40003000,
    0x00000FFF, 0x0000AAAA, 0x00000201, 0x00000000
};

const program_target_t flash_algo = {
    0x20000047,  // Init
    0x20000075,  // UnInit
    0x20000083,  // EraseChip
    0x200000AF,  // EraseSector
    0x200000FB,  // ProgramPage

    // BKPT : start of blob + 1
    // RSB  : address to access global/static data
    // RSP  : stack pointer
    {
        0x20000001,
        0x20000C00,
        0x20001000
    },

    0x20000400,  // mem buffer location
    0x20000000,  // location to write prog_blob in target RAM
    sizeof(flash_code),  // prog_blob size
    flash_code,  // address of prog_blob
    0x00000400,  // ram_to_flash_bytes_to_be_written
};
