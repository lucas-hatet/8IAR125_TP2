#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBall.generated.h"

UCLASS()
class IAR125_TP1_API AMyBall : public AActor
{
	GENERATED_BODY()

public:
	AMyBall();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	FVector InitialVelocity;

	UPROPERTY(EditAnywhere)
	float Gravity = 1000.0f;
	
protected:
	virtual void BeginPlay() override;


private:
	FVector CurrentVelocity;
};
