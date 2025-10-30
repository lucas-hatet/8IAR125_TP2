#include "MyPaddle.h"
#include "MyBall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

AMyPaddle::AMyPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = Mesh;
}

void AMyPaddle::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector TargetLocation;

	if (!IsValid(TargetBall) || TargetBall->IsActorBeingDestroyed())
	{
		TArray<AActor*> Balls;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyBall::StaticClass(), Balls);
		Balls.Sort([](const AActor& A, const AActor& B)
		{
			return A.GetActorLocation().Z < B.GetActorLocation().Z;
		});
		
		if (Balls.Num() > 0)
			if (Balls[0]->GetActorLocation().Z > GetActorLocation().Z && (
					Balls[0]->GetActorLocation().Z > GetActorLocation().Z + Premove
					|| Balls[0]->GetActorLocation().X < GetActorLocation().X - 50 || Balls[0]->GetActorLocation().X > GetActorLocation().X + 50
				))
				TargetLocation = Balls[0]->GetActorLocation();
			else if (Balls.Num() > 1)
				TargetLocation = Balls[1]->GetActorLocation();
		else
			TargetLocation = FVector::ZeroVector;
	}

	
	TargetLocation.Y = GetActorLocation().Y;
	TargetLocation.Z = GetActorLocation().Z;
	
	FVector Steering;
	if (FMath::Abs(TargetLocation.X - GetActorLocation().X) < 10) Steering = FVector::ZeroVector;
	else Steering = Seek(TargetLocation);
	
	Velocity += Steering * DeltaTime;
	Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);
	if (FMath::Abs(TargetLocation.X - GetActorLocation().X) < 50) Velocity *= 10/brakeForce;
	
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	SetActorLocation(NewLocation);
}

FVector AMyPaddle::Seek(const FVector& Target)
{
	FVector DesiredVelocity = Target - GetActorLocation();
	DesiredVelocity.Normalize();
	DesiredVelocity *= MaxSpeed;

	FVector Steering = DesiredVelocity - Velocity;
	Steering = Steering.GetClampedToMaxSize(MaxForce);

	return Steering;
}
