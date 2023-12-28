// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateStudy.h"

// Sets default values
ADelegateStudy::ADelegateStudy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADelegateStudy::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(GetWorld()->GetFirstPlayerController());
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADelegateStudy::InputTest);


	// ���ٽ�
	// [this] (�Ű�����...) -> ��ȯ�� 
	// {
	//		To do...
	// }

	// DECLARE_DELEGATE �Լ� ���  (3����)
	simpleDel.BindUFunction(this, TEXT("SimpleDelFunc"));
	simpleDel.BindUObject(this, &ADelegateStudy::SimpleDelFunc);
	/*simpleDel.BindLambda([this]()->void {
		UE_LOG(LogTemp, Warning, TEXT("Call SimpleDelFunc by Lambda"));
	});*/

	// DECLARE_DELEGATE_OneParam �Լ� ���
	simpleOneParamDel.BindUFunction(this, TEXT("SimpleOneParamDelFunc"));
	simpleOneParamDel.BindUObject(this, &ADelegateStudy::SimpleOneParamDelFunc);
	/*simpleOneParamDel.BindLambda([this](FString str) -> void {
		UE_LOG(LogTemp, Warning, TEXT("Call SimpleOneParamDelFunc by Lambda"));
	});*/

	// DECLARE_MULTICAST_DELEGATE �Լ� ���
	delHandle = multiDel.AddUFunction(this, TEXT("MultiDel1"));
	multiDel.AddUObject(this, &ADelegateStudy::MultiDel2);
	multiDel.AddUObject(this, &ADelegateStudy::SimpleDelFunc);
	multiDel.AddLambda([this]() -> void {
		UE_LOG(LogTemp, Warning, TEXT("Call multiDel by Lambda"));
	});

	// DECLARE_MULTICAST_DELEGATE_TwoParams �Լ� ���
	multiTwoParamDel.AddUFunction(this, TEXT("MultiTwoParamDel1"));
	multiTwoParamDel.AddUObject(this, &ADelegateStudy::MultiTwoParamDel2);
	multiTwoParamDel.AddLambda([this](int32 num, FString str) -> void {
		UE_LOG(LogTemp, Warning, TEXT("Call multiTwoParamDel by Lambda - %d, %s"), num, *str);
	});

	// DECLARE_DYNAMIC_DELEGATE �Լ� ���
	//dynamicDel.BindUFunction(this, TEXT("DynamicDelFunc"));

	// DECLARE_DYNAMIC_DELEGATE_OneParam �Լ� ���
	dynamicOneparamDel.BindUFunction(this, TEXT("SimpleOneParamDelFunc"));

	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams �Լ� ���
	dynamicMultiTwoParamDel.AddDynamic(this, &ADelegateStudy::DynamicMultiTwoParamDel1);

	
	del.BindUFunction(this, TEXT("DynamicMultiTwoParamDel2"));
	dynamicMultiTwoParamDel.Add(del);
}

// Called every frame
void ADelegateStudy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADelegateStudy::InputTest()
{
	// DECLARE_DELEGATE �� ��� �ִ� �Լ��� ȣ��
	simpleDel.ExecuteIfBound();
	// DECLARE_DELEGATE �� ��� �ִ� �Լ� ����
	simpleDel.Unbind();

	// DECLARE_DELEGATE_OneParam �� ��� �ִ� �Լ��� ȣ��
	simpleOneParamDel.ExecuteIfBound(TEXT("hi!!"));
	// DECLARE_DELEGATE_OneParam �� �Լ� ����
	simpleOneParamDel.Unbind();

	// DECLARE_MULTICAST_DELEGATE �� ��� �ִ� �Լ��� ȣ��
	multiDel.Broadcast();
	// DECLARE_MULTICAST_DELEGATE �� �Լ� ����
	multiDel.Clear();			// ���
	//multiDel.RemoveAll(this);	// �ڽ��� Ŭ������ �ִ� �Լ�
	//multiDel.Remove(delHandle);	// �ϳ��� 

	// DECLARE_MULTICAST_DELEGATE_TwoParams �� ����ִ� �Լ� ȣ��
	multiTwoParamDel.Broadcast(100, TEXT("hello"));
	// DECLARE_MULTICAST_DELEGATE_TwoParams �� �Լ� ����
	multiTwoParamDel.Clear();
	//multiTwoParamDel.RemoveAll(this);
	//multiTwoParamDel.Remove( Add �� ����� ���ϰ��� ������ �����ؼ� �� ���� )

	// DECLARE_DYNAMIC_DELEGATE �� ����ִ� �Լ� ȣ��
	dynamicDel.ExecuteIfBound();
	// DECLARE_DYNAMIC_DELEGATE �� �Լ� ����
	dynamicDel.Unbind();

	// DECLARE_DYNAMIC_DELEGATE_OneParam �� ����ִ� �Լ� ȣ��
	dynamicOneparamDel.ExecuteIfBound(TEXT("Good Morning"));
	// DECLARE_DYNAMIC_DELEGATE_OneParam �� �Լ� ����
	dynamicOneparamDel.Unbind();

	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams �� ����ִ� �Լ� ȣ��
	dynamicMultiTwoParamDel.Broadcast(2000, TEXT("Good Afternoon"));

	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams �Լ� ����
	//dynamicMultiTwoParamDel.Clear();
	//dynamicMultiTwoParamDel.RemoveAll(this);
	dynamicMultiTwoParamDel.Remove(del);
}

void ADelegateStudy::SimpleDelFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("SimpleDelFunc"));
}

void ADelegateStudy::SimpleOneParamDelFunc(FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("SimpleOneParamDelFunc - %s"), *str);
}

void ADelegateStudy::MultiDel1()
{
	UE_LOG(LogTemp, Warning, TEXT("MultiDel1"));
}

void ADelegateStudy::MultiDel2()
{
	UE_LOG(LogTemp, Warning, TEXT("MultiDel2"));
}

void ADelegateStudy::MultiTwoParamDel1(int32 num, FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("MultiTwoParamDel1 - %d, %s"), num, *str);
}

void ADelegateStudy::MultiTwoParamDel2(int32 num, FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("MultiTwoParamDel2 - %d, %s"), num, *str);
}

void ADelegateStudy::DynamicDelFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("DynamicDelFunc"));
}

void ADelegateStudy::DynamicOneParamDel(FString name)
{
	UE_LOG(LogTemp, Warning, TEXT("DynamicOneParamDel - %s"), *name);
}

void ADelegateStudy::DynamicMultiTwoParamDel1(int32 age, FString name)
{
	UE_LOG(LogTemp, Warning, TEXT("DynamicMultiTwoParamDel1 - %d, %s"), age, *name);
}

void ADelegateStudy::DynamicMultiTwoParamDel2(int32 age, FString name)
{
	UE_LOG(LogTemp, Warning, TEXT("DynamicMultiTwoParamDel2 - %d, %s"), age, *name);
}

