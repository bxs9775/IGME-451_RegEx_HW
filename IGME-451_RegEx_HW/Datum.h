#pragma once
class Datum
{
public:
	//constructor
	Datum();
	~Datum();

	// getters
	class getClass();
	template<T>
	T get();

	//operator overrides
	template<T>
	void operator=(T value);

private:
	//fields
	class classType;
	void* value;
};

