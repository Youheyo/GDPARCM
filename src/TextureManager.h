#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "IconSpawner.h"
#include "ThreadPool.h"

class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;
	
public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadSingleStreamAsset(int index); //loads a single streaming asset based on index in directory
	void loadMultipleStreamAssets(IExecutionEvent* spwn);
	void loadAssetsFromDirectory(IExecutionEvent* event);
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	sf::Texture* getBaseTextureFromList(const int index);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;
	void instantiateAsTexture(String path, String assetName, bool isStreaming);

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;

	ThreadPool* pool;

	const std::string STREAMING_PATH = "Media/Streaming/";
	const std::string DATA_PATH = "Media/artwork/";

	int streamingAssetCount = 0;

	void countStreamingAssets();


};