#ifndef ARTICLE_H__
#define ARTICLE_H__

class Article {
public:
	Article() {}
	Article(uint32_t id_, string title_): id(id_), title(title_){}
	uint32_t id; // Unique in the newsgroup
	string title;

	string author;
	string text;
	uint32_t newsgroupId; // The newsgroupid this article belongs to
};

#endif
