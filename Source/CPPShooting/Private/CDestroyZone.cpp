// Fill out your copyright notice in the Description page of Project Settings.


#include "CDestroyZone.h"
#include "Components/BoxComponent.h"
#include "CBullet.h"

// Sets default values
ACDestroyZone::ACDestroyZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// boxComponent ����
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	// RootComponent �� ����
	SetRootComponent(compBox);
	// compBox �� ũ�⸦ Ű����
	compBox->SetBoxExtent(FVector(50, 2000, 50));
	// collision preset �� ����
	compBox->SetCollisionProfileName(TEXT("DestroyZone"));
}

// Called when the game starts or when spawned
void ACDestroyZone::BeginPlay()
{
	Super::BeginPlay();
	
	// Overlap �浹�� �Ǿ��� �� ȣ��Ǵ� �Լ� ���
	compBox->OnComponentBeginOverlap.AddDynamic(this, &ACDestroyZone::OnOverlap);
}

// Called every frame
void ACDestroyZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDestroyZone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���࿡ �Ѿ��� �ƴϸ�
	if (OtherComp->GetCollisionObjectType() != ECollisionChannel::ECC_GameTraceChannel2)
	{
		// �ε��� ���� �ı�����
		OtherActor->Destroy();
	}	
	else
	{
		Cast<ACBullet>(OtherActor)->InsertMagazine();
	}
}

