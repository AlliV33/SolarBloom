#pragma once
#include "Ally.h"

class Station : public Ally
{
public:
	void OnInitialize() override;
	void LoadAnimation() override;
};