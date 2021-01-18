
@{{BLOCK(carpink)

@=======================================================================
@
@	carpink, 16x16@4, 
@	Transparent color : 00,FF,00
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2021-01-17, 16:41:38
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global carpinkTiles		@ 128 unsigned chars
carpinkTiles:
	.word 0x33223000,0x11331300,0x11111100,0x11111120,0x11111120,0x33333120,0x33331120,0x22221100
	.word 0x00023223,0x00231331,0x00211111,0x02211111,0x02211111,0x02213333,0x02211333,0x00211222
	.word 0x22221100,0x23331100,0x22221120,0x11111120,0x11111120,0x11111120,0x11111000,0x22121000
	.word 0x00211222,0x00211333,0x02211222,0x02211111,0x02211111,0x02211111,0x00221111,0x00021212

	.section .rodata
	.align	2
	.global carpinkPal		@ 32 unsigned chars
carpinkPal:
	.hword 0x03E0,0x5C17,0x0000,0x7F1F,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(carpink)
