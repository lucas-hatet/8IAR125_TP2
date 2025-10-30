#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBallSpawner.generated.h"

UCLASS()
class IAR125_TP1_API AMyBallSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AMyBallSpawner();

	virtual void Tick(float DeltaTime) override;
	int Wait;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AMyBall> BallClass;

private:
	FVector TargetPosition;
	bool bHasTarget;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Width = 600.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed = 300.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxForce = 600.f;

	FVector Velocity = FVector::ZeroVector;

	void SpawnBall();
	
	FVector Seek(const FVector& Target);
};
