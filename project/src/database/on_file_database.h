#ifndef ON_FILE_DATABASE_H__
#define ON_FILE_DATABASE_H__

#include <iostream>
using std::cout;
using std::endl;

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace boost::filesystem;
using boost::filesystem::fstream;

#include "../wireprotocol/string_p.h"
#include <utility>
using std::make_pair;

#include <string>
using std::string;

#include <cstdlib>

#include <vector>
using std::vector;

#include <algorithm>
using std::for_each;
using std::sort;

/**
--  fstream works like the standard fstream, but you can put a path object instead of string as first parameter.

-- Directory structure

 		database/
 			max 		-- file that contains an uint that tells the last ng-ID created in this database
 			NGID1/
 				name  	-- Name of the newsgroup
 				max    -- file that contains an uint that tells the last art-ID created In this Newsgroup
 			NGID2/
 				name
 				max
 				ArtID1   -- file that contains three string_p, title, author and text
 			NGID3/
 				name
 				max
 				ArtID1
 				ArtID2


NGID1 is a number
ArtID1 is a number

**/

//forward declarations

class ArticleIterator {
public:
	ArticleIterator() : dirItr() {}

	ArticleIterator(uint32_t ngId) {
		string pathstr = "database/";
		pathstr.append(std::to_string(ngId));
		path ngPath(pathstr);
		if (!exists(ngPath)){
			throw NGDoesntExistException();
		}
		dirItr = directory_iterator(ngPath);
		skipSome();
	}

	void skipSome() {
    	while(dirItr != directory_iterator() && (dirItr->path().filename() == "max" || dirItr->path().filename() == "name") ) {
    		++dirItr;
    	}
    }

	ArticleIterator& operator++() {
        ++dirItr;
        skipSome();
        return *this;
    }

	bool operator==(const ArticleIterator& ai) const {
        return dirItr == ai.dirItr;
    }
    bool operator!=(const ArticleIterator& ai) const {
        return !(*this == ai);
    }

    const pair<uint32_t, shared_ptr<Article> > operator*() {
    	directory_entry *entry = &(*dirItr);
    	path p = entry->path();
    	fstream stream;

    	stream.open(p, fstream::in);
    	shared_ptr<Article> art(new Article());

    	string_p title, author, text;
    	stream >> title >> author >> text;
    	stream.close();
    	art->title = title;
    	art->author = author;
    	art->text = text;
    	int iid = atoi(p.filename().c_str());
    	uint32_t id = static_cast<uint32_t>(iid);
    	art->id = id;

    	return make_pair(id, art);
    }
private:
	directory_iterator dirItr;
};

class NGIterator {
public:
	NGIterator() : dirItr() {}

	NGIterator(string path_) : dirItr(path(path_)) {
		skipSome();
	}

	NGIterator& operator++() {
        ++dirItr;
        skipSome();
        return *this;
    }

    void skipSome() {
    	while(dirItr != directory_iterator() && (dirItr->path().filename() == "max" || dirItr->path().filename() == "name") ) {
    		++dirItr;
    	}
    }

	bool operator==(const NGIterator& ni) const {
        return dirItr == ni.dirItr;
    }
    bool operator!=(const NGIterator& ni) const {
        return !(*this == ni);
    }


    const pair<uint32_t, shared_ptr<Newsgroup> > operator*() {
    	directory_entry *entry = &(*dirItr);

    	

    	path p = entry->path();
		int iid = atoi(p.filename().c_str());
    	uint32_t id = static_cast<uint32_t>(iid);
		path test("/name");
    	p += test;


    	boost::filesystem::fstream stream;
    	stream.open(p, fstream::in);
    	string_p name;
    	stream >> name;

    	shared_ptr<Newsgroup> ng(new Newsgroup());
    	ng->id = id;
    	ng->name = name;

    	return make_pair(id, ng);
    }

private:
	directory_iterator dirItr;
};


class OnFileDatabase : public Database <vector<pair<uint32_t, shared_ptr<Newsgroup>>>::const_iterator, vector<pair<uint32_t, shared_ptr<Article>>>::const_iterator > {
public:

	OnFileDatabase() : p("database") {
		path ngCountFile("database/max");
		if (!exists(p)){
			cout << "Database not found, creating database." << endl;
			create_directory(p);
			if (!exists(p)){
				cout << "Unable to create database, exiting." << endl;
				exit(1);
			}

		} else if (!is_directory(p)){
			cout << "Database found but is not a directory" << endl;
			exit(1);
		} else {
			// P is a directory
			// Each folder in P represents a newsgroup
			// just continue
		}
		if (!exists(ngCountFile)){
			cout << "Creating database/max" << endl;
			fstream stream;
			stream.open(ngCountFile, fstream::binary | fstream::out | fstream::trunc);
			num_p ngCounter(1);
			stream << ngCounter;
			stream.close();
		}
	}
	void addArticle(shared_ptr<Article> article){
		string number = std::to_string(article->newsgroupId);
		string pathStr("database");
		pathStr.append("/");
		pathStr.append(number);
		path ngPath(pathStr);

		if (!exists(ngPath)){
			throw NGDoesntExistException();
		} else {
			num_p artCounter;
			pathStr.append("/max");
			fstream stream;
			stream.open(pathStr, fstream::binary | fstream::in); // Open max file to read artcounter
			stream >> artCounter;
			stream.close();

			string artPath("database/");
			artPath.append(number);

			artPath.append("/");
			artPath.append(std::to_string(artCounter));
			if (!exists(artPath)){
				stream.open(artPath, fstream::binary | fstream::out | fstream::trunc);
				stream << string_p(article->title) << string_p(article->author) << string_p(article->text);
				stream.close();
			}

			artCounter.value++;
			stream.open(pathStr, fstream::binary | fstream::out | fstream::trunc); // Open max file to write artcounter++
			stream << artCounter;
			stream.close();

			
			
		}
	}


