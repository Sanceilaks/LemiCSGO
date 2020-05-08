#pragma once
#include "color.h"
#include "SingletonTemplate.h"

//struct UISettings
//{
//
//};
//
//struct HackSettings
//{
//public:
//	struct EspBox
//	{
//	public:
//		bool IsActive = true;
//		Color BoxColor = Color(10, 10, 10);
//		Color NameColor = Color(255, 0, 0);
//	};
//	struct BannyHop
//	{
//	public:
//		bool isActive = true;
//	};
//}HackSet;


struct BannyHopSet
{
public:
	bool isActive = true;
};
struct EspSettings
{
public:
	bool IsActive = true;
	float BoxColor[4] = { 10, 10, 10, 130 };
	float NameColor[4] = { 255, 0, 0, 255 };
};

struct HackSettings
{
public:
	EspSettings* ESP = new EspSettings();
	BannyHopSet* BHOP = new BannyHopSet();
};

class CoreSettings : public Singleton<CoreSettings>
{
	HackSettings* HSettings = new HackSettings();
public:
	HackSettings* GetHackSettings()
	{
		return this->HSettings;
	}
};