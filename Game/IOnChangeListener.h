#pragma once

#include "stdafx.h"
#include "eScene.h"
#include "Parameter.h"

//	�C���^�[�t�F�[�X
class IOnSceneChangedListener
{
public:
	IOnSceneChangedListener() = default;
	virtual ~IOnSceneChangedListener() = default;
	virtual void onSceneChanged(const eScene scene, Parameter &parameter ,const bool stackClear) = 0;
};

