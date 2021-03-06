#ifndef NEWSGROUP_H__
#define NEWSGROUP_H__

#include <map>
using std::map;
#include <utility>
using std::make_pair;
#include "database_exceptions.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

class Newsgroup {
private:
	map<uint32_t, shared_ptr<Article>> articles;

public:
	Newsgroup() {}
	Newsgroup(uint32_t id_, string name_): id(id_), name(name_){}
	uint32_t id; // Must be unique
	string name;

	uint32_t articleCounter = 1; // Describes the number of the next article


	void addArticle(shared_ptr<Article> article){
		article->id = articleCounter++;
		articles.insert(make_pair(article->id, article));
	}
	shared_ptr<Article> getArticle(uint32_t artId){
		auto artIt = articles.find(artId);
		if (artIt == articles.end()){
			throw ArtDoesntExistException();
		}
		return artIt->second;
	}

	void deleteArticle(uint32_t artId){
		auto artIt = articles.find(artId);
		if (artIt == articles.end()){
			throw ArtDoesntExistException();
		}
		articles.erase(artIt);
	}

	auto getArticleBegin() -> decltype(articles.cbegin()) {
		return articles.cbegin();
	}
	auto getArticleEnd() -> decltype(articles.cend()) {
		return articles.cend();
	}


};

#endif
