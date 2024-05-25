; Import
	extern AnglesToAxis
	extern AxisToAngles
	extern BG_GetSpeed
	extern BG_CalculateViewAngles
	extern BG_GetWeaponDef
	extern BG_CalculateWeaponPosition_Sway
	extern BG_CalculateWeaponAngles
	extern BG_IsAimDownSightWeapon
	extern ClientInactivityTimer
	extern ClientImpacts
	extern G_SetOrigin
	extern G_UpdateEntityStateFromPlayerState
	extern G_Spawn
	extern g_speed
	extern g_entities
	extern g_mantleBlockTimeBuffer
	extern HandleClientEvent
	extern level
	extern MatrixMultiply
	extern memset
	extern Pmove
	extern SR_PmoveGetSpeed
	extern Player_UpdateActivate
	extern Scr_Notify
	extern Scr_AddVector
	extern SV_LinkEntity
	extern SpectatorThink
	extern scr_const
	extern _ZN9EntHandle6setEntEP9gentity_s

; Exports
	global ClientThink_real

SECTION .text

; void ClientThink_real(gentity_s* ent, usercmd_s* ucmd)
ClientThink_real:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x28c
	mov ebx, [ebp+0xc]
	mov eax, [ebp+0x8]
	mov edi, [eax+0x15c]
	cmp dword [edi+0x2f8c], 0x2
	jz ClientThink_real_10
ClientThink_real_70:
	add esp, 0x28c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
ClientThink_real_10:
	mov ecx, level
	mov eax, [ecx+0x1ec]
	lea edx, [eax+0xc8]
	cmp [ebx], edx
	jle ClientThink_real_20
	mov [ebx], edx
	mov eax, [ecx+0x1ec]
ClientThink_real_20:
	sub eax, 0x3e8
	cmp [ebx], eax
	jge ClientThink_real_30
	mov [ebx], eax
	mov esi, eax
ClientThink_real_210:
	sub esi, [edi]
	test esi, esi
	jle ClientThink_real_40
	cmp esi, 0xc9
	mov eax, 0xc8
	cmovge esi, eax
ClientThink_real_230:
	mov eax, [edi+0x2f64]
	cmp eax, 0x3
	jz ClientThink_real_50
	cmp eax, 0x2
	jz ClientThink_real_60
	mov [esp], edi
	call ClientInactivityTimer
	test eax, eax
	jz ClientThink_real_70
	mov eax, [edi+0x3088]
	mov [edi+0x308c], eax
	mov edx, [edi+0x3100]
	test edx, edx
	jnz ClientThink_real_80
	and eax, 0xffffffd7
	mov [edi+0x308c], eax
ClientThink_real_80:
	mov edx, [edi+0x2f94]
	mov [edi+0x3088], edx
	test dl, 0x28
	jnz ClientThink_real_90
	mov dword [edi+0x3100], 0x0
	mov edx, [edi+0x3088]
ClientThink_real_90:
	mov eax, [edi+0x308c]
	not eax
	and eax, edx
	mov [edi+0x3090], eax
	or eax, [edi+0x3094]
	mov [edi+0x3094], eax
	mov ecx, [edi+0x5b4]
	test ecx, ecx
	jz ClientThink_real_100
	test eax, 0x10000
	jnz ClientThink_real_110
	test eax, 0x20000
	jnz ClientThink_real_120
ClientThink_real_250:
	and edx, 0x1300
	mov [edi+0x3088], edx
	and dword [edi+0x3090], 0x1300
	and eax, 0x1300
	mov [edi+0x3094], eax
