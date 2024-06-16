	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 4
	.globl	_swap_double                    ; -- Begin function swap_double
	.p2align	2
_swap_double:                           ; @swap_double
	.cfi_startproc
; %bb.0:
	ldr	d0, [x0]
	ldr	d1, [x1]
	str	d1, [x0]
	str	d0, [x1]
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_transpose_2x2_naive            ; -- Begin function transpose_2x2_naive
	.p2align	2
_transpose_2x2_naive:                   ; @transpose_2x2_naive
	.cfi_startproc
; %bb.0:
	ldp	d0, d1, [x0, #8]
	str	d1, [x0, #8]
	str	d0, [x0, #16]
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_transpose_2x2_arm_neon_simd    ; -- Begin function transpose_2x2_arm_neon_simd
	.p2align	2
_transpose_2x2_arm_neon_simd:           ; @transpose_2x2_arm_neon_simd
	.cfi_startproc
; %bb.0:
	ldp	q0, q1, [x0]
	zip1.2d	v2, v0, v1
	zip2.2d	v0, v0, v1
	stp	q2, q0, [x0]
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	.cfi_def_cfa_offset 80
	stp	x22, x21, [sp, #32]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #48]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	mov	x20, #4613937818241073152
	mov	x21, #4607182418800017408
	stp	x21, x20, [sp, #16]
	mov	x22, #4611686018427387904
	stp	xzr, x22, [sp]
Lloh0:
	adrp	x19, l_.str@PAGE
Lloh1:
	add	x19, x19, l_.str@PAGEOFF
	mov	x0, x19
	bl	_printf
	stp	x21, x20, [sp, #16]
	stp	xzr, x22, [sp]
	mov	x0, x19
	bl	_printf
	mov	w0, #0
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%lf %lf %lf %lf\n"

.subsections_via_symbols
