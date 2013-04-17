#ifndef ON_FILE_DATABASE_H__
#define ON_FILE_DATABASE_H__

#include <iostream>
using std::cout;
using std::endl;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "../wireprotocol/string_p.h";

/**
--  Fstream works like the standard fstream, but you can put a path object instead of string as first parameter.

-- Directory structure

 		database/
 			max 		-- file that contains an uint that tells the last ng-ID created in this database
 			NGID1/
 				max    -- file that contains an uint that tells the last art-ID created In this Newsgroup
 			NGID2/
 				max
 				ArtID1   -- file that contains three string_p, title, author and text
 			NGID3/
 				max
 				ArtID1
 				ArtID2


NGID1 is a number
ArtID1 is a number

**/

class OnFileDatabase : public Database {
public:

	OnFileDatabase(){
		p("database");
		path ngCountFile("database/max");
		if (!exists(p)){
			cout << "Database not found" << endl;
			create_directory(p);
			ngCounter = 0;

		} else if (!is_directory(p){
			cout << "Database found but is not a directory" << endl;
			exit(1);
		} else {
			// P is a directory
			// Each folder in P represents a newsgroup
			// just continue
		}
		if (exists(ngCountFile)){
			if (is_directory(ngCountFile)){

			}
			fstream stream;
			stream.open(ngCountFile, fstream::out);
			stream >> ngCounter;
			stream.close();
		} else {
			fstream stream;
			stream.open(ngCountFile, fstream::in | fstream::trunc);
			ngCounter = 0;
			stream << ngCounter;
			stream.close();
		}
	}
	void addArticle(shared_ptr<Article> article){
		string number = to_string(article.newsgroupId);
		string pathStr("database");
		pathStr.append("/");
		pathStr.append(number);
		path ngPath(pathStr);

		if (!exists(ngPath)){
			throw NGDoesntExistException();
		} else {
			uint artCounter;
			pathStr.append("/max");
			fstream stream;
			stream.open(pathStr, fstream::out); // Open max file to read artcounter
			stream >> artCounter;
			stream.close();
			artCounter++;
			stream.open(pathStr, fstream::in | fstream::trunc); // Open max file to write artcounter++
			stream << artCounter;
			stream.close();

			string artPath("database/"));
			artPath.append(number);
			artPath.append("/");
			artPath.append(to_string(artCounter));
			if (!exists(artPath)){
				stream.open(artPath, fstream::in | fstream:trunc);
				stream << string_p(article->title) << string_p(article->author) << string_p(article->text);
				stream.close();
			}
		}
	}


	shared_ptr<Article> getArticle(uint32_t artId, uint32_t NGId){
		path artPath("database/");
		artPath.append(to_string(NGId));
		if (!exists(artPath)){
			throw NGDoesntExistException();
		}
		artPath.append("/");
		artPath.append(to_string(artId));
		if (!exists(artPath)){
			throw ArtDoesntExistException();
		}
		fstream stream;
		stream.open(artPath, fstream::out);
		shared_ptr<Article> article(new Article());
		string_p title, author, text;
		stream >> title >> author >> text;
		article->title = title;
		article->author = author;
		article->text = text;
		return article;
	}


	void addNewsgroup(shared_ptr<Newsgroup> newsgroup){
		string number = to_string(newsgroup.Id);
		string pathStr("database");
		pathStr.append("/");
		pathStr.append(number);
		path ngPath(pathStr);

		if (exists(ngPath)){
			throw NGAlreadyExistsException();
		}
		create_directory(ngPath);
		pathStr.append("/max");
		fstream stream;
		stream.open(pathStr, fstream::in | fstream:trunc);
		uint artCounter = 1;
		stream << artCounter;
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
		string number = to_string(ngId);
		string pathStr("database");
		pathStr.append("/");
		pathStr.append(number);
		path ngPath(pathStr);

		if (!exists(ngPath)){
			throw NGDoesntExistException();
		}
		string artNum = to_string(artId);
		pathStr.append("/");
		pathStr.append(artNum);
		if (!exists(ngPath)){
			throw ArtDoesntExistException();
		}

		remove_all(ngPath);
	}

	void deleteNewsgroup(uint32_t ngId){
		string number = to_string(newsgroup.Id);
		string pathStr("database");
		pathStr.append("/");
		pathStr.append(number);
		path ngPath(pathStr);

		if (!exists(ngPath)){
			throw NGDoesntExistException();
		}
		remove_all(ngPath);
	}

private:
	path p;
	uint ngCounter;
};

class ArticleIterator {

	ArticleIterator(uint32_t ngId){
		string pathstr = "database/";
		pathstr.append = to_string(ngId);
		path ngPath(pathstr);
		dirItr(ngPath);
	}

	ArticleIterator& ArticleIterator::operator++() {
        ++dirItr;
        return *this;
    }

	bool ArticleIterator::operator==(const ArticleIterator& ai) const {
        return dirItr == ai.dirItr;
    }
    bool ArticleIterator::operator!=(const ArticleIterator& ai) const {
        return !(*this == ai);
    }

    shared_ptr<Article> ArticleIterator::operator*() {
    	directory_entry *entry = *dirItr;
    	path p = entry->path();
    	fstream stream(p, fstream::out);

    	shared_ptr<Article> art(new Article());

    	string_p title, author, text;
    	stream << title << author << text;
    	art->title = title;
    	art->author = author;
    	art->text = text;

    	return art;
    }


private:
	directory_iterator dirItr;
};



#endif
