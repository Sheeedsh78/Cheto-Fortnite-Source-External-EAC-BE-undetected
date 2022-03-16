#pragma once
#include <Windows.h>

#define OFFSET_UWORLD 0xb78bc70

namespace Offsets {
	uintptr_t PastePolice = 0x1337;


	uintptr_t GameInstance = 0x190;
	uintptr_t LocalPlayers = 0x38;
	uintptr_t PlayerController = 0x30;
	uintptr_t LocalPawn = 0x2A8;
	uintptr_t PlayerState = 0x238;
	uintptr_t RootComponent = 0x130;
	uintptr_t Persistentlevel = 0x30;
	uintptr_t TeamIndex = 0xF28;
	uintptr_t AcotrCount = 0xA0;
	uintptr_t AAcotrs = 0x98;
	uintptr_t Mesh = 0x280;
	uintptr_t RelativeLocation = 0x11C;
	uintptr_t CurrentActor = 0x8;
	uintptr_t Velocity = 0x140;
	uintptr_t ComponentToWorld = 0x1C0;
	uintptr_t BoneArray = 0x4B0;
	uintptr_t bIsDying = 0x548;
	uintptr_t bIsDBNO = 0x572;
}

namespace W2S {
	uintptr_t chain69 = 0xA8;
	uintptr_t chain699 = 0x7E8;
	uintptr_t chain = 0x70;
	uintptr_t chain1 = 0x98;
	uintptr_t chain2 = 0x140;
	uintptr_t vDelta = 0x10;
	uintptr_t zoom = 0x580;
}