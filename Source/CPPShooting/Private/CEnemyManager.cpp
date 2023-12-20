// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyManager.h"



// Sets default values
ACEnemyManager::ACEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	// �����ð��� ������
	// ���ʹ̰��忡�� ���ʹ̸� ������ ���ÿ� ��ġ�� ��(EnemyManager)�� ��ġ��
}

// Called every frame
void ACEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ʿ��� ������� : ����ð�
	
	// 1. ����ð��� �帣�� �Ѵ�.
	currTime += DeltaTime;
	// 2. ���࿡ ����ð��� 1���� Ŀ���ٸ� (1�ʰ� �����ٸ�)
	if (currTime > 1)
	{
		// 3. 1�ʰ� ������� ��� Outlog �� ���
		UE_LOG(LogTemp, Warning, TEXT("11111111111"));
		// 4. ����ð��� �ʱ�ȭ
		currTime = 0;
	}
}