ClientThink_real_100:
	mov ecx, [edi+0xb4]
	mov [ebp-0x23c], ecx
	mov dword [esp+0x8], 0x110
	mov dword [esp+0x4], 0x0
	lea eax, [ebp-0x230]
	mov [esp], eax
	call memset
	mov [ebp-0x230], edi
	mov eax, [ebx]
	mov [ebp-0x22c], eax
	mov eax, [ebx+0x4]
	mov [ebp-0x228], eax
	mov eax, [ebx+0x8]
	mov [ebp-0x224], eax
	mov eax, [ebx+0xc]
	mov [ebp-0x220], eax
	mov eax, [ebx+0x10]
	mov [ebp-0x21c], eax
	mov eax, [ebx+0x14]
	mov [ebp-0x218], eax
	mov eax, [ebx+0x18]
	mov [ebp-0x214], eax
	mov eax, [ebx+0x1c]
	mov [ebp-0x210], eax
	mov eax, [edi+0x2fb0]
	mov [ebp-0x20c], eax
	mov eax, [edi+0x2fb4]
	mov [ebp-0x208], eax
	mov eax, [edi+0x2fb8]
	mov [ebp-0x204], eax
	mov eax, [edi+0x2fbc]
	mov [ebp-0x200], eax
	mov eax, [edi+0x2fc0]
	mov [ebp-0x1fc], eax
	mov eax, [edi+0x2fc4]
	mov [ebp-0x1f8], eax
	mov eax, [edi+0x2fc8]
	mov [ebp-0x1f4], eax
	mov eax, [edi+0x2fcc]
	mov [ebp-0x1f0], eax
	mov eax, 0x810011
	cmp dword [edi+0x4], 0x7
	mov edx, 0x2810011
	cmovl eax, edx
	mov [ebp-0x1ec], eax
	mov byte [ebp-0x124], 0x1
	lea edx, [edi+0x3098]
	lea ecx, [edi+0x1c]
	mov [ebp-0x270], ecx
	mov eax, [edi+0x1c]
	mov [edi+0x3098], eax
	lea eax, [edi+0x20]
	mov [ebp-0x254], eax
	mov eax, [edi+0x20]
	mov [edx+0x4], eax
	lea ecx, [edi+0x24]
	mov [ebp-0x250], ecx
	mov eax, [edi+0x24]
	mov [edx+0x8], eax
	mov [ebp-0xcc], edi
	mov eax, [edi+0x310c]
	mov [ebp-0xc8], eax
	mov eax, level
	mov edx, [eax+0x1ec]
	mov [ebp-0xc4], edx
	mov eax, [edi+0x3114]
	mov [ebp-0xc0], eax
	mov eax, [edi+0x3110]
	mov [ebp-0xbc], eax
	mov [esp+0x4], edx
	mov [esp], edi
	call BG_GetSpeed
	fstp dword [ebp-0xb8]
	cvtsi2ss xmm0, esi
	mulss xmm0, [_float_0_00100000]
	movss [ebp-0x26c], xmm0
	movss [ebp-0xb4], xmm0
	mov eax, [edi+0x3148]
	mov [ebp-0xb0], eax
	lea eax, [edi+0x3164]
	mov [ebp-0x268], eax
	mov [ebp-0xac], eax
	; -------------------------- SR Pmove_Extended --------------------------
	; Get the player's gspeed instead of the global server CVar
	; -----------------------------------------------------------------------
	; mov eax, g_speed 					; cvar_t* g_speed;
	; mov eax, [eax]					; deref
	; mov eax, [eax+0xc]				; eax = g_speed.integer;
	;
	mov ecx, [edi+0x24]					; playerState_t* ps
	call SR_PmoveGetSpeed				; int SR_PmoveGetSpeed(playerState_t *ps)
	; -------------------------- SR Pmove_Extended --------------------------
	mov [edi+0x60], eax
	lea edx, [ebp-0x3c]
	mov [esp+0x4], edx
	lea eax, [ebp-0xcc]
	mov [esp], eax
	call BG_CalculateViewAngles
	lea eax, [edi+0x108]
	movss xmm0, dword [edi+0x108]
	addss xmm0, [ebp-0x3c]
	movss [ebp-0x30], xmm0
	movss xmm0, dword [eax+0x4]
	addss xmm0, [ebp-0x38]
	movss [ebp-0x2c], xmm0
	movss xmm0, dword [eax+0x8]
	addss xmm0, [ebp-0x34]
	movss [ebp-0x28], xmm0
	mov eax, [edi+0xe8]
	mov [esp], eax
	call BG_GetWeaponDef
	mov [ebp-0x258], eax
	mov eax, [edi+0x630]
	add eax, [edi+0x634]
	sub eax, [ebp-0xc4]
	test eax, eax
	jle ClientThink_real_130
