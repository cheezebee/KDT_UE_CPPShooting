// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyManager.generated.h"

UCLASS()
class CPPSHOOTING_API ACEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//����ð�
	UPROPERTY()
	float currTime = 0;

	//�����ð�
	UPROPERTY(EditAnywhere)
	float createTime = 1;

	//�����ð� �ּҰ�, �ִ밪
	UPROPERTY(EditAnywhere)
	float fMin = 1.0f;

	UPROPERTY(EditAnywhere)
	float fMax = 3.0f;

	//Enemy ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACEnemy> enemyFactory;


};
