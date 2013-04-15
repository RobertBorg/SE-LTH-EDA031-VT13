#ifndef DATABASE_H__
#define DATABASE_H__

#include "article.h"
#include "newsgroup.h"
template <typename newsgroup_itt_type, typename article_itt_type>
class Database {
public:
	virtual void addArticle(shared_ptr<Article> article) = 0;
	virtual shared_ptr<Article> getArticle(uint32_t artId, uint32_t NGId) = 0;
	virtual void addNewsgroup(shared_ptr<Newsgroup> newsgroup) = 0;

	virtual const newsgroup_itt_type getNewsgroupBegin() = 0;
	virtual const newsgroup_itt_type getNewsgroupEnd() = 0;

	virtual const article_itt_type getArticleBegin(uint32_t ngId) = 0;
	virtual const article_itt_type getArticleEnd(uint32_t ngId) = 0;

	virtual void deleteArticle(uint32_t artId, uint32_t ngId) = 0;
	virtual void deleteNewsgroup(uint32_t ngId) = 0;
};



#endif
