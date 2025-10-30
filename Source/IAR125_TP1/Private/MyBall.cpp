#include "MyBall.h"

#include "MyPaddle.h"
#include "Components/StaticMeshComponent.h"

AMyBall::AMyBall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
}

void AMyBall::BeginPlay()
{
	Super::BeginPlay();

	Mesh->AddImpulse(InitialVelocity, NAME_None, true);
}


void AMyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
