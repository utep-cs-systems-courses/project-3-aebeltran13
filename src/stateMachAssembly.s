	.arch msp430g2553

	.p2align 1,0
JT:
	.word default
	.word case1
	.word case2
	.word case3
	.word case4

	.text
	.global state_advance
state_advance:
	cmp #5, &switch_state_changed
	jhs default
	mov &switch_state_changed, r12
	add r12, r12
	mov JT(r12), r0
case1:
	call #drawMoon 		;calls draw moon method
	call #led_dim		;calls dim method
	add #1, redrawScreen
	jmp end
case2:
	call #songBGR
	call #song
	add #1, redrawScreen
case3:
	call #fillTeehee
	call #siren_song
	add #1, redrawScreen
case4:
	call #drawFace
	add #1, redrawScreen
default:
	jmp end
end:
	ret
