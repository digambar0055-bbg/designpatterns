#include <iostream>
#include <mutex>

class Singleton
{
	private:
		static Singleton* instance;
		static std::mutex mtx;
		Singleton () {}
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		
	public:
		static Singleton * getInstance()
		{
			std::lock_guard<std::mutex> lock(mtx);
			if(!instance)
			{
				instance = new Singleton();
			}
			return instance;
		}
};

static Singleton* instance = nullptr;
std::mutex Singleton::mtx;

int main()
{
	return 0;
}
