
//{{BLOCK(road)

//======================================================================
//
//	road, 256x512@4, 
//	+ palette 16 entries, not compressed
//	+ 207 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x64 
//	Total size: 32 + 6624 + 4096 = 10752
//
//	Time-stamp: 2021-01-18, 10:50:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROAD_H
#define GRIT_ROAD_H

#define roadTilesLen 6624
extern const unsigned int roadTiles[1656];

#define roadMapLen 4096
extern const unsigned short roadMap[2048];

#define roadPalLen 32
extern const unsigned short roadPal[16];

#endif // GRIT_ROAD_H

//}}BLOCK(road)
