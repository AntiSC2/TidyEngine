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

#include <fstream>
#include <vorbis/vorbisfile.h>
#include <vector>
#include "error.hpp"
#include "iomanager.hpp"

IOManager IO;

IOManager::IOManager()
{
	;
}

IOManager::~IOManager()
{

}

FIBITMAP *IOManager::LoadImage(std::string filepath)
{
	if (filepath.find(".png") != std::string::npos)
		return FreeImage_Load(FIF_PNG, filepath.c_str(), PNG_DEFAULT);
	else if (filepath.find(".bmp") != std::string::npos)
		return FreeImage_Load(FIF_BMP, filepath.c_str(), BMP_DEFAULT);
	else if (filepath.find(".jpeg") != std::string::npos)
		return FreeImage_Load(FIF_JPEG, filepath.c_str());

	printf("Warning: image %s has an unsupported file format!",
		       filepath.c_str());
	return nullptr;
}

std::string IOManager::ReadFile(std::string filepath)
{
	std::ifstream source(filepath);
	if (source.fail()) {
		printf("Warning: failed to open %s!", filepath.c_str());
		return "";
	}

	std::string source_contents = "";
	std::string line = "";

	while (std::getline(source, line))
		source_contents += line + '\n';

	source.close();
	return source_contents;
}

size_t IfsRead(void *out, size_t size, size_t bytesize, void *in)
{
	auto& stream = *static_cast<std::ifstream *> (in);
	stream.read(static_cast<char *> (out), size * bytesize);

	return stream.gcount();
}

int IfsClose(void *in)
{
	auto& stream = *static_cast<std::ifstream *> (in);
	stream.close();

	return 0;
}

bool IOManager::LoadVorbis(std::string filepath, Sample *out)
{
	std::ifstream source(filepath, std::ifstream::binary);
	
	if (source.is_open() == false) {
		printf("Warning: failed to open %s!", filepath.c_str());
		return false;
	}

	ov_callbacks cbs {IfsRead, nullptr, IfsClose, nullptr};
	OggVorbis_File vorbis;

	if (ov_open_callbacks(&source, &vorbis, nullptr,
	    0, cbs) < 0) {
		ov_clear(&vorbis);
		return false;
	}

	vorbis_info *info = ov_info(&vorbis, -1);	
	char buffer[4096];
	int current_section;
	std::vector<char> pcm;

	while (true) {
		long ret = ov_read(&vorbis, buffer, sizeof(char) * 4096, 
		                   0, 2, 1, &current_section);
		if (ret == 0) {
			break;
		} else if (ret < 0) {
			ov_clear(&vorbis);
			printf("Warning: error in stream %s!", filepath.c_str());
			return false;
		} else {
			for (int i = 0; i < ret; i++)
				pcm.push_back(buffer[i]);
		}
	}
	
	ALenum format = (info->channels > 1) ? AL_FORMAT_STEREO16 :
	                                       AL_FORMAT_MONO16;

	out->CreateBuffer(format, pcm.data(), pcm.size(), info->rate);
	ov_clear(&vorbis);
	return true;
}