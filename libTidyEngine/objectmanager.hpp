/*
TidyEngine
Copyright (C) 2016 Jakob Sinclair

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
Contact the author at: jakob.sinclair99@gmail.com
*/

#pragma once

class Object;
class Renderer;

#include <memory>
#include <vector>
#include "camera2d.hpp"

class ObjectManager {
public:
	ObjectManager();
	virtual ~ObjectManager();
	
	virtual void Update();
	virtual void Draw(Renderer *renderer);
	virtual void AddObject(Object *object);
	virtual void SetCamera(Camera2D *camera);
	virtual const Camera2D *GetCamera();
protected:
	std::vector<std::unique_ptr<Object>> m_Objects;
	Camera2D *m_CurrentCamera = nullptr;
};