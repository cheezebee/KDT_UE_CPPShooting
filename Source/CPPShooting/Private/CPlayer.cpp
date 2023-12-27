// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "Components/BoxComponent.h"
#include "CBullet.h"
#include "Kismet/GameplayStatics.h"
#include "CMainGameMode.h"


// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComponent �߰� 
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//BoxComponent �� RootComponent �� ������
	SetRootComponent(compBox); // �Ǵ� RootComponent = compBox;
	//Collision Enable ����(�������� �浹, ���� �浹, �� �� ���)
	compBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Object Type
	compBox->SetCollisionObjectType(ECC_GameTraceChannel3);
	//��� Response �� Ignore ����
	compBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Enemy �� Overlap ���� ����
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	
	//StaticeMeshComponent �߰�
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//compMesh �� RootComponent �� �ڽ����� ����
	compMesh->SetupAttachment(RootComponent);
	//Collision Preset �� NoCollision���� ����
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	//���(StaticMesh) �� �о�鿩�� ��������
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
	//���࿡ �� �о�鿴�ٸ�
	if (tempMesh.Succeeded())
	{
		//Mesh�� ��������
		compMesh->SetStaticMesh(tempMesh.Object);
		//ȸ����Ű��(x : 90, z : 90)
		//(Pitch=2.000000,Yaw=3.000000,Roll=1.000000)
		compMesh->SetRelativeRotation(FRotator(0, 90, 90));
		//ũ������
		compMesh->SetRelativeScale3D(FVector(4));
	}

	//�Ѿ� ������ ��������.
	ConstructorHelpers::FClassFinder<ACBullet> tempBulletFactory(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Bullet.BP_Bullet_C'"));
	if (tempBulletFactory.Succeeded())
	{
		bulletFactory = tempBulletFactory.Class;
	}

	//�Ѿ� �Ҹ� ��������.
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/star-wars-blaster.star-wars-blaster'"));
	if (tempSound.Succeeded())
	{
		fireSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// �浹 �Ǿ��� �� ȣ��Ǵ� �Լ� ���
	compBox->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::OnOverlap);

	// źâ�� �Ѿ��� ���� ����
	for (int32 i = 0; i < 5; i++)
	{
		// 1. �Ѿ��� �����Ѵ�.
		ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(bulletFactory);
		// 2. ������ �Ѿ��� źâ�� �ִ´�.
		magazine.Add(bullet);
	}

	// TArray ��� ����
	TArray<float> arrayNum;

	// �߰�
	arrayNum.Add(10);
	arrayNum.Add(20);
	arrayNum.Add(moveSpeed);

	for (int32 i = 0; i < arrayNum.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	}

	// ����
	//arrayNum.RemoveAt(1);
	arrayNum.Remove(20);

	for (int32 i = 0; i < arrayNum.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	}

	// �߰� ����
	arrayNum.Insert(100, 1);

	for (int32 i = 0; i < arrayNum.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	}
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//P = P0 + vt
	FVector p0 = GetActorLocation();

	//��, �츦 �����ϴ� ������ ���Ѵ�.
	FVector dirH = GetActorRightVector() * h;
	//��, �ϸ� �����ϴ� ������ ���Ѵ�.
	FVector dirV = GetActorUpVector() * v;
	//���� ������ ������
	FVector dir = dirH + dirV;
	//���� ������ ũ�⸦ 1�� ������.
	dir.Normalize();

	FVector vt = dir * moveSpeed * DeltaTime;
	FVector p = p0 + vt;
	SetActorLocation(p);
	

	// ����ð��� ����
	currTime += DeltaTime;
	// ���࿡ ����ð��� 0.5 ���� ũ�ٸ�
	if (currTime > 0.5f)
	{
		// �Ѿ��� �߻�
		//InputFire();
		// ����ð� �ʱ�ȭ
		currTime = 0;
	}
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//A, D Ű ������ �� ȣ��Ǵ� �Լ� ���
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::InputHorizontal);
	//W, S Ű ������ �� ȣ��Ǵ� �Լ� ���
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::InputVertical);
	//Fire �� ��ϵ� Ű�� ������ �� ȣ��Ǵ� �Լ� ���
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ACPlayer::InputFire);
}

void ACPlayer::InputHorizontal(float value)
{
	h = value;
	//UE_LOG(LogTemp, Warning, TEXT("H : %f"), value);
}

void ACPlayer::InputVertical(float value)
{
	v = value;
	//UE_LOG(LogTemp, Warning, TEXT("V : %f"), value);
}

void ACPlayer::InputFire()
{
	// �Ѿ˰���(BP_Bullet) ���� �Ѿ��� �ϳ� �����Ѵ�.
	//ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(bulletFactory);
	//if (bullet == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("bullet is null"));
	//}
	//else
	//{
	//	// ������ �Ѿ��� ���� ��ġ�� ���´�.
	//	bullet->SetActorLocation( GetActorLocation() );
	//}

	//�Ǵ�
	GetWorld()->SpawnActor<ACBullet>(bulletFactory, GetActorLocation(), GetActorRotation());

	// �Ѿ� �߻� �Ҹ�
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

void ACPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���࿡ �浹�� ���Ͱ� Enemy ���
	if (OtherActor->GetName().Contains(TEXT("Enemy")))
	{
		// GameOverWidget �����
		ACMainGameMode* currGameMode = GetWorld()->GetAuthGameMode<ACMainGameMode>();
		currGameMode->ShowGameOverUI();

		// ���콺 ������ ���̰� ����
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

		// ������ �Ͻ� ����
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// �ε��� ���� �ı�
		OtherActor->Destroy();

		// ���� �ı�
		Destroy();
	}	
}
