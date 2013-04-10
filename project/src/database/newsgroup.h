#ifndef NEWSGROUP_H__
#define NEWSGROUP_H__


class Newsgroup {
public:
	Newsgroup(string name_, uint32_t id_): name(name_), id(id_){}
	vector<Article> articles;
	string name;
	uint32_t id; // Must be unique

	uint32_t articleCounter = 1; // Describes the number of the next article


	void addArticle(shared_ptr<Article> article){
		article->id = articleCounter;
		articles.emplace(article->id, article);
		ngIt->articleCounter++;
	}
	shared_ptr<Article> getArticle(uint32_t artId){
		auto artIt = articles.find(artId);
		if (artIt == articles.end){
			throw ArtDoesntExistException();
		}
		return artIt;
	}

	void deleteArticle(uint32_t artId){
		auto artIt = articles.find(artId);
		if (artIt == articles.end){
			throw ArtDoesntExistException();
		}
		articles.erase(artIt);
	}

	const auto getArticleIterator(){
		return articles.cbegin();
	}
	const auto getArticleEnd(){
		return articles.cend();
	}


private:
	map<uint32_t, shared_ptr<Article>> articles;
};

#endif
