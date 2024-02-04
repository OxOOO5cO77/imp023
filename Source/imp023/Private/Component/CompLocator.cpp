// Copyright 2024 Impending Technologies

#include "Component/CompLocator.h"

UCompLocator::UCompLocator()
{
	PrimaryComponentTick.bCanEverTick = false;

	Locator = ELocator::None;
}
