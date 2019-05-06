#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Waypoint.generated.h"

UCLASS()
class PROGRAMMINGTEST_API AWaypoint : public AActor
{
	GENERATED_BODY()
	
public:
	AWaypoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY()
	int32 currentIndex = 0;

	UPROPERTY(EditAnywhere)
	TArray<AWaypoint*> ListOfWaypoints;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPlayerEnter(UPrimitiveComponent* OverlapComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

};