// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "CPlayer.h"

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComponent ���� �� RootComponent ��
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	SetRootComponent(compBox);
	// compBox �� BoxExtent �� ���� 25, 25, 50 ���� ����
	compBox->SetBoxExtent(FVector(25, 25, 50));
	// compBox �� Collision preset �� Bullet ���� ����
	compBox->SetCollisionProfileName(TEXT("Bullet"));

	// StaticMeshComponent �� RootComponent �� �ڽ�����
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox); //(RootComponent)
	// ũ�⸦ 0.5, 0.5, 1 �� ����
	compMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 1));
	// Collision preset �� NoCollision ���� ����
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	// Cube �� �о�ͼ� ����
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}

	// Cube �� ���͸��� ����
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Engine/EngineDebugMaterials/TangentColorMaterial.TangentColorMaterial'"));
	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0, tempMat.Object);
	}
}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//���� ��� �̵��ϰ� �ʹ�.(P = P0 + vt)
	FVector p0 = GetActorLocation();
	FVector vt = GetActorUpVector() * moveSpeed * DeltaTime;
	FVector p = p0 + vt;
	SetActorLocation(p);
}

void ACBullet::SetAcitve(bool isActive)
{
	// ���࿡ isActive �� true ��
	if (isActive == true)
	{
		// ���(mesh) �� ���̰� ����
		compMesh->SetVisibility(isActive);
		// �浹 �� �� �ְ� ����
		compBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	// �׷��� ������
	else
	{
		// ���(mesh) �� �Ⱥ��̰� ����
		compMesh->SetVisibility(isActive);
		// �浹 ���� �ʰ� ����
		compBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACBullet::InsertMagazine()
{
	// 1. Player �� ã��
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

	// 2. ���࿡ player �� ã�� �������� �Լ��� ������.
	if (actor == nullptr) return;
	
	// 3. ACPlayer �� ����ȯ
	ACPlayer* player = Cast<ACPlayer>(actor);
	// 4. ���� Player �� ������ �ִ� źâ�� ����
	player->magazine.Add(this);
	// 5. ���� ��Ȱ��ȭ
	SetAcitve(false);


}

