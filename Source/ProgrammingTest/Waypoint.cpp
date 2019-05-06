#include "Waypoint.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Components/SphereComponent.h"
#include "AI_Bot_Character.h"

AWaypoint::AWaypoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWaypoint::OnPlayerEnter);

}

void AWaypoint::BeginPlay()
{
	Super::BeginPlay();
}

void AWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaypoint::OnPlayerEnter(UPrimitiveComponent * OverlapComponent, AActor * OtherActor,	UPrimitiveComponent * OtherComponent,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAI_Bot_Character* Character = nullptr;

	if (OtherActor != nullptr)
	{
		Character = Cast<AAI_Bot_Character>(OtherActor);

		if (Character != nullptr)
		{
			//Calculate a Random Int
			currentIndex = FMath::RandRange(0, ListOfWaypoints.Num() - 1);
			//Assign Random Int to TArray of Waypoints and pass that info to Character
			Character->NextWaypoint = ListOfWaypoints[currentIndex];
		}
	}
}