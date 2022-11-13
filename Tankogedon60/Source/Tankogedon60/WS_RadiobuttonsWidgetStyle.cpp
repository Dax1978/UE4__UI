// Fill out your copyright notice in the Description page of Project Settings.


#include "WS_RadiobuttonsWidgetStyle.h"

FWS_RadiobuttonsStyle::FWS_RadiobuttonsStyle()
{
	// � UE ���� ���������� ���������� ������, ������� ������������ � ����� UE
	// � �������� �� ��� (�� ���� ������ 1-��: UE UI / Lesson05 / 38:10)
	// � ��������������� �������� ����� �������� ����� �� ���������� �����:
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("RadioButton");
	TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalUnderlinedText");
	// ����� ���� ��������� ����� ������, ����� ��� ������-�����, � ������ �� ����������. ��� ����� �� �����.

	// ������ � ������������ �� ������ ����� �� ��������� FCoreStyle, ����� ��� ����� ����� ��������� ���������
}

FWS_RadiobuttonsStyle::~FWS_RadiobuttonsStyle()
{
}

// �� �������� ����� ��� ������ �� ����������� (UE UI / Lesson05 / 29:20)
const FName FWS_RadiobuttonsStyle::TypeName(TEXT("FWS_RadiobuttonsStyle"));

// ��� �����, ������� ����� �������������� �� ���������
const FWS_RadiobuttonsStyle& FWS_RadiobuttonsStyle::GetDefault()
{
	// ��� ������� �� ����� �������� ��������, ��� �� ����� ��������� �� ����������� (UE UI / Lesson05 / 30:25)
	static FWS_RadiobuttonsStyle Default;
	return Default;
}

// �������� ��� �������, ��� ������ �����
void FWS_RadiobuttonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them

	// ������� ������������:
	FSlateWidgetStyle::GetResources(OutBrushes);

	// (UE UI / Lesson05 / 36:10)
	// ��� ����� ������ ���������� �����, �� ����� ��������� ����� 2 ����:
	// 
	// 1. ���� � ��������� � ����� ����� ����� �� ���� �����
	// (� ���� ������ ��� CheckBoxstyle � TextBlockStyle), �.�. ��� ��� ����������� �� FSlateWidgetStyle
	// �� �� ���� ���������� ����� ������� GetResources:
	CheckBoxStyle.GetResources(OutBrushes);
	TextBlockStyle.GetResources(OutBrushes);

	// 2. ���� ���������� FSlateBrush, �� ����� �������� ��� ������� � ���� ������
	// � ������� � header �����:
	// UPROPERTY(EditAnywhere, Category = Appearance)
	// FSlateBrush BackgroundBrush;
	// �.�. ������� ��� ����� ��������� ��� background, � ������� ������� �������� ��� ����
	// ����� � ���������� OutBrushes ���� �������� ��� BackgroundBrush, ��� ���:
	// OutBrushes.Add(&BackgroundBrush);
	// 
	// ��������������, ���� ����� ������ ����� ����� ������, ���� ������ �� ���, ����� ������� ��������.
	//
	
}

