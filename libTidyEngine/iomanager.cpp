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
		printf("Warning: failed to open %s!\n", filepath.c_str());
		return "";
	}

	std::string source_contents = "";
	std::string line = "";

	while (std::getline(source, line))
		source_contents += line + '\n';

	source.close();
	return source_contents;
}

Sample IOManager::LoadVorbis(std::string filepath) {
	std::ifstream source(filepath, std::ifstream::binary);
	if (source.fail()) {
		Error e("Warning: failed to open " + filepath + '!');
		throw e;
	}

	source.seekg(0, source.end);
	int length = source.tellg();
	source.seekg(0, source.beg);

	char *pcm = new char[length];
	char *buffer = new char[4096];
	source.read(pcm, length);
	printf("%d", length);

	if (source.fail()) {
		delete[] pcm;
		delete[] buffer;
		source.close();
		Error e("Warning: failed to read " + filepath + '!');
		throw e;
	}

	source.close();
	OggVorbis_File vorbis;

	if (ov_open_callbacks(pcm, &vorbis, nullptr,
	    0, OV_CALLBACKS_NOCLOSE) < 0) {
		delete[] pcm;
		delete[] buffer;
		Error e("Warning: " + filepath + " is not in ogg format!");
		throw e;
	}

	vorbis_info *info = ov_info(&vorbis, -1);
	printf("Channel: %d\nFreq: %d", info->channels, info->rate);

	int current_section;
	int pos = 0;
	while (true) {
		long ret = ov_read(&vorbis, buffer, sizeof(char) * length, 
		                   0, 2, 1, &current_section);
		if (ret == 0) {
			break;
		} else if (ret < 0) {
			delete[] pcm;
			Error e("Warning: error in stream " + filepath + '!');
			throw e;
		} else {
			int i = pos;
			int offset = i;
			pos += ret;
			for (;i < pos; i++)
				pcm[i] = buffer[i - offset];
		}
	}

	if (info->channels >= 2) {
		Sample sound(AL_FORMAT_STEREO16, pcm, length, info->rate);
		delete[] pcm;
		ov_clear(&vorbis);
		return sound;
	}
	else if (info->channels < 2) {
		Sample sound(AL_FORMAT_MONO16, pcm, length, info->rate);
		delete[] pcm;
		ov_clear(&vorbis);
		return sound;
	}
	delete[] pcm;
	ov_clear(&vorbis);
	Error e("Warning: failed to read " + filepath + '!');
	throw e;
}
