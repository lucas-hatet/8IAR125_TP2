#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPaddle.generated.h"

UCLASS()
class IAR125_TP1_API AMyPaddle : public AActor
{
	GENERATED_BODY()

public:
	AMyPaddle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxSpeed = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxForce = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Premove = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float brakeForce = 12.f;


private:
	class AActor* TargetBall = nullptr;
	FVector Seek(const FVector& Target);
};
