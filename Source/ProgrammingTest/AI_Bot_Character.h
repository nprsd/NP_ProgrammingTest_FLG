#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "AI_Bot_Character.generated.h"

UCLASS()
class PROGRAMMINGTEST_API AAI_Bot_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AAI_Bot_Character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWaypoint* NextWaypoint;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
