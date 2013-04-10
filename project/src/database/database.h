#ifndef DATABASE_H__
#define DATABASE_H__


class database {
public:
	int addArticle(Article article);
	Article getArticle(uint32_t artId);
	int addNewsgroup(Newsgroup newsgroup);
	vector<Newsgroup> getAllNewsgroups();
	vector<Article> getArticlesForNewsgroup(uint32_t ngId);
	int deleteArticle(uint32_t artId, uint32_t ngId);
	int deleteNewsgroup(uint32_t ngId);
};

#endif