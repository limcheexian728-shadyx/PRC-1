// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Health_Component.h"
#include "StatComponent.h"
#include "GameFramework/Character.h"
#include "PlayerHUD.h"
#include "HeroCharacter.generated.h"



UCLASS()
class PRC_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UPlayerHUD> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerHUD> HUDInstance;

public:
	// Sets default values for this character's properties
	AHeroCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealth_Component> HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStatComponent> StatComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> DodgeAction;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> KeyboardOnlyMappingContext;

	virtual void Jump() override;
	UPROPERTY(EditAnywhere, Category = "Movement|Bullet Jump")
	float BulletJumpVelocityBoost = 600.0f;
	UPROPERTY(EditAnywhere, Category = "Movement|Bullet Jump")
	float BulletJumpAirControlBoost = 0.3f;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetKeyboardOnlyMode(bool bEnable);

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void Dodge(const struct FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Movement|Dodge")
	float DodgeImpulse = 900.0f;
	UPROPERTY(EditAnywhere, Category = "Movement|Dodge")
	float IFrameDuration = 0.35f;
	UPROPERTY(EditAnywhere, Category = "Movement|Dodge")
	float DodgeCooldown = 0.6f;

	bool bIsInvincible = false;

	UPROPERTY(BlueprintAssignable, Category = "Collectibles")
	FOnCollectibleCountChanged OnCollectibleCountChanged;

	UFUNCTION(BlueprintCallable, Category = "Collectibles")
	void AddCollectible();

	

private:
	int32 CollectibleCount = 0;
	bool bIsDodging = false;
	FTimerHandle InvincibilityTimerHandle;
	FTimerHandle DodgeCooldownTimerHandle;
	void EndInvincibility();
	void EndDodgeCooldown();


};
