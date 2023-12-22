// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWidget* widget;

	// btnRetry �� ��������. (UWidget* �� ��ȯ)
	widget = GetWidgetFromName(TEXT("btnRetry"));
	// UButton ������ ����ȯ
	btnRetry = Cast<UButton>(widget);
	// btnRetry �� Ŭ�� �Ǿ��� �� ȣ��Ǵ� �Լ� ���
	btnRetry->OnClicked.AddDynamic(this, &UCGameOverWidget::OnClickRetry);

	// btnQuit �� ��������. (UWidget* �� ��ȯ)
	widget = GetWidgetFromName(TEXT("btnQuit"));
	// UButton������  ����ȯ
	btnQuit = Cast<UButton>(widget);
	// btnQuit �� Ŭ�� �Ǿ��� �� ȣ��Ǵ� �Լ� ���
	btnQuit->OnClicked.AddDynamic(this, &UCGameOverWidget::OnClickQuit);
}

void UCGameOverWidget::OnClickRetry()
{
	// ������ �ٽ� �ε��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainGameLevel"));
}

void UCGameOverWidget::OnClickQuit()
{
	// ���� ���� ��Ų��
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}
