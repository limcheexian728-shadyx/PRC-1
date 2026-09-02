// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;   // mouse-look rotates the boom

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false; // camera just sits on the boom
    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

    HealthComp = CreateDefaultSubobject<UHealth_Component>(TEXT("HealthComp"));
    StatComp = CreateDefaultSubobject<UStatComponent>(TEXT("StatComp"));
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (StatComp && GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed *= StatComp->MoveSpeedMultiplier;
    }

    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }

        if (IsLocallyControlled() && HUDWidgetClass)
        {
            HUDInstance = CreateWidget<UPlayerHUD>(PC, HUDWidgetClass);
            if (HUDInstance) HUDInstance->AddToViewport();
        }
    }


}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Move);
        EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Look);
        EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EIC->BindAction(IA_TestDamage, ETriggerEvent::Started, this, &AHeroCharacter::OnTestDamage);
        //EIC->BindAction(DodgeAction, ETriggerEvent::Started, this, &AHeroCharacter::Dodge);
    }
}

void AHeroCharacter::OnTestDamage(const FInputActionValue&)
{
    if (HealthComp) HealthComp->TakeDamage(25.f);
}

void AHeroCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MoveInput = Value.Get<FVector2D>();
    if (Controller && !MoveInput.IsNearlyZero())
    {
        const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
        const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(ForwardDir, MoveInput.Y);
        AddMovementInput(RightDir, MoveInput.X);
    }
}

void AHeroCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookInput = Value.Get<FVector2D>();
    AddControllerYawInput(LookInput.X);
    AddControllerPitchInput(LookInput.Y);
}

void AHeroCharacter::Dodge(const FInputActionValue& Value)
{
    if (bIsDodging) return;
    bIsDodging = true;
    bIsInvincible = true;

    LaunchCharacter(GetActorForwardVector() * DodgeImpulse, true, false);

    GetWorldTimerManager().SetTimer(InvincibilityTimerHandle, this,
        &AHeroCharacter::EndInvincibility, IFrameDuration, false);
    GetWorldTimerManager().SetTimer(DodgeCooldownTimerHandle, this,
        &AHeroCharacter::EndDodgeCooldown, DodgeCooldown, false);
}

void AHeroCharacter::EndInvincibility() { bIsInvincible = false; }
void AHeroCharacter::EndDodgeCooldown() { bIsDodging = false; }

void AHeroCharacter::SetKeyboardOnlyMode(bool bEnable)
{
    auto* PC = Cast<APlayerController>(Controller);
    auto* Sub = PC ? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
        PC->GetLocalPlayer()) : nullptr;
    if (!Sub) return;

    if (bEnable)
    {
        Sub->RemoveMappingContext(DefaultMappingContext);
        Sub->AddMappingContext(KeyboardOnlyMappingContext, 0);
    }
    else
    {
        Sub->RemoveMappingContext(KeyboardOnlyMappingContext);
        Sub->AddMappingContext(DefaultMappingContext, 0);
    }
}

void AHeroCharacter::Jump()
{
    Super::Jump();
    LaunchCharacter(FVector(0.f, 0.f, BulletJumpVelocityBoost), false, true);
    GetCharacterMovement()->AirControl =
        FMath::Min(1.0f, GetCharacterMovement()->AirControl + BulletJumpAirControlBoost);
}
void AHeroCharacter::AddCollectible()
{
    CollectibleCount++;
    OnCollectibleCountChanged.Broadcast(CollectibleCount);
}



