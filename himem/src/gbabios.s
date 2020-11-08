@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@                               unilib himem                               @@
@@                                                                          @@
@@                      Copyright © 2019-2020 Aquefir                       @@
@@                       Released under BSD-2-Clause.                       @@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.file "src/gbabios.s"
.ident "AS: (devkitARM release 46) 2.27"

.section .text
.balign  2, 0
.code    16

@ === SoftReset [00h] =================================================
@ DECL: void _bios_soft_reset();
@ DESC:
.balign 2, 0
.globl _bios_soft_reset
.code 16

_bios_soft_reset:
	SWI     0x00
	BX      LR

@ === RegisterRamReset [01h] ==========================================
@ DECL: void _bios_register_ram_reset(u32 flags);
@ DESC:
.balign 2, 0
.globl _bios_register_ram_reset
.code 16

_bios_register_ram_reset:
	SWI     0x01
	BX      LR

@ === Halt [02h] ======================================================
@ DECL: void _bios_halt();
@ DESC:
.balign 2, 0
.globl _bios_halt
.code 16

_bios_halt:
	SWI     0x02
	BX      LR

@ === Stop [03h] ======================================================
@ DECL: void _bios_stop();
@ DESC:
.balign 2, 0
.globl _bios_stop
.code 16

_bios_stop:
	SWI     0x03
	BX      LR

@ === IntrWait [04h] ==================================================
@ DECL: void _bios_intr_wait(u32 flagClear, u32 irq);
@ DESC:
.balign 2, 0
.globl _bios_intr_wait
.code 16

_bios_intr_wait:
	SWI     0x04
	BX      LR

@ === VBlankIntrWait [05h] ============================================
@ DECL: void _bios_vblank_intr_wait();
@ DESC:
.balign 2, 0
.globl _bios_vblank_intr_wait
.code 16

_bios_vblank_intr_wait:
	SWI     0x05
	BX      LR

@ === Div [06h] =======================================================
@ DECL: s32 _bios_div(s32 num, s32 den);
@ DESC:
.balign 2, 0
.globl _bios_div
.code 16

_bios_div:
	SWI     0x06
	BX      LR

@ === DivArm [07h] ====================================================
@ DECL: s32 _bios_div_arm(s32 den, s32 num);
@ DESC:
.balign 2, 0
.globl _bios_div_arm
.code 16

_bios_div_arm:
	SWI     0x07
	BX      LR

@ === Sqrt [08h] ======================================================
@ DECL: u32 _bios_sqrt(u32 num);
@ DESC:
.balign 2, 0
.globl _bios_sqrt
.code 16

_bios_sqrt:
	SWI     0x08
	BX      LR

@ === ArcTan [09h] ====================================================
@ DECL: s16 _bios_arc_tan(s16 dydx);
@ DESC:
.balign 2, 0
.globl _bios_arc_tan
.code 16

_bios_arc_tan:
	SWI     0x09
	BX      LR

@ === ArcTan2 [0Ah] ===================================================
@ DECL: s16 _bios_arc_tan2(s16 x, s16 y);
@ DESC:
.balign 2, 0
.globl _bios_arc_tan2
.code 16

_bios_arc_tan2:
	SWI     0x0A
	BX      LR

@ === CpuSet [0Bh] ====================================================
@ DECL: void _bios_cpu_set(const void *src, void *dst, u32 mode);
@ DESC:
.balign 2, 0
.globl _bios_cpu_set
.code 16

_bios_cpu_set:
	SWI     0x0B
	BX      LR

@ === CpuFastSet [0Ch] ================================================
@ DECL: void _bios_cpu_fast_set(const void *src, void *dst, u32 mode);
@ DESC:
.balign 2, 0
.globl _bios_cpu_fast_set
.code 16

_bios_cpu_fast_set:
	SWI     0x0C
	BX      LR

@ === BgAffineSet [0Eh] ===============================================
@ DECL: void _bios_bg_affine_set(const BgAffineSource *src, BgAffineDest *dst, s32 num);
@ DESC:
.balign 2, 0
.globl _bios_bg_affine_set
.code 16

_bios_bg_affine_set:
	SWI     0x0E
	BX      LR

@ === ObjAffineSet [0Fh] ==============================================
@ DECL: void _bios_obj_affine_set(const ObjAffineSource *src, void *dst, s32 num, s32 offset);
@ DESC:
.balign 2, 0
.globl _bios_obj_affine_set
.code 16

_bios_obj_affine_set:
	SWI     0x0F
	BX      LR

@ === BitUnPack [10h] =================================================
@ DECL: void _bios_bit_unpack(const void *src, void *dst, BUP *bup);
@ DESC:
.balign 2, 0
.globl _bios_bit_unpack
.code 16

_bios_bit_unpack:
	SWI     0x10
	BX      LR

