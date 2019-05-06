#include "BlueCube.h"
#include "ProgrammingTestCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ABlueCube::ABlueCube()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 100.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionSphere;
	
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SuperMesh->SetupAttachment(RootComponent);
	
	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlueCube::OnOverlap);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	
	if(Mesh.Object)
	SuperMesh->SetStaticMesh(Mesh.Object);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean'"));
	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}

	SuperMesh->SetMaterial(0, StoredMaterial);

}

void ABlueCube::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProgrammingTestCharacter>(OtherActor) != nullptr)
	{
		Cast<AProgrammingTestCharacter>(OtherActor)->BlueResource += 1;
		Destroy();
	}
}