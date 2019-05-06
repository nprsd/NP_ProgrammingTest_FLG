#include "RedSphere.h"
#include "ProgrammingTestCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"

ARedSphere::ARedSphere()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 100.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionSphere;

	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SuperMesh->SetupAttachment(RootComponent);

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ARedSphere::OnOverlap);
	MyCollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ARedSphere::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (Mesh.Object)
		SuperMesh->SetStaticMesh(Mesh.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished'"));
	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}

	SuperMesh->SetMaterial(0, StoredMaterial);

}

void ARedSphere::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		isColliding = false;
}

void ARedSphere::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProgrammingTestCharacter>(OtherActor) && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Press E to Pick Me Up!"));
		isColliding = true;
		player = OtherActor;
	}	
}

void ARedSphere::BeginPlay()
{
	Super::BeginPlay();
}

void ARedSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isColliding && Cast<AProgrammingTestCharacter>(player)->isRedPressed)
	{
		Cast<AProgrammingTestCharacter>(player)->RedResource += 1;
		Destroy();
	}
}