@ === LZ77UnCompWram [11h] ============================================
@ DECL: void _bios_lzss_decomp_wram(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_lzss_decomp_wram
.code 16

_bios_lzss_decomp_wram:
	SWI     0x11
	BX      LR

@ === LZ77UnCompVram [12h] ============================================
@ DECL: void _bios_lzss_decomp_vram(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_lzss_decomp_vram
.code 16

_bios_lzss_decomp_vram:
	SWI     0x12
	BX      LR

@ === HuffUnComp [13h] ================================================
@ DECL: void _bios_huff_decomp(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_huff_decomp
.code 16

_bios_huff_decomp:
	SWI     0x13
	BX      LR

@ === RLUnCompWram [14h] ==============================================
@ DECL: void _bios_rl_decomp_wram(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_rl_decomp_wram
.code 16

_bios_rl_decomp_wram:
	SWI     0x14
	BX      LR

@ === RLUnCompVram [15h] ==============================================
@ DECL: void _bios_rl_decomp_vram(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_rl_decomp_vram
.code 16

_bios_rl_decomp_vram:
	SWI     0x15
	BX      LR

@ === Diff8bitUnFilterWram [16h] ======================================
@ DECL: void _bios_diff_8bit_unfilter_wram(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_diff_8bit_unfilter_wram
.code 16

_bios_diff_8bit_unfilter_wram:
	SWI     0x16
	BX      LR

@ === Diff8bitUnFilterVram [17h] ======================================
@ DECL: void _bios_diff_8bit_unfilter_vram(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_diff_8bit_unfilter_vram
.code 16

_bios_diff_8bit_unfilter_vram:
	SWI     0x17
	BX      LR

@ === Diff16bitUnFilter [18h] =========================================
@ DECL: void _bios_diff_16bit_unfilter(const void *src, void *dst);
@ DESC:
.balign 2, 0
.globl _bios_diff_16bit_unfilter
.code 16

_bios_diff_16bit_unfilter:
	SWI     0x18
	BX      LR

@ === SoundBias [19h] =================================================
@ DECL: void _bios_sound_bias(u32 bias);
@ DESC:
.balign 2, 0
.globl _bios_sound_bias
.code 16

_bios_sound_bias:
	SWI     0x19
	BX      LR

@ === SoundDriverInit [1Ah] ===========================================
@ DECL: void _bios_sound_driver_init(void *src);
@ DESC:
@    .balign 2
@    .globl _bios_sound_driver_init
@    .code 16

@_bios_sound_driver_init:
@    SWI     0x1A
@    BX      LR

@ === SoundDriverMode [1Bh] ===========================================
@ DECL: void _bios_sound_driver_mode(u32 mode);
@ DESC:
@    .balign 2
@    .globl _bios_sound_driver_mode
@    .code 16

@_bios_sound_driver_mode:
@    SWI     0x1B
@    BX      LR

@ === SoundDriverMain [1Ch] ===========================================
@ DECL: void _bios_sound_driver_main();
@ DESC:
@    .balign 2
@    .globl _bios_sound_driver_main
@    .code 16

@_bios_sound_driver_main:
@    SWI     0x1C
@    BX      LR

@ === SoundDriverVSync [1Dh] ==========================================
@ DECL: void _bios_sound_driver_vsync();
@ DESC:
@    .balign 2
@    .globl _bios_sound_driver_vsync
@    .code 16

@_bios_sound_driver_vsync:
@    SWI     0x1D
@    BX      LR

@ === SoundChannelClear [1Eh] =========================================
@ DECL: void _bios_sound_channel_clear();
@ DESC:
@    .balign 2
@    .globl _bios_sound_channel_clear
@    .code 16

@_bios_sound_channel_clear:
@    SWI     0x1E
@    BX      LR

@ === MidiKey2Freq [1Fh] ==============================================
@ DECL: u32 _bios_midi_key_to_freq(void *wa, u8 mk, u8 fp);
@ DESC:
.balign 2, 0
.globl _bios_midi_key_to_freq
.code 16

_bios_midi_key_to_freq:
	SWI     0x1F
	BX      LR

@ === MultiBoot [25h] =================================================
@ DECL: s32 _bios_multi_boot(MultiBootParam* mb, u32 mode);
@ DESC:
.balign 2, 0
.globl _bios_multi_boot
.code 16

_bios_multi_boot:
	SWI     0x25
	BX      LR

@ === SoundDriverVSyncOff [28h] =======================================
@ DECL: void _bios_sound_driver_vsync_off();
@ DESC:
@    .balign 2
@    .globl _bios_sound_driver_vsync_off
@    .code 16

@_bios_sound_driver_vsync_off:
@    SWI     0x28
@    BX      LR

@ === SoundDriverVSyncOn [29h] ========================================
@ DECL: void _bios_sound_driver_vsync_on();
@ DESC:
@    .balign 2
@    .globl _bios_sound_driver_vsync_on
@    .code 16

@_bios_sound_driver_vsync_on:
@    SWI     0x29
@    BX      LR
