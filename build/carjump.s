
@{{BLOCK(carjump)

@=======================================================================
@
@	carjump, 32x32@4, 
@	Transparent color : 00,FF,00
@	+ palette 16 entries, not compressed
@	+ 16 tiles not compressed
@	Total size: 32 + 512 = 544
@
@	Time-stamp: 2021-01-16, 18:52:52
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global carjumpTiles		@ 512 unsigned chars
carjumpTiles:
	.word 0x00000000,0x40000000,0x44000000,0x14000000,0x12220000,0x12442000,0x12442000,0x12222000
	.word 0x33333244,0x22222224,0x11111111,0x12112111,0x12112111,0x11111111,0x11111111,0x11112111
	.word 0x44233333,0x42222222,0x11111111,0x11121121,0x11121121,0x11111111,0x11111111,0x11121111
	.word 0x00000000,0x00000004,0x00000044,0x00000041,0x00002221,0x00024421,0x00024421,0x00022221
	.word 0x12442000,0x12222000,0x12222000,0x12222000,0x12220000,0x10000000,0x10000000,0x10000000
	.word 0x11114111,0x11112111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x22222211
	.word 0x11141111,0x11121111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11222222
	.word 0x00024421,0x00022221,0x00022221,0x00022221,0x00002221,0x00000001,0x00000001,0x00000001

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x22000000,0x22200000,0x24420000
	.word 0x33333211,0x33333211,0x33333211,0x33332211,0x22222111,0x33321111,0x35221111,0x22211111
	.word 0x11233333,0x11233333,0x11233333,0x11223333,0x11122222,0x11112332,0x11112232,0x11111222
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000222,0x00002222,0x00002442
	.word 0x22220000,0x24420000,0x24420000,0x22220000,0x22000000,0x00000000,0x00000000,0x00000000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111110,0x22222100,0x33332000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x31111111,0x33122222,0x03323333
	.word 0x00002222,0x00002442,0x00002442,0x00002222,0x00000022,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global carjumpPal		@ 32 unsigned chars
carjumpPal:
	.hword 0x03E0,0x2C1C,0x0000,0x67F6,0x7FFF,0x73F7,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(carjump)
