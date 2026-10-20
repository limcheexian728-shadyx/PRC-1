// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PRCSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PRC_API UPRCSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Save")
	int32 Score = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	float HP = 100.f;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	TArray<FString> Inventory;
};
