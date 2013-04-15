#ifndef ON_FILE_DATABASE_H__
#define ON_FILE_DATABASE_H__


class OnFileDatabase : public Database {
public:
	void addArticle(shared_ptr<Article> article){
	}

	Article getArticle(uint32_t artId, uint32_t NGId){
	}


	void addNewsgroup(shared_ptr<Newsgroup> newsgroup){
	}

	const auto getNewsgroupBegin(){
	}
	const auto getNewsgroupEnd(){
	}

	const auto getArticleIterator(uint32_t ngId){
	}
	const auto getArticleEnd(uint32_t ngId){
	}


	void deleteArticle(uint32_t artId, uint32_t ngId){
	}

	void deleteNewsgroup(uint32_t ngId){
		
	}
};

private:

#endif
