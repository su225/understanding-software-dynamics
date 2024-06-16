	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 4
	.globl	_swap_double                    ; -- Begin function swap_double
	.p2align	2
_swap_double:                           ; @swap_double
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #24]
	str	x1, [sp, #16]
	ldr	x8, [sp, #24]
	ldr	d0, [x8]
	str	d0, [sp, #8]
	ldr	x8, [sp, #16]
	ldr	d0, [x8]
	ldr	x8, [sp, #24]
	str	d0, [x8]
	ldr	d0, [sp, #8]
	ldr	x8, [sp, #16]
	str	d0, [x8]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_transpose_2x2_naive            ; -- Begin function transpose_2x2_naive
	.p2align	2
_transpose_2x2_naive:                   ; @transpose_2x2_naive
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #8]
	ldr	x9, [sp, #8]
	ldr	x8, [sp, #8]
	add	x0, x9, #8
	add	x1, x8, #16
	bl	_swap_double
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_transpose_2x2_arm_neon_simd    ; -- Begin function transpose_2x2_arm_neon_simd
	.p2align	2
_transpose_2x2_arm_neon_simd:           ; @transpose_2x2_arm_neon_simd
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #288
	.cfi_def_cfa_offset 288
	stp	x28, x27, [sp, #272]            ; 16-byte Folded Spill
	.cfi_offset w27, -8
	.cfi_offset w28, -16
	
	str	x0, [sp, #168]  ; store address of matrix a to sp+168
	ldr	x8, [sp, #168]  ; x8 <- address of matrix a from sp+168
	ldr	q0, [x8]        ; load first element a[0]
	
	str	q0, [sp, #128]  ; store a[0] in q0 to sp+128
	ldr	q0, [sp, #128]  ; load a[0] in sp+128 + q0
	
	str	q0, [sp, #112]
	ldr	q0, [sp, #112]
	str	q0, [sp, #144]
	ldr	x8, [sp, #168]
	ldr	q0, [x8, #16]
	str	q0, [sp, #80]
	ldr	q0, [sp, #80]
	str	q0, [sp, #64]
	ldr	q0, [sp, #64]
	str	q0, [sp, #96]
	ldr	q1, [sp, #144]
	ldr	q0, [sp, #96]
	str	q1, [sp, #208]
	str	q0, [sp, #192]
	ldr	q0, [sp, #208]
	ldr	q1, [sp, #192]
	zip1.2d	v0, v0, v1
	str	q0, [sp, #176]
	ldr	q0, [sp, #176]
	str	q0, [sp, #48]
	ldr	q1, [sp, #144]
	ldr	q0, [sp, #96]
	str	q1, [sp, #256]
	str	q0, [sp, #240]
	ldr	q0, [sp, #256]
	ldr	q1, [sp, #240]
	zip2.2d	v0, v0, v1
	str	q0, [sp, #224]
	ldr	q0, [sp, #224]
	str	q0, [sp, #32]
	ldr	q0, [sp, #48]
	str	q0, [sp, #16]
	ldr	x8, [sp, #168]
	ldr	q0, [sp, #16]
	str	q0, [x8]
	ldr	q0, [sp, #32]
	str	q0, [sp]
	ldr	x8, [sp, #168]
	ldr	q0, [sp]
	str	q0, [x8, #16]
	ldp	x28, x27, [sp, #272]            ; 16-byte Folded Reload
	add	sp, sp, #288
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #160
	.cfi_def_cfa_offset 160
	stp	x29, x30, [sp, #144]            ; 16-byte Folded Spill
	add	x29, sp, #144
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	str	wzr, [sp, #60]
	adrp	x8, l___const.main.matrix1@PAGE
	add	x8, x8, l___const.main.matrix1@PAGEOFF
	ldr	q0, [x8]
	sub	x0, x29, #48
	stur	q0, [x29, #-48]
	ldr	q0, [x8, #16]
	stur	q0, [x29, #-32]
	adrp	x8, l___const.main.matrix2@PAGE
	add	x8, x8, l___const.main.matrix2@PAGEOFF
	ldr	q0, [x8]
	add	x9, sp, #64
	str	x9, [sp, #40]                   ; 8-byte Folded Spill
	str	q0, [sp, #64]
	ldr	q0, [x8, #16]
	str	q0, [sp, #80]
	bl	_transpose_2x2_naive
	ldr	x0, [sp, #40]                   ; 8-byte Folded Reload
	bl	_transpose_2x2_arm_neon_simd
	ldur	d3, [x29, #-48]
	ldur	d2, [x29, #-40]
	ldur	d1, [x29, #-32]
	ldur	d0, [x29, #-24]
	mov	x8, sp
	str	d3, [x8]
	str	d2, [x8, #8]
	str	d1, [x8, #16]
	str	d0, [x8, #24]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	str	x0, [sp, #48]                   ; 8-byte Folded Spill
	bl	_printf
	ldr	x0, [sp, #48]                   ; 8-byte Folded Reload
	ldr	d3, [sp, #64]
	ldr	d2, [sp, #72]
	ldr	d1, [sp, #80]
	ldr	d0, [sp, #88]
	mov	x8, sp
	str	d3, [x8]
	str	d2, [x8, #8]
	str	d1, [x8, #16]
	str	d0, [x8, #24]
	bl	_printf
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB3_2
	b	LBB3_1
LBB3_1:
	bl	___stack_chk_fail
LBB3_2:
	mov	w0, #0
	ldp	x29, x30, [sp, #144]            ; 16-byte Folded Reload
	add	sp, sp, #160
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__const
	.p2align	3, 0x0                          ; @__const.main.matrix1
l___const.main.matrix1:
	.quad	0x0000000000000000              ; double 0
	.quad	0x3ff0000000000000              ; double 1
	.quad	0x4000000000000000              ; double 2
	.quad	0x4008000000000000              ; double 3

	.p2align	3, 0x0                          ; @__const.main.matrix2
l___const.main.matrix2:
	.quad	0x0000000000000000              ; double 0
	.quad	0x3ff0000000000000              ; double 1
	.quad	0x4000000000000000              ; double 2
	.quad	0x4008000000000000              ; double 3

	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%lf %lf %lf %lf\n"

.subsections_via_symbols
