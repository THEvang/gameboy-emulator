#pragma once

#include <stdint.h>

int gb_rlc(uint8_t* r, uint8_t* flags);
int gb_rrc(uint8_t* r, uint8_t* flags);
int gb_rl(uint8_t* r, uint8_t* flags);
int gb_slr(uint8_t* r, uint8_t* flags);
int gb_rr(uint8_t* r, uint8_t* flags);
int gb_sla(uint8_t* r, uint8_t* flags);
int gb_sra(uint8_t* r, uint8_t* flags);
int gb_swap(uint8_t*, uint8_t*);
int gb_bit(uint8_t, int, uint8_t*);
int gb_res(uint8_t*, int);
int gb_set(uint8_t*, int);