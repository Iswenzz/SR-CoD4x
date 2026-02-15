;Imports of g_bsp:

;Exports of g_bsp:
	global gameWorldMp
	global gameWorldSp


SECTION .text


;Initialized global or static variables of g_bsp:
SECTION .data


;Initialized constant data of g_bsp:
SECTION .rdata


;Zero initialized global or static variables of g_bsp:
SECTION .bss
gameWorldMp: resb 0x20
gameWorldSp: resb 0x2C


;All cstrings:
SECTION .rdata



;All constant floats and doubles:
SECTION .rdata