ClientThink_real_270:
	lea ebx, [edi+0x3130]
	mov [esp+0x14], esi
	mov dword [esp+0x10], 0x3f800000
	mov [esp+0xc], ebx
	lea eax, [edi+0x3124]
	mov [esp+0x8], eax
	lea eax, [edi+0x3118]
	mov [esp+0x4], eax
	mov [esp], edi
	call BG_CalculateWeaponPosition_Sway
	mov eax, [ebp-0xcc]
	mov [ebp-0x120], eax
	mov eax, [ebp-0xb8]
	mov [ebp-0x11c], eax
	movss xmm0, dword [ebp-0x26c]
	movss [ebp-0x118], xmm0
	lea eax, [edi+0x313c]
	mov [ebp-0x264], eax
	mov eax, [edi+0x313c]
	mov [ebp-0x114], eax
	mov edx, [ebp-0x264]
	mov eax, [edx+0x4]
	mov [ebp-0x110], eax
	mov eax, [edx+0x8]
	mov [ebp-0x10c], eax
	mov eax, [edi+0x3148]
	mov [ebp-0x108], eax
	mov eax, [ebp-0xc4]
	mov [ebp-0x104], eax
	mov eax, [edi+0x310c]
	mov [ebp-0x100], eax
	mov eax, [edi+0x3114]
	mov [ebp-0xfc], eax
	mov eax, [edi+0x3110]
	mov [ebp-0xf8], eax
	lea ecx, [edi+0x314c]
	mov [ebp-0x260], ecx
	mov eax, [edi+0x314c]
	mov [ebp-0xf4], eax
	mov eax, [ecx+0x4]
	mov [ebp-0xf0], eax
	mov eax, [ecx+0x8]
	mov [ebp-0xec], eax
	lea esi, [edi+0x3158]
	mov [ebp-0x25c], esi
	mov eax, [edi+0x3158]
	mov [ebp-0xe8], eax
	mov eax, [esi+0x4]
	mov [ebp-0xe4], eax
	mov eax, [esi+0x8]
	mov [ebp-0xe0], eax
	mov eax, [edi+0x3130]
	mov [ebp-0xdc], eax
	mov eax, [ebx+0x4]
	mov [ebp-0xd8], eax
	mov eax, [ebx+0x8]
	mov [ebp-0xd4], eax
	mov eax, [ebp-0x268]
	mov [ebp-0xd0], eax
	lea edx, [ebp-0x3c]
	mov [esp+0x4], edx
	lea eax, [ebp-0x120]
	mov [esp], eax
	call BG_CalculateWeaponAngles
	mov eax, [ebp-0x120]
	mov eax, [eax+0xe8]
	mov [esp], eax
	call BG_IsAimDownSightWeapon
	test eax, eax
	jz ClientThink_real_140
	pxor xmm0, xmm0
	mov eax, [ebp-0x120]
	ucomiss xmm0, [eax+0xf4]
	jp ClientThink_real_150
	jnz ClientThink_real_150
ClientThink_real_140:
	mov eax, [ebp-0x114]
	mov edx, [ebp-0x264]
	mov [edx], eax
	mov eax, [ebp-0x110]
	mov [edx+0x4], eax
	mov eax, [ebp-0x10c]
	mov [edx+0x8], eax
	mov eax, [ebp-0x108]
	mov [edi+0x3148], eax
	mov eax, [ebp-0xf4]
	mov ecx, [ebp-0x260]
	mov [ecx], eax
	mov eax, [ebp-0xf0]
	mov [ecx+0x4], eax
	mov eax, [ebp-0xec]
	mov [ecx+0x8], eax
	mov eax, [ebp-0xe8]
	mov esi, [ebp-0x25c]
	mov [esi], eax
	mov eax, [ebp-0xe4]
	mov [esi+0x4], eax
	mov eax, [ebp-0xe0]
	mov [esi+0x8], eax
	mov eax, [ebp-0x30]
	mov [edi+0x30a4], eax
	mov eax, [ebp-0x2c]
	mov [edi+0x30a8], eax
	lea eax, [ebp-0x230]
	mov [esp], eax
	call Pmove
	cmp byte [ebp-0x140], 0x0
	jnz ClientThink_real_160
ClientThink_real_260:
	mov ecx, [ebp-0x23c]
	cmp ecx, [edi+0xb4]
	jz ClientThink_real_170
	mov eax, level
	mov edx, [eax+0x1ec]
	mov esi, [ebp+0x8]
	mov [esi+0x184], edx
	mov eax, [eax+0x1ec]
	mov [esi+0x158], eax
ClientThink_real_170:
	mov esi, [ebp+0x8]
	mov [esp+0x4], esi
	mov [esp], edi
	call G_UpdateEntityStateFromPlayerState
