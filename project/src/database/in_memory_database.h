#ifndef IN_MEMORY_DATABASE_H__
#define IN_MEMORY_DATABASE_H__


class InMemoryDatabase : public Database {
public:
	void addArticle(shared_ptr<Article> article){
		auto ngIt = newsgroups.find(article->newsgroupId);
		if (ngIt == newsgroups.end){
			throw NGDoesntExistException();
		}
		auto artIt = articles.find(article->id);
		if (ngIt != articles.end){
			throw NGAlreadyExistsException();
		}
		articles.emplace(article->id, article);

	}
	Article getArticle(uint32_t artId);
	void addNewsgroup(Newsgroup newsgroup);
	vector<Newsgroup> getAllNewsgroups();
	vector<Article> getArticlesForNewsgroup(uint32_t ngId);
	void deleteArticle(uint32_t artId, uint32_t ngId);
	void deleteNewsgroup(uint32_t ngId);
};

private:


	map<uint32_t, shared_ptr<Newsgroup>> newsgroups;
	map<uint32_t, shared_ptr<Article>> articles;

#endif
