// Copyright 2024 Impending Technologies

#include "Component/CompZone.h"

UCompZone::UCompZone()
{
	PrimaryComponentTick.bCanEverTick = false;

	Zone = EZone::Middle;
}
