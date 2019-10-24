	.arch armv7-a
	.eabi_attribute 27, 3	@ Tag_ABI_HardFP_use
	.eabi_attribute 28, 1	@ Tag_ABI_VFP_args
	.fpu vfpv3-d16
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 6	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
	.file	"asm-offsets.c"
@ GNU C (crosstool-NG linaro-1.13.1-4.7-2013.04-20130415 - Linaro GCC 2013.04) version 4.7.3 20130328 (prerelease) (arm-linux-gnueabihf)
@	compiled by GNU C version 4.1.3 20080704 (prerelease) (Ubuntu 4.1.2-27ubuntu1), GMP version 5.0.2, MPFR version 3.1.0, MPC version 0.9
@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed:  -nostdinc -nostdinc -I include -I . -I include
@ -I include -I . -I ./lib/libfdt -I arch/arm/include/
@ -I arch/arm/vexpress/include/ -imultiarch arm-linux-gnueabihf
@ -iprefix /opt/toolchains/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/../lib/gcc/arm-linux-gnueabihf/4.7.3/
@ -isysroot /opt/toolchains/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/bin/../arm-linux-gnueabihf/libc
@ -D __KERNEL__ -D __SO3__ -D __KERNEL__ -D __SO3__
@ -include include/generated/autoconf.h
@ -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include
@ -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include
@ -MD arch/arm/.asm-offsets.s.d arch/arm/asm-offsets.c -marm
@ -mno-thumb-interwork -march=armv7-a -mtune=cortex-a9 -mfloat-abi=hard
@ -mfpu=vfpv3-d16 -mtls-dialect=gnu -auxbase-strip arch/arm/asm-offsets.s
@ -g -O0 -Wall -Wstrict-prototypes -fno-common -fno-builtin -ffreestanding
@ -fverbose-asm
@ options enabled:  -fauto-inc-dec -fbranch-count-reg -fdebug-types-section
@ -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
@ -feliminate-unused-debug-types -ffunction-cse -fgcse-lm -fgnu-runtime
@ -fident -finline-atomics -fira-share-save-slots -fira-share-spill-slots
@ -fivopts -fkeep-static-consts -fleading-underscore -fmath-errno
@ -fmerge-debug-strings -fmove-loop-invariants -fpeephole
@ -fprefetch-loop-arrays -freg-struct-return
@ -fsched-critical-path-heuristic -fsched-dep-count-heuristic
@ -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
@ -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
@ -fsched-stalled-insns-dep -fshow-column -fsigned-zeros
@ -fsplit-ivs-in-unroller -fstrict-volatile-bitfields -ftrapping-math
@ -ftree-coalesce-vars -ftree-cselim -ftree-forwprop -ftree-loop-if-convert
@ -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
@ -ftree-parallelize-loops= -ftree-phiprop -ftree-pta -ftree-reassoc
@ -ftree-scev-cprop -ftree-slp-vectorize -ftree-vect-loop-version
@ -funit-at-a-time -fverbose-asm -fzero-initialized-in-bss -marm -mglibc
@ -mlittle-endian -msched-prolog -munaligned-access
@ -mvectorize-with-neon-quad

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.global	main
	.type	main, %function
main:
.LFB69:
	.file 1 "arch/arm/asm-offsets.c"
	.loc 1 54 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!	@,
.LCFI0:
	.cfi_def_cfa_offset 4
	.cfi_offset 11, -4
	add	fp, sp, #0	@,,
.LCFI1:
	.cfi_def_cfa_register 11
	.loc 1 55 0
#APP
@ 55 "arch/arm/asm-offsets.c" 1
	
->
@ 0 "" 2
	.loc 1 57 0
@ 57 "arch/arm/asm-offsets.c" 1
	
->OFFSET_TCB_CPU_REGS #124 offsetof(tcb_t, cpu_regs)	@
@ 0 "" 2
	.loc 1 59 0
@ 59 "arch/arm/asm-offsets.c" 1
	
->
@ 0 "" 2
	.loc 1 61 0
@ 61 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R0 #0 offsetof(cpu_regs_t, r0)	@
@ 0 "" 2
	.loc 1 62 0
@ 62 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R1 #4 offsetof(cpu_regs_t, r1)	@
@ 0 "" 2
	.loc 1 63 0
@ 63 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R2 #8 offsetof(cpu_regs_t, r2)	@
@ 0 "" 2
	.loc 1 64 0
