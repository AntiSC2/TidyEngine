/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
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