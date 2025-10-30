#include "MyBallSpawner.h"
#include "MyBall.h"
#include "MyPaddle.h"
#include "Kismet/GameplayStatics.h"

AMyBallSpawner::AMyBallSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyBallSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AMyBallSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHasTarget || FVector::Dist(GetActorLocation(), TargetPosition) < 10.f)
	{
		float RandomX = FMath::RandRange(-Width, Width);
		TargetPosition = FVector(RandomX, GetActorLocation().Y, GetActorLocation().Z);
		SpawnBall();
		bHasTarget = true;
	}

	FVector Steering = Seek(TargetPosition);
	Velocity += Steering * DeltaTime;
	Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);
	Velocity.Y = 0.f;
	Velocity.Z = 0.f;

	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	NewLocation.X = FMath::Clamp(NewLocation.X, -900.f, 900.f);
	NewLocation.Y = GetActorLocation().Y;
	NewLocation.Z = GetActorLocation().Z;

	SetActorLocation(NewLocation);
}

void AMyBallSpawner::SpawnBall()
{
	if (!BallClass) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, -30.f);
	FActorSpawnParameters Params;

	AMyBall* NewBall = GetWorld()->SpawnActor<AMyBall>(BallClass, SpawnLocation, FRotator::ZeroRotator, Params);
	NewBall->InitialVelocity = FVector(0.f, 0.f, 0.f);
}

FVector AMyBallSpawner::Seek(const FVector& Target)
{
	FVector DesiredVelocity = Target - GetActorLocation();
	DesiredVelocity.Normalize();
	DesiredVelocity *= MaxSpeed;

	FVector Steering = DesiredVelocity - Velocity;
	Steering = Steering.GetClampedToMaxSize(MaxForce);

	return Steering;
}
