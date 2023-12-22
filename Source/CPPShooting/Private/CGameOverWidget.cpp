// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameOverWidget.h"
#include "Components/Button.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// btnRetry �� ��������. (UWidget* �� ��ȯ)
	UWidget* widget = GetWidgetFromName(TEXT("btnRetry"));
	// UButton ������ ����ȯ
	btnRetry = Cast<UButton>(widget);
	// btnRetry �� Ŭ�� �Ǿ��� �� ȣ��Ǵ� �Լ� ���
	btnRetry->OnClicked.AddDynamic(this, &UCGameOverWidget::OnClickRetry);
}

void UCGameOverWidget::OnClickRetry()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClickRetry"));
}
