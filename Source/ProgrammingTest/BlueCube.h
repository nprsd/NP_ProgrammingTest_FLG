#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BlueCube.generated.h"

UCLASS()
class PROGRAMMINGTEST_API ABlueCube : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlueCube();

	float SphereRadius;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SuperMesh;
	
	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	USphereComponent* MyCollisionSphere;

	UPROPERTY(EditAnywhere)
	UMaterial* StoredMaterial;
	
	UMaterialInstanceDynamic* DynamicMaterialInst;

};