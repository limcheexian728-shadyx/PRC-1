// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(const FString& ItemName)
{
	Items.Add(ItemName);
}

bool UInventoryComponent::RemoveItem(const FString& ItemName)
{
	return Items.RemoveSingle(ItemName) > 0;
}

int32 UInventoryComponent::CountItem(const FString& ItemName) const
{
	int32 Count = 0;
	for (const FString& Item : Items)
	{
		if (Item == ItemName)
		{
			Count++;
		}
	}
	return Count;
}