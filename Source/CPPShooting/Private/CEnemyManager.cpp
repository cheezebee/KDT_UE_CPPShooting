// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyManager.h"
#include "CEnemy.h"


// Sets default values
ACEnemyManager::ACEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Enemy ���� �ҷ�����
	ConstructorHelpers::FClassFinder<ACEnemy> tempEnemyFactory(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Enemy.BP_Enemy_C'"));
	if (tempEnemyFactory.Succeeded())
	{
		enemyFactory = tempEnemyFactory.Class;
	}
}

// Called when the game starts or when spawned
void ACEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// �����ð��� ������ ������ ����
	createTime = FMath::RandRange(fMin, fMax);
}

// Called every frame
void ACEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ʿ��� ������� : ����ð�, �����ð�, EnemyFactory(EnemyBlueprint)
	
	// 1. ����ð��� �帣�� �Ѵ�.
	currTime += DeltaTime;
	// 2. ���࿡ ����ð��� �����ð� ���� Ŀ���ٸ� (�����ð��ʰ� �����ٸ�)
	if (currTime > createTime)
	{
		// 3. Enemy �� �����ϰ� ��ġ��Ű��.
		GetWorld()->SpawnActor<ACEnemy>(enemyFactory, GetActorLocation(), GetActorRotation());
		// 4. ����ð��� �ʱ�ȭ
		currTime = 0;
		// 5. �����ð��� ������ ������ ����
		createTime = FMath::RandRange(fMin, fMax);
	}
}

