// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegateStudy.generated.h"

// �Ű������� ���� �Լ��� �ϳ� ����� �� �ִ� ��������Ʈ
DECLARE_DELEGATE(FSimpleDel);

// �Ű������� �ִ� �Լ��� �ϳ� ����� �� �ִ� ��������Ʈ
DECLARE_DELEGATE_OneParam(FSimpleOneParamDel, FString);

// �Ű������� ���� �Լ��� ������ ����� �� �ִ� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FMultiDel);

// �Ű������� �ִ� �Լ��� ������ ����� �� �ִ� ��������Ʈ
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiTwoParamDel, int32, FString);


UCLASS()
class CPPSHOOTING_API ADelegateStudy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateStudy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InputTest();

public:

	//---------------------------
	FSimpleDel simpleDel;
	UFUNCTION()
	void SimpleDelFunc();

	//---------------------------
	FSimpleOneParamDel simpleOneParamDel;
	UFUNCTION()
	void SimpleOneParamDelFunc(FString str);

	//---------------------------
	FMultiDel multiDel;
	UFUNCTION()
	void MultiDel1();
	UFUNCTION()
	void MultiDel2();
	FDelegateHandle delHandle;

	//---------------------------
	FMultiTwoParamDel multiTwoParamDel;
	UFUNCTION()
	void MultiTwoParamDel1(int32 num, FString str);
	UFUNCTION()
	void MultiTwoParamDel2(int32 num, FString str);
};
