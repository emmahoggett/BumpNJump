
@{{BLOCK(carred)

@=======================================================================
@
@	carred, 16x16@4, 
@	Transparent color : 00,FF,00
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2021-01-18, 14:41:46
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global carredTiles		@ 128 unsigned chars
carredTiles:
	.word 0x11120000,0x32321000,0x33233222,0x33133212,0x33233222,0x33333222,0x22223000,0x11123000
	.word 0x00022111,0x00212323,0x22233233,0x21233133,0x22233233,0x22233333,0x22232222,0x00232111
	.word 0x11123000,0x22223222,0x21123212,0x22223222,0x22233222,0x33331000,0x11212000,0x22220000
	.word 0x00232111,0x22232222,0x21232112,0x22232222,0x22233222,0x22213333,0x00221211,0x00022222

	.section .rodata
	.align	2
	.global carredPal		@ 32 unsigned chars
carredPal:
	.hword 0x03E0,0x67F6,0x0000,0x2C1C,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(carred)
