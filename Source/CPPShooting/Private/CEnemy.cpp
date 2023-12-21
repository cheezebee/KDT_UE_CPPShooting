// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CPlayer.h"
#include "Particles/ParticleSystem.h"
#include "CMainGameMode.h"

// Sets default values
ACEnemy::ACEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Component �߰�
	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	// Root Component �� ����
	RootComponent = compSphere;
	// Sphere �� �������� 50���� ����
	compSphere->SetSphereRadius(50);
	// Collision Enable ����
	compSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Object Type ���� (Enemy��)
	compSphere->SetCollisionObjectType(ECC_GameTraceChannel1);
	// ��� Response �� Ignore �� ����
	compSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Bullet �� Overlap ���� ����
	compSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	// Player �� Overlap ���� ����
	compSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
	// DestroyZone �� Overlap ���� ����
	compSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);

	// StaticMeshComponent �߰�
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// RootComponent �� �ڽ����� ����
	compMesh->SetupAttachment(RootComponent);
	// Collision Prests �� NoCollision ���� ����
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	// ��� ����� �о����
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resources/Drone/Drone_low.Drone_low'"));
	if (tempMesh.Succeeded())
	{
		// ��� ����� ����
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	// compMesh �� ��ġ, ȸ���� ����
	compMesh->SetRelativeLocation(FVector(50, 0, 0));
	// Pitch, yaw, roll (y, z, x)
	compMesh->SetRelativeRotation(FRotator(0, 90, 90));

	// ���� �Ҹ� ��������
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Explosion01.Explosion01'"));
	if (tempSound.Succeeded())
	{
		exploSound = tempSound.Object;
	}
	// ���� ȿ�� ��������
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempEffect(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (tempEffect.Succeeded())
	{
		exploEffect = tempEffect.Object;
	}
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	int32 rand = UKismetMathLibrary::RandomIntegerInRange(0, 9);
	// �Ǵ� int32 rand = FMath::RandRange(0, 9);

	// 50% Ȯ���� ������ �÷��̾ ���ϰ� 
	if (rand < 5)
	{
		// ó���� �ѹ� �÷��̾ ���ϴ� ������ ���ϰ�
		// �÷��̾ ã��.		
		target = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

		// �÷��̾ �� ã�Ҵٸ�
		if (target != nullptr)
		{
			// 1. �÷��̾ ���ϴ� ������ ������ (player ��ġ - ��(Enemy)�� ��ġ)
			FVector playerPos = target->GetActorLocation();
			dir = playerPos - GetActorLocation();

			// ���࿡ ũ�Ⱑ 2...���ٰ� �����ϸ�..
			// 2. ������ ũ�⸦ 1�� �ٲ���
			dir.Normalize();		//---> dir �� ũ�Ⱑ 1�̵ȴ�.
			//dir.GetSafeNormal();	//---> dir �� ũ�Ⱑ ����, dir�� ũ�⸦ 1�θ���������� Vector ��ȯ
		}
		else
		{
			dir = -GetActorUpVector();
		}
	}
	// 50% Ȯ���� ������ �Ʒ��� ���ϰ�
	else
	{
		dir = -GetActorUpVector();
	}

	// Overlap �浹�� �Ǿ��� �� ȣ��Ǵ� �Լ� ��� (Delegate = �Լ��� ������ �ִ� ����)
	compSphere->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnOverlap);

}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// �� �������� ��� �̵��ϰ�ʹ�.
// 3. P = P0 + vt  �� �̿��ؼ� ���� �������� ��� ��������.
	FVector p0 = GetActorLocation();
	FVector vt = dir * moveSpeed * DeltaTime;
	FVector p = p0 + vt;
	SetActorLocation(p);
}

void ACEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ε��� ���Ͱ� Bullet �̶�� 
	if (OtherActor->GetName().Contains(TEXT("Bullet")))
	{
		// ���� �Ҹ� ����
		UGameplayStatics::PlaySound2D(GetWorld(), exploSound);

		// ���� ȿ�� ��������.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), exploEffect, GetActorLocation(), GetActorRotation());

		// ���� ���� ��带 ��������
		AGameModeBase* mode = UGameplayStatics::GetGameMode(GetWorld());
		// ������ ���� ��带 ACMainGameMode ������ ��ȯ
		ACMainGameMode* mainMode = Cast<ACMainGameMode>(mode);
		// ������ ����
		mainMode->AddScore(10);

		// �ε��� �� �ı�
		OtherActor->Destroy();
		// ���� �ı�
		Destroy();
	}

}

