#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "RedSphere.generated.h"

UCLASS()
class PROGRAMMINGTEST_API ARedSphere : public AActor
{
	GENERATED_BODY()

public:	

	ARedSphere();
	
	float SphereRadius;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SuperMesh;
	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	USphereComponent* MyCollisionSphere;

	UPROPERTY(EditAnywhere)
	UMaterial* StoredMaterial;

	UMaterialInstanceDynamic* DynamicMaterialInst;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isColliding;

	UPROPERTY()
	AActor* player;

protected:
	virtual void BeginPlay() override;

};
