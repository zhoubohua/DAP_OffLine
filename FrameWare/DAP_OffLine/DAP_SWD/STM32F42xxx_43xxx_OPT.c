/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "flash_blob.h"

static const uint32_t flash_code[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x49324833, 0x49336081, 0x68C16081, 0x431122F0, 0x694060C1, 0xD4060680, 0x492F4830, 0x21066001,
    0x492F6041, 0x20006081, 0x48294770, 0x22016941, 0x61414311, 0x47702000, 0x68C24825, 0x430A21F0,
    0x4A2860C2, 0x4A286182, 0x69426142, 0x431A2302, 0x68C26142, 0x0F120612, 0x68C2D004, 0x60C2430A,
    0x47702001, 0x47702000, 0x47702000, 0x4818B510, 0x68C4CA06, 0x431C23F0, 0x4C1A60C4, 0x61824022,
    0x40114A1A, 0x61411C89, 0x03C968C1, 0x68C1D4FC, 0x0F090609, 0x68C1D004, 0x60C14319, 0xBD102001,
    0xBD102000, 0x4E0AB570, 0x4C106813, 0x69756852, 0x40254023, 0xD10642AB, 0x69B44B0A, 0x401C401A,
    0xD00142A2, 0xBD701C40, 0xBD701840, 0x08192A3B, 0x40023C00, 0x4C5D6E7F, 0x00005555, 0x40003000,
    0x00000FFF, 0x0FFF0000, 0x0FFFAAEC, 0xCFFFFFFC, 0x00000000
};

const program_target_t flash_algo = {
    0x20000021,  // Init
    0x2000004B,  // UnInit
    0x20000059,  // EraseChip
    0x20000089,  // EraseSector
    0x2000008D,  // ProgramPage

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
    0x00000008,  // ram_to_flash_bytes_to_be_written
};
