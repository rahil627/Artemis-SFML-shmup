#ifndef PAYLOAD_H_PP
#define PAYLOAD_H_PP

#include <string>
#include <unordered_map>

template<typename T>
class PayLoad {
private:
	std::unordered_map<std::string, T> payloadMap;
public:
	T getValue(std::string id){return payloadMap[id];);
	void setValue(std::string id, T value){payloadMap[id] = value;};
}

#endif
