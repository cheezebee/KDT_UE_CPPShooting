// Fill out your copyright notice in the Description page of Project Settings.


#include "CBackground.h"

// Sets default values
ACBackground::ACBackground()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh Component �߰�
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// RootComponent �� ����
	RootComponent = compMesh;

	// Plane ����� �о� �ͼ� ����
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	
	// ���� �̹��� �о� �ͼ� ����
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/Resources/MatBG.MatBG'"));
	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0, tempMat.Object);
	}
}

// Called when the game starts or when spawned
void ACBackground::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBackground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �Ʒ��� �������� (P = P0 + vt)
	FVector p0 = GetActorLocation();
	FVector vt = FVector::DownVector * scrollSpeed * DeltaTime;
	FVector p = p0 + vt;

	// ���࿡ p �� z ���� -3000 ���� ������ p �� z ���� 9000 �� ���Ѵ�.
	if (p.Z < -3000)
	{
		p.Z += 9000;
	}

	SetActorLocation(p);
}

