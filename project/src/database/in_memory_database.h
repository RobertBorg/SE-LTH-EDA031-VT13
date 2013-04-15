#ifndef IN_MEMORY_DATABASE_H__
#define IN_MEMORY_DATABASE_H__


class InMemoryDatabase : public Database<decltype(map<uint32_t, shared_ptr<Newsgroup>>.cbegin()),decltype(map<uint32_t, shared_ptr<Article>>::cbegin()) {
public:
	void addArticle(shared_ptr<Article> article){
		auto ngIt = newsgroupsById.find(article->newsgroupId);
		if (ngIt == newsgroupsById.end){
			throw NGDoesntExistException();
		}
		ngIt->addArticle(article);
	}

	Article getArticle(uint32_t artId, uint32_t NGId){
		auto ngIt = newsgroupsById.find(article->newsgroupId);
		if (ngIt == newsgroups.end){
			throw NGDoesntExistException();
		}
		return ngIt->getArticle(artId);
	}


	void addNewsgroup(shared_ptr<Newsgroup> newsgroup){
		auto ngIt = newsgroupsByName.find(newsgroup->name);

		if (ngIt != newsgroupsByName.end){
			throw NGAlreadyExistsException();
		}
		newsgroup->id = NGCounter;
		NGCounter++;
		newsgroupsByName.emplace(newsgroup->name, newsgroup);
		newsgroupsById.emplace(newsgroup->id, newsgroup);
	}

	const auto getNewsgroupBegin(){
		return newsgroupsById.cbegin();
	}
	const auto getNewsgroupEnd(){
		return newsgroupsById.cend();
	}

	const auto getArticleBegin(uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupsById.end){
			throw NGDoesntExistException();
		}
		return ngIt->getArticleBegin();
	}
	const auto getArticleEnd(uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupsById.end){
			throw NGDoesntExistException();
		}
		return ngIt->getArticleEnd();
	}


	void deleteArticle(uint32_t artId, uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupsById.end){
			throw NGDoesntExistException();
		}
		ngIt->deleteArticle(artId);
	}

	void deleteNewsgroup(uint32_t ngId){
		auto ngIt = newsgroupsById.find(ngId);
		if (ngIt == newsgroupId.end){
			throw NGDoesntExistException();
		}
		auto ngIt2 = newsgroupsByName.find(ngIt->name);
		newsgroupsByName.erase(ngIt2);
		newsgroupsById.erase(ngIt);

		
	}
};

private:
	uint NGCounter = 1;
	map<string, shared_ptr<Newsgroup>> newsgroupsByName
	map<uint32_t, shared_ptr<Newsgroup>> newsgroupsById;
	map<uint32_t, shared_ptr<Article>> articles;

#endif