	shared_ptr<Article> getArticle(uint32_t artId, uint32_t NGId){
		string artString = "database/";
		artString.append(std::to_string(NGId));

		path artPath(artString);
		if (!exists(artPath)){
			throw NGDoesntExistException();
		}
		artString.append("/");
		artString.append(std::to_string(artId));
		path artPath2(artString);
		if (!exists(artPath2)){
			throw ArtDoesntExistException();
		}
		fstream stream;
		stream.open(artPath2, fstream::binary | fstream::in);
		shared_ptr<Article> article(new Article());
		string_p title, author, text;
		stream >> title >> author >> text;
		article->title = title;
		article->author = author;
		article->text = text;
		return article;
	}


	void addNewsgroup(shared_ptr<Newsgroup> newsgroup){
		string maxPath = "database/max";
		path max(maxPath);
		fstream stream;
		// Read old max
		num_p number;
		stream.open(max, fstream::binary | fstream::in);
		stream >> number;
		stream.close();
		cout << number << endl;
		
		string pathStr("database");
		pathStr.append("/");
		pathStr.append(std::to_string(number));
		path ngPath(pathStr);

		if (exists(ngPath)){
			throw NGAlreadyExistsException();
		}

		for (auto itr = NGIterator("database/") ; (itr != NGIterator()); ++itr){ // To check that name doesnt already exists
			if ((*itr).second->name == newsgroup->name){
				cout << (*itr).second->name << endl << newsgroup->name << endl; 
				throw NGAlreadyExistsException();
			}
		}


		create_directory(ngPath);
		path namePath = "database/";
		namePath += std::to_string(number);		// WRite name
		namePath += "/name";
		cout << "writing name file to" << namePath << endl;
		stream.open(namePath, fstream::binary | fstream::out | fstream::trunc);
		stream << string_p(newsgroup->name);
		stream.close();

		// write new max
		number.value++;
		stream.open(max, fstream::out | fstream::binary | fstream::trunc);
		stream << number;
		stream.close();
		pathStr.append("/max");
		stream.open(pathStr, fstream::binary | fstream::out | fstream::trunc); // Write maxvalue
		num_p artCounter(1);
		stream << artCounter;
		stream.close();

		
	}

	vector<pair<uint32_t, shared_ptr<Newsgroup>>>::const_iterator getNewsgroupBegin(){
		NGIterator temp("database/");
		ngCache.clear();
		for_each(temp, NGIterator(), [&] (const pair<uint32_t, shared_ptr<Newsgroup>> &p) { ngCache.push_back(p); } );
		sort(ngCache.begin(), ngCache.end(), 
			[] (const pair<uint32_t, shared_ptr<Newsgroup>> &a, const pair<uint32_t, shared_ptr<Newsgroup>> &b ) -> bool {
			return a.first < b.first;
		});
		return ngCache.cbegin();
	}
	vector<pair<uint32_t, shared_ptr<Newsgroup>>>::const_iterator getNewsgroupEnd(){
		return ngCache.cend();
	}	

	vector<pair<uint32_t, shared_ptr<Article>>>::const_iterator getArticleBegin(uint32_t ngId){
		ArticleIterator temp(ngId);
		articleCache.clear();
		for_each(temp, ArticleIterator(), [&] (const pair<uint32_t, shared_ptr<Article>> &p) { articleCache.push_back(p); } );
		sort(articleCache.begin(), articleCache.end(), 
			[] (const pair<uint32_t, shared_ptr<Article>> &a, const pair<uint32_t, shared_ptr<Article>> &b ) -> bool {
			return a.first < b.first;
		});
		return articleCache.cbegin();
	}
	vector<pair<uint32_t, shared_ptr<Article>>>::const_iterator getArticleEnd(uint32_t ngId){
		return articleCache.cend();
	}


	void deleteArticle(uint32_t artId, uint32_t ngId){
		string number = std::to_string(ngId);
		string pathStr("database");
		pathStr.append("/");
		pathStr.append(number);
		path ngPath(pathStr);

		if (!exists(ngPath)){
			throw NGDoesntExistException();
		}
		string artNum = std::to_string(artId);
		pathStr.append("/");
		pathStr.append(artNum);
		path artPath(pathStr);
		if (!exists(artPath)){
			throw ArtDoesntExistException();
		}

		remove_all(artPath);
	}

	void deleteNewsgroup(uint32_t ngId){
		string number = std::to_string(ngId);
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
	vector<pair<uint32_t, shared_ptr<Newsgroup>>> ngCache;
	vector<pair<uint32_t, shared_ptr<Article>>> articleCache;
};



#endif
