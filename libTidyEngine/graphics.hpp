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

struct GLFWwindow;
class Font;
class Shader;
class IRenderer;

#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "screen.hpp"
#include "system.hpp"

class Graphics: public ISystem {
public:
	Graphics() = default;
	Graphics(uint16_t width, uint16_t height, const char *title, int gl_major, int gl_minor);
	virtual ~Graphics() = default;

	void Initialize(uint16_t width, uint16_t height, const char *title, int gl_major, int gl_minor);
	virtual std::string GetType();
	virtual void Execute(bool fixed = false);

	template<typename R, typename ...Args>
	R &CreateRenderer(Args &&...args);
	void AddRenderer(std::unique_ptr<IRenderer> &&renderer, std::type_index index);
	template<typename R>
	R &GetRenderer();

	bool LoadShaders(std::string name, std::string v, std::string f,
			std::vector<std::string> attributes = {});
	Shader *GetShader(std::string name);
	GLFWwindow *GetWindow();
	void Clear();
	void Present();
private:	
	Screen m_Screen;
	std::map<std::type_index, std::unique_ptr<IRenderer>> m_Renderers;
	std::unordered_map<std::string, std::unique_ptr<Shader>> m_Shaders;
};

template<typename R, typename ...Args>
R& Graphics::CreateRenderer(Args &&...args)
{
	static_assert(std::is_base_of<IRenderer, R>::value, "Error: tried to create a non-renderer for graphics!\n");
	R *rend_p = new R(std::forward<Args>(args)...);
	R &r = *rend_p;

	AddRenderer(std::unique_ptr<IRenderer>(static_cast<IRenderer*>(rend_p)), std::type_index(typeid(R)));

	return r;
}

template<typename R>
R &Graphics::GetRenderer()
{
	static_assert(std::is_base_of<IRenderer, R>::value, "Error: tried to retrieve non-system object from manager!\n");
	if (m_Renderers.find(std::type_index(typeid(R))) == m_Renderers.end())
		throw std::runtime_error("Error: could not find system of that type in manager!\n");
	auto &rend = static_cast<R&>(*m_Renderers[std::type_index(typeid(R))].get());
	return rend;
}