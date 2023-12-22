// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPStudy.h"

// Sets default values
ACPPStudy::ACPPStudy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPPStudy::BeginPlay()
{
	Super::BeginPlay();
	
	// �Է� Ȱ��ȭ
	EnableInput(GetWorld()->GetFirstPlayerController());

	// �Է� ���ε�
	InputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ACPPStudy::InputFire);
}

// Called every frame
void ACPPStudy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMove == true)
	{
		//�Ÿ� = �ð� * �ӷ�
		FVector p0 = GetActorLocation();
		FVector vt = GetActorRightVector() * 150 * DeltaTime;
		FVector p = p0 + vt;

		// �̵��Ÿ���ŭ distance ������
		distance -= 150 * DeltaTime;

		// ���࿡ �̵��� �Ÿ��� 0���� ũ�ٸ�?
		if (distance > 0)
		{
			SetActorLocation(p);
		}
		// ���࿡ �̵��� �Ÿ��� 0���� �۴�?
		else if (distance < 0)
		{
			p = p + GetActorRightVector() * distance;
			SetActorLocation(p);
			distance = 0;
		}
	}
}

void ACPPStudy::InputFire()
{
	UE_LOG(LogTemp, Warning, TEXT("InputFire"));

	isMove = true;
}
