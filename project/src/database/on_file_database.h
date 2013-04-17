#ifndef ON_FILE_DATABASE_H__
#define ON_FILE_DATABASE_H__

#include <iostream>
using std::cout;
using std::endl;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;


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
				writeArticle(article, stream);
				stream.close();
			}
		}
	}

	void writeArticle(shared_ptr<Article> art, fstream &s){
		s << art->title << art->author << art->text;
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
		stream >> article->title >> article->author >> article->text

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
	path p;
	uint ngCounter;

#endif
