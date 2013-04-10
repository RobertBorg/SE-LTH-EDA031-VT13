#ifndef ARTICLE_H__
#define ARTICLE_H__

class Article {
public:
	string title;
	string author;
	string text;
	uint32_t id; // Unique in the newsgroup
	uint32_t newsgroupId; // The newsgroupid this article belongs to

};

#endif
