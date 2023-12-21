// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainGameMode.h"
#include "CMainWidget.h"

ACMainGameMode::ACMainGameMode()
{
	// MainWidget Ŭ���� ��������
	ConstructorHelpers::FClassFinder<UCMainWidget> tempMainWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_MainWidget.BP_MainWidget_C'"));
	if (tempMainWidget.Succeeded())
	{
		mainWidget = tempMainWidget.Class;
	}
}

void ACMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	// mainWiget ����
	mainUI = CreateWidget<UCMainWidget>(GetWorld(), mainWidget);
	// ������ Widget �� ȭ�鿡 ������
	mainUI->AddToPlayerScreen();
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
	}
}
