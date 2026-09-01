// Fill out your copyright notice in the Description page of Project Settings.


#include "Health_Component.h"

// Called when the game starts
void UHealth_Component::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	// ...
	
}

void UHealth_Component::TakeDamage(float Amount)
{
	if (Amount <= 0.f) return;
	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
	if (CurrentHealth <= 0.f) OnPlayerDeath.Broadcast();
}

void UHealth_Component::Heal(float Amount)
{
	if (Amount <= 0.f)return;
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}