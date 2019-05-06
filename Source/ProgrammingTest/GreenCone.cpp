#include "GreenCone.h"
#include "ProgrammingTestCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"

AGreenCone::AGreenCone()
{
	PrimaryActorTick.bCanEverTick = true;

	ProximityToPlayer = 100.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(ProximityToPlayer);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionSphere;

	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SuperMesh->SetupAttachment(RootComponent);

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGreenCone::OnOverlap);
	MyCollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AGreenCone::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));

	if (Mesh.Object)
		SuperMesh->SetStaticMesh(Mesh.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));
	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}

	SuperMesh->SetMaterial(0, StoredMaterial);

}

void AGreenCone::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		isColliding = false;
}

void AGreenCone::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProgrammingTestCharacter>(OtherActor) && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Press Q to Pick Me Up!"));
		isColliding = true;
		player = OtherActor;
	}
}

void AGreenCone::BeginPlay()
{
	Super::BeginPlay();
	MyCollisionSphere->SetSphereRadius(ProximityToPlayer);
}

void AGreenCone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isColliding && Cast<AProgrammingTestCharacter>(player)->isGreenPressed)
	{
		Cast<AProgrammingTestCharacter>(player)->GreenResource += 1;
		Destroy();
	}
}
