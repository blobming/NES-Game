anytoc map_mainboard.h map.nam 8 "const u8 map_mainboard[]="
anytoc col_mainboard.h map.pal 8 "const u8 col_mainboard[]="
cl65 -t nes main.c
replace main.nes main chr.chr
pause