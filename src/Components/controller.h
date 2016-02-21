/*
Copyright (C) 2015 Jakob Sinclair

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
*/

#pragma once
#include "component.h"
#include "../Core/input.h"
#include <string>

class Actor;

//This class is a base class for controller components
//It can be used but does not do anything by itself
class Controller : public Component {
	public:
		Controller();
		virtual ~Controller();

		virtual bool initialize(std::string name, Actor* parent);
		virtual bool getUpdate();
		virtual bool getDraw();

		virtual void doCommand(std::string command);
		virtual void update();

		void setInputReference(Input& inputReference);
	protected:
		Input* m_Input = nullptr;
};
