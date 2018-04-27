#ifndef _SignalK_ReaderHandler_
#define _SignalK_ReaderHandler_
#include <mutex>

namespace SignalK {
	template<class T> class ReaderHandler
	{
	public:
		ReaderHandler(T** resource, std::function<void()> deleter);	
		T * enterReader();
		T * getResource();
		void exitReader();
		void replace(T *newResource);
		void replaceIf(T* newRes, std::function<bool(T*, T*)> cond);
		void modify(std::function<void(T*)> updater);
	private:
		std::function<void()> deleter;
		//bool toDestroy = false;
		int readerCounter = 0;
		std::mutex readerLock, newReaderlock;
		std::condition_variable waitNoReader;
		T** resource=nullptr;
		

	};
}

template<class T> SignalK::ReaderHandler<T>::ReaderHandler(T** resource, std::function<void()> deleter)
{
	readerLock.lock();
	this->resource = resource;
	this->deleter = deleter;
	readerLock.unlock();
}




template<class T> T *SignalK::ReaderHandler<T>::getResource()
{
	auto res = *resource;
	return res;
}


template<class T> T *SignalK::ReaderHandler<T>::enterReader()
{

	newReaderlock.lock();
	newReaderlock.unlock();
	readerLock.lock();
	readerCounter++;
	auto result = *resource;
	readerLock.unlock();
	return result;
}

template<class T> void SignalK::ReaderHandler<T>::exitReader()
{
    readerLock.lock();
	bool signal = false;
	readerCounter--;
	signal = readerCounter == 0;
	readerLock.unlock();
	if(signal) waitNoReader.notify_one();
	
}

template<class T> void SignalK::ReaderHandler<T>::replace(T* newRes)
{
	newReaderlock.lock();
	std::unique_lock<std::mutex> uReaderLock(readerLock);
	//uReaderLock.lock();
	if (readerCounter > 0) {
		
		waitNoReader.wait(uReaderLock, [this] {return this->readerCounter <= 0; });
	}
	deleter();
	*resource = newRes;
	uReaderLock.unlock();
	newReaderlock.unlock();
}
template<class T> void SignalK::ReaderHandler<T>::replaceIf(T* newRes, std::function<bool(T*, T*)> cond)
{
	newReaderlock.lock();
	std::unique_lock<std::mutex> uReaderLock(readerLock);
	//uReaderLock.lock();
	if (readerCounter > 0) {

		waitNoReader.wait(uReaderLock, [this] {return this->readerCounter <= 0; });
	}
	if (cond(*resource, newRes)) {
		deleter();
		*resource = newRes;
	}
	uReaderLock.unlock();
	newReaderlock.unlock();
}
template<class T> void SignalK::ReaderHandler<T>::modify(std::function<void(T*)> updater)
{
	newReaderlock.lock();
	std::unique_lock<std::mutex> uReaderLock(readerLock);
	//uReaderLock.lock();
	if (readerCounter > 0) {
		
		waitNoReader.wait(uReaderLock, [this] {return this->readerCounter <= 0; });
	}
	updater(*resource);
	uReaderLock.unlock();
	newReaderlock.unlock();
}

#endif

