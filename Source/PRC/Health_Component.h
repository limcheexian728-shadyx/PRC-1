// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Health_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnHealthChanged, float, NewHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

//DECLARE macros go here

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PRC_API UHealth_Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHealth = 100.f;
	float CurrentHealth = 0.f;
	// delegate UPROPERTY slots go here after the DECLARE macros above
	//void TakeDamage(float Amount);
	//void Heal(float Amount);

	UPROPERTY(BlueprintAssignable) 
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable) 
	FOnPlayerDeath OnPlayerDeath;

	UFUNCTION(BlueprintCallable) 
	void TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable) 
	void Heal(float Amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