ClientThink_real_240:
	mov edx, [ebp+0x8]
	add edx, 0x13c
	mov [ebp-0x248], edx
	mov edx, [ebp+0x8]
	add edx, 0x18
	mov ecx, [ebp+0x8]
	mov eax, [ecx+0x18]
	mov [ecx+0x13c], eax
	add ecx, 0x140
	mov [ebp-0x244], ecx
	mov eax, [edx+0x4]
	mov esi, [ebp+0x8]
	mov [esi+0x140], eax
	add esi, 0x144
	mov [ebp-0x240], esi
	mov eax, [edx+0x8]
	mov edx, [ebp+0x8]
	mov [edx+0x144], eax
	mov edx, [ebp+0x8]
	add edx, 0x108
	mov eax, [ebp-0x164]
	mov ecx, [ebp+0x8]
	mov [ecx+0x108], eax
	mov eax, [ebp-0x160]
	mov [edx+0x4], eax
	mov eax, [ebp-0x15c]
	mov [edx+0x8], eax
	mov edx, ecx
	add edx, 0x114
	mov eax, [ebp-0x158]
	mov [ecx+0x114], eax
	mov eax, [ebp-0x154]
	mov [edx+0x4], eax
	mov eax, [ebp-0x150]
	mov [edx+0x8], eax
	mov esi, [ecx+0x15c]
	mov eax, [esi+0xb4]
	lea ebx, [eax-0x4]
	cmp [ebp-0x23c], ebx
	cmovge ebx, [ebp-0x23c]
	lea edx, [eax+0x40]
	lea ecx, [ebx-0x100]
	cmp ebx, edx
	cmovg ebx, ecx
	cmp ebx, eax
	jl ClientThink_real_190
ClientThink_real_220:
	mov edx, [ebp+0x8]
	mov [esp], edx
	call SV_LinkEntity
	mov ecx, [ebp-0x270]
	mov eax, [ecx]
	mov esi, [ebp-0x248]
	mov [esi], eax
	mov edx, [ebp-0x254]
	mov eax, [edx]
	mov ecx, [ebp-0x244]
	mov [ecx], eax
	mov esi, [ebp-0x250]
	mov eax, [esi]
	mov edx, [ebp-0x240]
	mov [edx], eax
	mov edx, [ebp+0x8]
	add edx, 0x148
	xor eax, eax
	mov ecx, [ebp+0x8]
	mov [ecx+0x148], eax
	mov [edx+0x4], eax
	mov [edx+0x8], eax
	mov eax, [edi+0x10c]
	mov [ecx+0x14c], eax
	lea esi, [ebp-0x230]
	mov [esp+0x4], esi
	mov [esp], ecx
	call ClientImpacts
	mov eax, [ebp-0x23c]
	cmp eax, [edi+0xb4]
	jz ClientThink_real_200
	mov eax, level
	mov eax, [eax+0x1ec]
	mov edx, [ebp+0x8]
	mov [edx+0x184], eax
ClientThink_real_200:
	mov ecx, [ebp+0x8]
	mov [esp], ecx
	call Player_UpdateActivate
	add esp, 0x28c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
ClientThink_real_30:
	mov esi, [ebx]
	jmp ClientThink_real_210
ClientThink_real_190:
	mov eax, ebx
	and eax, 0x3
	mov edx, [esi+eax*4+0xc8]
	mov [esp+0xc], edx
	mov eax, [esi+eax*4+0xb8]
	mov [esp+0x8], eax
	mov eax, [ebp+0x8]
	mov [esp+0x4], eax
	mov [esp], esi
	call HandleClientEvent
	add ebx, 0x1
	cmp [esi+0xb4], ebx
	jg ClientThink_real_190
	jmp ClientThink_real_220
ClientThink_real_50:
	mov edx, [ebp+0x8]
	mov eax, [edx+0x15c]
	mov ecx, [eax+0x3088]
	mov [eax+0x308c], ecx
	mov edx, [eax+0x2f94]
	mov [eax+0x3088], edx
	not ecx
	and edx, ecx
	or [eax+0x3094], edx
	add esp, 0x28c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
ClientThink_real_40:
	mov eax, [ebp+0x8]
	sub eax, g_entities
	sar eax, 0x2
	imul eax, eax, 0x2c0685b5
	cmp [edi+0xdc], eax
	jnz ClientThink_real_230
	jmp ClientThink_real_70
ClientThink_real_60:
	mov [esp+0x4], ebx
	mov ecx, [ebp+0x8]
	mov [esp], ecx
	call SpectatorThink
	jmp ClientThink_real_70
ClientThink_real_150:
	mov ecx, [ebp-0x258]
	mov esi, [ecx+0x438]
	test esi, esi
	jnz ClientThink_real_140
	lea esi, [ebp-0x84]
	mov [esp+0x4], esi
	lea eax, [ebp-0x3c]
	mov [esp], eax
	call AnglesToAxis
	lea esi, [ebp-0xa8]
	mov [esp+0x4], esi
	lea edx, [ebp-0x30]
	mov [esp], edx
	call AnglesToAxis
	lea ebx, [ebp-0x60]
	mov [esp+0x8], ebx
	mov [esp+0x4], esi
	lea ecx, [ebp-0x84]
	mov [esp], ecx
	call MatrixMultiply
	lea esi, [ebp-0x30]
	mov [esp+0x4], esi
	mov [esp], ebx
	call AxisToAngles
	jmp ClientThink_real_140
