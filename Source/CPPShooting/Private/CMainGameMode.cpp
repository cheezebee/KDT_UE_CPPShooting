// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainGameMode.h"

void ACMainGameMode::AddScore(int32 value)
{
	// ���������� ������Ű��
	currScore += value;
	
	UE_LOG(LogTemp, Warning, TEXT("currScore : %d"), currScore);
}
