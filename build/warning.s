
@{{BLOCK(warning)

@=======================================================================
@
@	warning, 16x16@4, 
@	Transparent color : 00,00,00
@	+ palette 16 entries, not compressed
@	+ 3 tiles (t|f reduced) not compressed
@	+ regular map (flat), not compressed, 2x2 
@	Total size: 32 + 96 + 8 = 136
@
@	Time-stamp: 2021-01-16, 18:52:53
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global warningTiles		@ 96 unsigned chars
warningTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x11111111,0x22222221,0x12222221,0x11222221,0x11122221,0x11122221,0x11122221,0x11222221
	.word 0x11222221,0x12222221,0x12222221,0x22222221,0x12222221,0x12222221,0x22222221,0x11111111

	.section .rodata
	.align	2
	.global warningMap		@ 8 unsigned chars
warningMap:
	.hword 0x0001,0x0401,0x0002,0x0402

	.section .rodata
	.align	2
	.global warningPal		@ 32 unsigned chars
warningPal:
	.hword 0x0000,0x7FFF,0x001C,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(warning)
