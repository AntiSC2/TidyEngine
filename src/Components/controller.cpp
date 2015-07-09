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

#include "controller.h"

Controller::Controller() {

}

Controller::~Controller() {

}

bool Controller::initialize(std::string name) {
    m_Name = name;
    return true;
}

bool Controller::getUpdate() {
    return true; 
}

bool Controller::getDraw() {
    return false;
}

void Controller::update() {
    ; 
}

void Controller::setInputReference(Input& inputReference) {
    m_Input = &inputReference;
}
