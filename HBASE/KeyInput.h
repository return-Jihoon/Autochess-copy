#pragma once
#include <string>
#include <vector>
#include <map>
#include "Ref.h"

#include "Debug.h"

class Input
{
private:
	class Key : public Reference
	{
	private:
		friend Input;

	public:
		bool IsKeyCheck(); // 키체크하는 구간.
		void Update(); // 키체크하는 구간.

	public:
		std::vector<int> mKeyVector;
		bool mUp;
		bool mUpAway; // 이녀석만 true
		bool mDown;
		bool mPress;

	private:
		Key();
		~Key();
	};

public:
	static void Update();
	static HPTR<Key> mNewKey;

	template<typename ...Rest>
	static void CreateKey(const wchar_t* name, Rest ...arg)
	{
		mNewKey = findKey(name);

		if (nullptr != mNewKey)
		{
			BOOM;
		}

		mNewKey = new Key();
		mNewKey->mKeyVector.reserve(sizeof...(arg));
		PushKey(arg...);

		mAllKeyMap.insert(std::map<std::wstring, HPTR<Key>>::value_type(name, mNewKey));
	}

	template<typename ...Rest>
	static void PushKey(int key, Rest ...arg)
	{
		mNewKey->mKeyVector.push_back(key);
		PushKey(arg...);
	}

	static void PushKey()
	{
	}

public:
	static bool IsKey	(const wchar_t* _Name);
	static bool Down	(const wchar_t* _Name);
	static bool UpAway	(const wchar_t* _Name);
	static bool Press	(const wchar_t* _Name);
	static bool Up		(const wchar_t* _Name);


private:
	static std::map<std::wstring, HPTR<Key>>::iterator	mKeyStartIter;
	static std::map<std::wstring, HPTR<Key>>::iterator	mKeyEndIter;
	static std::map<std::wstring, HPTR<Key>>			mAllKeyMap;

private:
	static HPTR<Key> findKey(const wchar_t* _Name);

public:
	Input();
	~Input();
};

