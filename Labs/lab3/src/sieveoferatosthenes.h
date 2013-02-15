#ifndef SIEVEOFERATOSTHENES_H__
#define SIEVEOFERATOSTHENES_H__

#include <string>
using std::string;
class SieveOfEratosthenes {
public:
	SieveOfEratosthenes(size_t highestNumber = 10) : algo(highestNumber+1, 'P') {
		algo[0] = 'C';
		algo[1] = 'C';
	}
	const string& doAlgo() {
		const size_t algoSize = algo.length();
		size_t pos = algo.find('P');
		while(pos != string::npos){
			for(size_t i = pos+pos; i < algoSize; i += pos) {
				algo[i] = 'C';
			}
			pos = algo.find('P',pos+1);
		}
		return algo;
	}
private:
	string algo;
};

#endif /* end of include guard: SIEVEOFERATOSTHENES_H__ */
