#ifndef IN_MEMORY_DATABASE_H__
#define IN_MEMORY_DATABASE_H__
#include "database.h"
#include "database_exceptions.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

class InMemoryDatabase : public Database< map<uint32_t, shared_ptr<Newsgroup> >::const_iterator, map<uint32_t, shared_ptr<Article> >::const_iterator > {
public:
	void addArticle(shared_ptr<Article> article){
		auto ngIt = newsgroupsById.find(article->newsgroupId);
		if (ngIt == newsgroupsById.end()){
			throw NGDoesntExistException();
		}
		ngIt->second->addArticle(article);
	}

	shared_ptr<Article> getArticle(uint32_t artId, uint32_t NGId){
		auto ngIt = newsgroupsById.find(NGId);
		if (ngIt == newsgroupsById.end()){
			throw NGDoesntExistException();
		}
		return ngIt->second->getArticle(artId);
	}


	void addNewsgroup(shared_ptr<Newsgroup> newsgroup){
		auto ngIt = newsgroupsByName.find(newsgroup->name);

		if (ngIt != newsgroupsByName.end()){
			throw NGAlreadyExistsException();
		}
		newsgroup->id = NGCounter;
		NGCounter++;
		newsgroupsByName.insert(make_pair(newsgroup->name, newsgroup));
		newsgroupsById.insert(make_pair(newsgroup->id, newsgroup));
	}

	map<uint32_t, shared_ptr<Newsgroup>>::const_iterator getNewsgroupBegin() {
		return newsgroupsById.cbegin();
	}

	map<uint32_t, shared_ptr<Newsgroup>>::const_iterator getNewsgroupEnd() {
		return newsgroupsById.cend();
	}

	map<uint32_t, shared_ptr<Article>>::const_iterator getArticleBegin(uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupsById.end()){
			throw NGDoesntExistException();
		}
		return ngIt->second->getArticleBegin();
	}
	
	map<uint32_t, shared_ptr<Article>>::const_iterator getArticleEnd(uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupsById.end()){
			throw NGDoesntExistException();
		}
		return ngIt->second->getArticleEnd();
	}


	void deleteArticle(uint32_t artId, uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupsById.end()){
			throw NGDoesntExistException();
		}
		ngIt->second->deleteArticle(artId);
	}

	void deleteNewsgroup(uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupsById.end()){
			throw NGDoesntExistException();
		}
		auto ngIt2 = newsgroupsByName.find(ngIt->second->name);
		newsgroupsByName.erase(ngIt2);
		newsgroupsById.erase(ngIt);
	}
private:
	uint NGCounter = 1;
	map<string, shared_ptr<Newsgroup>> newsgroupsByName;
	map<uint32_t, shared_ptr<Newsgroup>> newsgroupsById;
};


#endif
