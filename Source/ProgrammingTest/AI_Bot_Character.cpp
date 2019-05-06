#include "AI_Bot_Character.h"
#include "ProgrammingTestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAI_Bot_Character::AAI_Bot_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

}

void AAI_Bot_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAI_Bot_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAI_Bot_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
