// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainGameMode.h"
#include "CMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CSaveData.h"
#include "CGameOverWidget.h"

ACMainGameMode::ACMainGameMode()
{
	// MainWidget Ŭ���� ��������
	ConstructorHelpers::FClassFinder<UCMainWidget> tempMainWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_MainWidget.BP_MainWidget_C'"));
	if (tempMainWidget.Succeeded())
	{
		mainWidget = tempMainWidget.Class;
	}

	// GameOverWidget Ŭ���� ��������
	ConstructorHelpers::FClassFinder<UCGameOverWidget> tempGameOverWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (tempGameOverWidget.Succeeded())
	{
		gameOverWidget = tempGameOverWidget.Class;
	}
}

void ACMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	// mainWiget ����
	mainUI = CreateWidget<UCMainWidget>(GetWorld(), mainWidget);
	// ������ Widget �� ȭ�鿡 ������
	mainUI->AddToPlayerScreen();
	// �ְ� ���� �ҷ�����
	LoadData();
}

void ACMainGameMode::AddScore(int32 value)
{
	// ���������� ������Ű��
	currScore += value;

	// �������� UI�� ����
	mainUI->UpdateCurrScoreUI(currScore);

	// ���࿡ ���������� �ְ��������� ũ�ٸ�
	if (currScore > bestSocre)
	{
		// �ְ������� ���������� ����
		bestSocre = currScore;
		// �ְ����� UI �� ����
		mainUI->UpdateBestScoreUI(bestSocre);
		// �ְ����� ����
		SaveData();
	}
}

void ACMainGameMode::SaveData()
{
	// bestScore -> CSaveData �� �ִ� saveBestScore ������ �ִ´�.

	// 1. CSaveData �� �ϳ� �����Ѵ�. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::CreateSaveGameObject(UCSaveData::StaticClass());
	// 2. ������ ���� CSaveData �� ����ȯ
	UCSaveData* saveData = Cast<UCSaveData>(saveGame);
	// 3. saveBestScore = bestScore
	saveData->saveBestScore = bestSocre;
	// 4. CSaveData �� ����
	UGameplayStatics::SaveGameToSlot(saveData, TEXT("BEST_SCORE"), 0);
}

void ACMainGameMode::LoadData()
{
	// 1. "BEST_SCORE" ���� �Ǿ� �ִ� �����͸� �ҷ��´�. (USaveGame*)
	USaveGame* loadGame = UGameplayStatics::LoadGameFromSlot(TEXT("BEST_SCORE"), 0);
	// 2. ���࿡ �� �о�Դٸ� (������ ���� �־��ٸ�)
	if (loadGame != nullptr)
	{
		// 3. �ҷ��� ��ü�� UCSaveData �� ����ȯ
		UCSaveData* loadData = Cast<UCSaveData>(loadGame);	
		// 4. bestScore = saveBestScore
		bestSocre = loadData->saveBestScore;
		// 5. �ְ� ���� UI ����
		mainUI->UpdateBestScoreUI(bestSocre);
	}
}

void ACMainGameMode::ShowGameOverUI()
{
	// GameOverWidget �� �����.
	gameOverUI = CreateWidget<UCGameOverWidget>(GetWorld(), gameOverWidget);
	// ���� Widget �� ȭ�鿡 ����.
	gameOverUI->AddToPlayerScreen();
}
