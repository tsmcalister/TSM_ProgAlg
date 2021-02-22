#pragma once

#include <mutex>
#include <condition_variable>

using namespace std;

class ConditionVariable : public condition_variable {
	size_t m_waitingThreads;				// number of waiting threads

public:
	ConditionVariable() : m_waitingThreads(0) {}

	void wait(unique_lock<mutex> &m) {
		m_waitingThreads++;
		condition_variable::wait(m);
		m_waitingThreads--;
	}
	bool hasWaitingThreads() const { return m_waitingThreads > 0; }
};

class RWLock {
	mutex m_mutex;							// re-entrance not allowed
	ConditionVariable m_readingAllowed;		// true: no writer at work
	ConditionVariable m_writingAllowed;		// true: no reader and no writer at work
	bool m_writeLocked = false;				// locked for writing
	size_t m_readLocked = 0;				// number of concurrent readers

public:
	size_t getReaders() const {
		return m_readLocked;
	}

	void lockR() {
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_writeLocked || m_writingAllowed.hasWaitingThreads()){
			do {
				m_readingAllowed.wait(lock);
			} while(m_writeLocked);
		}
		m_readLocked++;
	}

	void unlockR() {
		if(--m_readLocked == 0){
			m_writingAllowed.notify_one();
		}
	}

	void lockW() {
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_writeLocked){
			do {
				m_writingAllowed.wait(lock);
			} while(m_writeLocked);
		}
		m_writeLocked = true;
	}

	void unlockW() {
		m_writeLocked = false;
		m_readingAllowed.notify_all();
		m_writingAllowed.notify_one();
	}
};