ClientThink_real_120:
	mov dword [esp+0x8], 0x0
	mov eax, scr_const
	movzx eax, word [eax+0x14]
	mov [esp+0x4], eax
	mov edx, [ebp+0x8]
	mov [esp], edx
	call Scr_Notify
	mov edx, [edi+0x3088]
	mov eax, [edi+0x3094]
	jmp ClientThink_real_250
ClientThink_real_160:
	mov edx, [ebp-0x130]
	mov [ebp-0x24c], edx
	mov eax, [ebp-0x230]
	mov eax, [eax+0xdc]
	lea ebx, [eax+eax*8]
	lea ebx, [eax+ebx*2]
	mov edx, ebx
	shl edx, 0x5
	add ebx, edx
	add ebx, eax
	add ebx, g_entities
	call G_Spawn
	mov esi, eax
	mov [esp+0x4], ebx
	lea eax, [eax+0x198]
	mov [esp], eax
	call _ZN9EntHandle6setEntEP9gentity_s
	mov [esp+0x4], ebx
	lea eax, [esi+0x154]
	mov [esp], eax
	call _ZN9EntHandle6setEntEP9gentity_s
	mov dword [esi+0x120], 0x10000
	mov dword [esi+0x190], 0x10000
	mov byte [esi+0xf6], 0x21
	mov dword [esi+0x4], 0x5
	mov byte [esi+0x16e], 0x15
	lea ecx, [esi+0x108]
	lea edx, [ebx+0x108]
	mov eax, [ebx+0x108]
	mov [esi+0x108], eax
	mov eax, [edx+0x4]
	mov [ecx+0x4], eax
	mov eax, [edx+0x8]
	mov [ecx+0x8], eax
	lea ecx, [esi+0x114]
	lea edx, [ebx+0x114]
	mov eax, [ebx+0x114]
	mov [esi+0x114], eax
	mov eax, [edx+0x4]
	mov [ecx+0x4], eax
	mov eax, [edx+0x8]
	mov [ecx+0x8], eax
	lea eax, [ebp-0x13c]
	mov [esp+0x4], eax
	mov [esp], esi
	call G_SetOrigin
	mov [esp], esi
	call SV_LinkEntity
	mov eax, g_mantleBlockTimeBuffer
	mov edx, [eax]
	mov eax, level
	mov ecx, [eax+0x1ec]
	add [ebp-0x24c], ecx
	mov eax, [edx+0xc]
	add [ebp-0x24c], eax
	mov edx, [ebp-0x24c]
	mov [esi+0x19c], edx
	jmp ClientThink_real_260
ClientThink_real_130:
	and dword [edi+0xc], 0xfffeffff
	jmp ClientThink_real_270
ClientThink_real_110:
	movsx eax, byte [ebx+0x1d]
	cvtsi2ss xmm3, eax
	movss xmm2, dword [_float_128_00000000]
	addss xmm3, xmm2
	movss xmm0, dword [_float_255_00000000]
	divss xmm3, xmm0
	movsx eax, byte [ebx+0x1e]
	cvtsi2ss xmm1, eax
	addss xmm1, xmm2
	divss xmm1, xmm0
	mov eax, level
	mulss xmm3, [eax+0x2e58]
	mulss xmm1, [eax+0x2e5c]
	movaps xmm0, xmm3
	mulss xmm0, [eax+0x2e64]
	addss xmm0, [eax+0x2e50]
	movaps xmm2, xmm1
	mulss xmm2, [eax+0x2e60]
	subss xmm0, xmm2
	movss [ebp-0x24], xmm0
	mulss xmm3, [eax+0x2e60]
	movss xmm0, dword [eax+0x2e54]
	subss xmm0, xmm3
	mulss xmm1, [eax+0x2e64]
	subss xmm0, xmm1
	movss [ebp-0x20], xmm0
	mov dword [ebp-0x1c], 0x0
	lea eax, [ebp-0x24]
	mov [esp], eax
	call Scr_AddVector
	mov dword [esp+0x8], 0x1
	mov eax, scr_const
	movzx eax, word [eax+0x16]
	mov [esp+0x4], eax
	mov eax, [ebp+0x8]
	mov [esp], eax
	call Scr_Notify
	mov edx, [edi+0x3088]
	mov eax, [edi+0x3094]
	jmp ClientThink_real_250


SECTION .rdata
	_float_0_00100000:		dd 0x3a83126f		; 0.001
	_float_128_00000000:	dd 0x43000000		; 128
	_float_255_00000000:	dd 0x437f0000		; 255
