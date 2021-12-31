#pragma once
  


class Reference
{
public:
	inline bool IsDebugCheck()
	{
		return mbDebug;
	}

	inline void DebugOn() {
		mbDebug = true;
	}

	void DebugCheck();

private:
	template<typename T>
	friend class HPTR;

	int mReferenceCount;
	bool mbDebug;

private:
	void increaseReferenceCount();
	void decreaseReferenceCount();

public:
	Reference();

protected:
	virtual ~Reference();
};

template<typename P>
class HPTR 
{

public:
	P* PTR;

	operator P*()
	{
		return PTR;
	}

	bool operator <(const std::nullptr_t _PTR) const
	{
		return PTR < _PTR;
	}
	bool operator >(const std::nullptr_t _PTR) const
	{
		return PTR > _PTR;
	}

	// 다른 PTR
	bool operator <(const HPTR& _PTR) const
	{
		return PTR < _PTR.PTR;
	}
	bool operator >(const HPTR& _PTR) const
	{
		return PTR > _PTR.PTR;
	}

	// 다른 PTR
	bool operator <(P* const _PTR) const
	{
		return PTR < _PTR;
	}
	bool operator >(P* const _PTR) const
	{
		return PTR > _PTR;
	}

	// 1000 int
	// nullptr
	bool operator !=(const std::nullptr_t _PTR) const
	{
		return PTR != _PTR;
	}
	bool operator ==(const std::nullptr_t _PTR) const
	{
		return PTR == _PTR;
	}

// 다른 PTR
	bool operator !=(const HPTR& _PTR) const
	{
		return PTR != _PTR.PTR;
	}
	bool operator ==(const HPTR& _PTR) const
	{
		return PTR == _PTR.PTR;
	}

// 다른 PTR
	bool operator !=(P* const _PTR) const
	{
		return PTR != _PTR;
	}
	bool operator ==(P* const _PTR) const
	{
		return PTR == _PTR;
	}

// ->연산자
	P* const operator->() const
	{
		return PTR;
	}

	P& operator*() const
	{
		return (*PTR);
	}

// 대입연산자들.
	HPTR& operator =(P* const _PTR)
	{
		CheckDEC();
		PTR = _PTR;
		CheckADD();
		return *this;
	}

	HPTR& operator =(const std::nullptr_t _PTR)
	{
		CheckDEC();
		PTR = nullptr;
		return *this;
	}

	HPTR& operator =(const HPTR& _PTR)
	{
		// 원래 내가 들고있던 PTR의 소유권을 
		// PTR
		// 내가 원래 들고있던 녀석의 소유권을 포기한다.
		CheckDEC();
		PTR = _PTR.PTR;
		// 내가 새롭게 들게될 녀석의 소유권을 주장한다.
		CheckADD();
		return *this;
	}

public:
	void CheckADD() 
	{
		if (nullptr == PTR)
		{
			return;
		}

		((Reference*)PTR)->increaseReferenceCount();
	}

	void CheckDEC()
	{
		if (nullptr == PTR)
		{
			return;
		}

		((Reference*)PTR)->decreaseReferenceCount();
	}

	template<typename CON>
	CON* Convert() 
	{
		return dynamic_cast<CON*>(PTR);
	}

public:
	HPTR() : PTR(nullptr) {}
	HPTR(const std::nullptr_t _PTR) : PTR(_PTR) {}
	HPTR(P* const _PTR) : PTR(_PTR) 
	{
		CheckADD();
	}

	HPTR(const HPTR& _PTR) : PTR(_PTR.PTR)
	{
		CheckADD();
	}

public:
	virtual ~HPTR()
	{
		CheckDEC();
	}
};

// 전역 연산자 오버로딩
template<typename P>
typename bool operator==(const std::nullptr_t _PTR, const HPTR<P>& _HPTR) 
{
	return _PTR == _HPTR.PTR;
}
template<typename P>
typename bool operator!=(const std::nullptr_t _PTR, const HPTR<P>& _HPTR)
{
	return _PTR != _HPTR.PTR;
}
