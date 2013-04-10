#ifndef DATABASE_H__
#define DATABASE_H__


class Database {
public:
	void addArticle(shared_ptr<Article> article);
	shared_ptr<Article> getArticle(uint32_t artId, uint32_t NGId);
	void addNewsgroup(shared_ptr<Newsgroup> newsgroup);

	const auto getNewsgroupIterator();
	const auto getNewsgroupEnd();

	const auto getArticleIterator(uint32_t ngId);
	const auto getArticleEnd(uint32_t ngId);

	void deleteArticle(uint32_t artId, uint32_t ngId);
	void deleteNewsgroup(uint32_t ngId);
};


struct NGDoesntExistException{};
struct ArtDoesntExistException{};
struct NGAlreadyExistsException{};

#endif
