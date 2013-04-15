#ifndef DATABASE_H__
#define DATABASE_H__

#include "article.h"
#include "newsgroup.h"
template <typename newsgroup_itt_type, typename article_itt_type>
class Database {
public:
	void addArticle(shared_ptr<Article> article);
	shared_ptr<Article> getArticle(uint32_t artId, uint32_t NGId);
	void addNewsgroup(shared_ptr<Newsgroup> newsgroup);

	const newsgroup_itt_type getNewsgroupBegin();
	const newsgroup_itt_type getNewsgroupEnd();

	const article_itt_type getArticleBegin(uint32_t ngId);
	const article_itt_type getArticleEnd(uint32_t ngId);

	void deleteArticle(uint32_t artId, uint32_t ngId);
	void deleteNewsgroup(uint32_t ngId);
};



#endif
