// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyControlDataAsset.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 450.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritYaw = true;
	CameraBoom->bInheritRoll = true;
	CameraBoom->bDoCollisionTest = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/MyContents/Input/MyIMC_Default.MyIMC_Default'"));
	if (IMCRef.Object)
	{
		DefaultMappingContext = IMCRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContents/Input/InputAction/MyIA_Move.MyIA_Move'"));
	if (IAMoveRef.Object)
	{
		MoveAction = IAMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContents/Input/InputAction/MyIA_Jump.MyIA_Jump'"));
	if (IAJumpRef.Object)
	{
		JumpAction = IAJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IALookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContents/Input/InputAction/MyIA_Look.MyIA_Look'"));
	if (IALookRef.Object)
	{
		LookAction = IALookRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IARunRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContents/Input/InputAction/MyIA_Run.MyIA_Run'"));
	if (IARunRef.Object)
	{
		RunAction = IARunRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IADefalutAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyContents/Input/InputAction/MyIA_DefaultAttack.MyIA_DefaultAttack'"));
	if (IADefalutAttackRef.Object)
	{
		DefalutAttackAction = IADefalutAttackRef.Object;
	}
}

void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterControlData(ControlDataAsset);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Look);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::TriggerRun);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyPlayerCharacter::ReleaseRun);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Canceled, this, &AMyPlayerCharacter::ReleaseRun);
	EnhancedInputComponent->BindAction(DefalutAttackAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::DefaultAttack);
}

void AMyPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AMyPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AMyPlayerCharacter::TriggerRun()
{
	GetCharacterMovement()->MaxWalkSpeed = ControlDataAsset->RunSpeed;
}

void AMyPlayerCharacter::ReleaseRun()
{
	GetCharacterMovement()->MaxWalkSpeed = ControlDataAsset->WalkSpeed;
}

void AMyPlayerCharacter::DefaultAttack()
{
	ProcessComboCommand();
}

void AMyPlayerCharacter::SetCharacterControlData(const UMyControlDataAsset* InDataAsset)
{
	Super::SetCharacterControlData(InDataAsset);
}
