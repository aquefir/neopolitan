/****************************************************************************\
 *                               unilib himem                               *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC__UNI_GBABIOS_H
#define INC__UNI_GBABIOS_H

#ifdef CFG_GBA

#include <uni/types/int.h>

void _bios_soft_reset( void );
void _bios_register_ram_reset( u32 );
void _bios_halt( void );
void _bios_stop( void );
void _bios_intr_wait( u32, u32 );
void _bios_vblank_intr_wait( void );
s32 _bios_div( s32, s32 );
s32 _bios_div_arm( s32, s32 );
u32 _bios_sqrt( u32 );
s16 _bios_arc_tan( s16 );
s16 _bios_arc_tan2( s16, s16 );
void _bios_cpu_set( const void *, void *, u32 );
void _bios_cpu_fast_set( const void *, void *, u32 );
void _bios_bg_affine_set( const void *, void *, s32 );
void _bios_obj_affine_set( const void *, void *, s32, s32 );
void _bios_bit_unpack( const void *, void *, void * );
void _bios_lzss_decomp_wram( const void *, void * );
void _bios_lzss_decomp_vram( const void *, void * );
void _bios_huff_decomp( const void *, void * );
void _bios_rl_decomp_wram( const void *, void * );
void _bios_rl_decomp_vram( const void *, void * );
void _bios_diff_8bit_unfilter_wram( const void *, void * );
void _bios_diff_8bit_unfilter_vram( const void *, void * );
void _bios_diff_16bit_unfilter( const void *, void * );
void _bios_sound_bias( u32 );
u32 _bios_midi_key_to_freq( void *, u8, u8 );
s32 _bios_multi_boot( void *, u32 );

#endif

#endif /* INC__UNI_GBABIOS_H */
