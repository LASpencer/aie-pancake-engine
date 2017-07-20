#pragma once
#include "stdafx.h"
#include "Texture.h"
#include "Audio.h"
#include "Font.h"

// Templated class for storing Audio and Texture assets identified by filepath
template<class T>
class Resource
{
public:
	Resource(const std::string& filename) : m_filename(filename) {
		m_data = std::unique_ptr<T>(new T(filename.c_str()));
	}
	~Resource()
	{ };

	std::string getFilename() {
		return m_filename;
	}

	T* get() {
		return m_data.get();
	}

	T& operator*() {
		return *m_data;
	}

	T* operator->() {
		return m_data.get();
	}

private:
	std::unique_ptr<T> m_data;
	std::string m_filename;
};

// Templated class for storing Font assets identified by filepath and size
class FontResource
{
public:
	FontResource(const std::string& filename, unsigned short height) : m_filename(filename), m_yExtent(height) {
		m_data = std::unique_ptr<aie::Font>(new aie::Font(filename.c_str(), height));
	}
	~FontResource() {};

	std::string getFilename() {
		return m_filename;
	}

	unsigned short getHeight() {
		return m_yExtent;
	}

	aie::Font* get() {
		return m_data.get();
	}

	aie::Font& operator*() {
		return *m_data;
	}

	aie::Font* operator->() {
		return m_data.get();
	}
private:
	std::unique_ptr<aie::Font> m_data;
	std::string m_filename;
	unsigned short m_yExtent;
};

typedef std::shared_ptr<Resource<aie::Audio>> AudioPtr;
typedef std::shared_ptr<FontResource> FontPtr;
typedef std::shared_ptr<Resource<aie::Texture>> TexturePtr;

/*	Resource Manager class loads and stores resources requested
by other objects

*/
class ResourceManager
{
public:
	enum ResourceType {
		texture,
		audio,
		font
	};

	ResourceManager() {};
	~ResourceManager() {};
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;


	TexturePtr getTexture(const std::string& filename);

	AudioPtr getAudio(const std::string& filename);

	FontPtr getFont(const std::string& filename, unsigned short size);

	/** Counts stored resources
	*	@param type Resource to check
	*	@return number of objects of type stored by resource manager*/
	size_t size(ResourceType type);

	// Release any unused resources
	void collectGarbage();

private:
	std::map<std::string, TexturePtr> m_textures;
	std::map<std::string, AudioPtr> m_audio;
	std::map<std::string, std::map<unsigned short, FontPtr>> m_fonts;
};