@ 64 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R3 #12 offsetof(cpu_regs_t, r3)	@
@ 0 "" 2
	.loc 1 65 0
@ 65 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R4 #16 offsetof(cpu_regs_t, r4)	@
@ 0 "" 2
	.loc 1 66 0
@ 66 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R5 #20 offsetof(cpu_regs_t, r5)	@
@ 0 "" 2
	.loc 1 67 0
@ 67 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R6 #24 offsetof(cpu_regs_t, r6)	@
@ 0 "" 2
	.loc 1 68 0
@ 68 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R7 #28 offsetof(cpu_regs_t, r7)	@
@ 0 "" 2
	.loc 1 69 0
@ 69 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R8 #32 offsetof(cpu_regs_t, r8)	@
@ 0 "" 2
	.loc 1 70 0
@ 70 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R9 #36 offsetof(cpu_regs_t, r9)	@
@ 0 "" 2
	.loc 1 71 0
@ 71 "arch/arm/asm-offsets.c" 1
	
->OFFSET_R10 #40 offsetof(cpu_regs_t, r10)	@
@ 0 "" 2
	.loc 1 72 0
@ 72 "arch/arm/asm-offsets.c" 1
	
->OFFSET_FP #44 offsetof(cpu_regs_t, fp)	@
@ 0 "" 2
	.loc 1 73 0
@ 73 "arch/arm/asm-offsets.c" 1
	
->OFFSET_IP #48 offsetof(cpu_regs_t, ip)	@
@ 0 "" 2
	.loc 1 74 0
@ 74 "arch/arm/asm-offsets.c" 1
	
->OFFSET_SP #52 offsetof(cpu_regs_t, sp)	@
@ 0 "" 2
	.loc 1 75 0
@ 75 "arch/arm/asm-offsets.c" 1
	
->OFFSET_LR #56 offsetof(cpu_regs_t, lr)	@
@ 0 "" 2
	.loc 1 76 0
@ 76 "arch/arm/asm-offsets.c" 1
	
->OFFSET_PC #60 offsetof(cpu_regs_t, pc)	@
@ 0 "" 2
	.loc 1 77 0
@ 77 "arch/arm/asm-offsets.c" 1
	
->OFFSET_PSR #64 offsetof(cpu_regs_t, psr)	@
@ 0 "" 2
	.loc 1 79 0
@ 79 "arch/arm/asm-offsets.c" 1
	
->
@ 0 "" 2
	.loc 1 81 0
	mov	r3, #0	@ D.4528,
	.loc 1 82 0
	mov	r0, r3	@, <retval>
	add	sp, fp, #0	@,,
	ldmfd	sp!, {fp}
	bx	lr
	.cfi_endproc
.LFE69:
	.size	main, .-main
.Letext0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x89
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF10
	.byte	0x1
	.4byte	.LASF11
	.4byte	.LASF12
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF9
	.uleb128 0x4
	.byte	0x1
	.4byte	.LASF13
	.byte	0x1
	.byte	0x35
	.byte	0x1
	.4byte	0x41
	.4byte	.LFB69
	.4byte	.LFE69
	.4byte	.LLST0
	.byte	0x1
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB69-.Ltext0
	.4byte	.LCFI0-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0-.Ltext0
	.4byte	.LCFI1-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI1-.Ltext0
	.4byte	.LFE69-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF4:
	.ascii	"unsigned int\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF12:
	.ascii	"/home/reds/Desktop/SYE/sye17_labo05/so3\000"
.LASF1:
	.ascii	"signed char\000"
.LASF0:
	.ascii	"short unsigned int\000"
.LASF3:
	.ascii	"short int\000"
.LASF13:
	.ascii	"main\000"
.LASF6:
	.ascii	"long long unsigned int\000"
.LASF11:
	.ascii	"arch/arm/asm-offsets.c\000"
.LASF2:
	.ascii	"unsigned char\000"
.LASF8:
	.ascii	"sizetype\000"
.LASF10:
	.ascii	"GNU C 4.7.3 20130328 (prerelease)\000"
.LASF9:
	.ascii	"char\000"
.LASF5:
	.ascii	"long long int\000"
	.ident	"GCC: (crosstool-NG linaro-1.13.1-4.7-2013.04-20130415 - Linaro GCC 2013.04) 4.7.3 20130328 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
