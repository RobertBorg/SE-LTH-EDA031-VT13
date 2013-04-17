#ifndef DATABASE_H__
#define DATABASE_H__

#include "article.h"
#include "newsgroup.h"
template <typename newsgroup_itt_type, typename article_itt_type>
class Database {
public:
	typedef newsgroup_itt_type ngIt;
	typedef article_itt_type artIt;
	virtual void addArticle(shared_ptr<Article> article) = 0;
	virtual shared_ptr<Article> getArticle(uint32_t artId, uint32_t NGId) = 0;
	virtual void addNewsgroup(shared_ptr<Newsgroup> newsgroup) = 0;

	virtual auto getNewsgroupBegin() -> newsgroup_itt_type = 0;
	virtual auto getNewsgroupEnd() -> newsgroup_itt_type = 0;

	virtual auto getArticleBegin(uint32_t ngId) -> article_itt_type = 0;
	virtual auto getArticleEnd(uint32_t ngId) -> article_itt_type = 0;

	virtual void deleteArticle(uint32_t artId, uint32_t ngId) = 0;
	virtual void deleteNewsgroup(uint32_t ngId) = 0;
};

class DummyDatabase : public Database< map<uint32_t, shared_ptr<Newsgroup> >::const_iterator, map<uint32_t,shared_ptr<Article> >::const_iterator> {
};

#endif
