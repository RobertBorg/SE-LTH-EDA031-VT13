#ifndef NEWSGROUP_H__
#define NEWSGROUP_H__

#include <map>
using std::map;
#include <utility>
using std::make_pair;
#include "database_exeptions.h"

class Newsgroup {
private:
	map<uint32_t, shared_ptr<Article>> articles;

public:
	Newsgroup(string name_, uint32_t id_): name(name_), id(id_){}
	string name;
	uint32_t id; // Must be unique

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
