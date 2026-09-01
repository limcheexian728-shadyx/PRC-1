// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

float UStatComponent::GetMoveSpeed(float BaseSpeed) const
{
	return BaseSpeed * MoveSpeedMultiplier;
}

void UStatComponent::AddCollectible(int32 Amount)
{
	CollectibleCount += Amount;
	OnCollectibleCountChanged.Broadcast(CollectibleCount);
}