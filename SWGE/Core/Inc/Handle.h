#pragma once


namespace SWGE {
namespace Core {

	template <typename DataType>
	class HandlePool;

	template <typename DataType>
	class Handle
	{
	public:
		Handle();

		bool IsValid() const;
		void Invalidate();

		DataType* Get() const; // gives you actual pointer (Meant to be used like a pointer)
		DataType* operator->() const;

		bool operator==(Handle rhs) const { return mIndex == rhs.mIndex && mGeneration == rhs.mGeneration; }
		bool operator!=(Handle rhs) const { return !(*this == rhs); }

	private:
		friend class HandlePool<DataType>;

		static const HandlePool<DataType>* sPool;

		uint32_t mIndex : 24;		// Bit Packing, specify the actual bits used in memory
		uint32_t mGeneration : 8;	// But using it is like using a normal uint32_t
									// in memory: [    24    ][ 8 ]

	};

	template <typename DataType>
	const HandlePool<DataType>* Handle<DataType>::sPool = nullptr;


	template <typename DataType>
	Handle<DataType>::Handle()
		: mIndex(0)
		, mGeneration(0)
	{
	}
	template <typename DataType>
	bool Handle<DataType>::IsValid() const
	{
		return sPool && sPool->IsValid(*this);
	}

	template <typename DataType>
	void Handle<DataType>::Invalidate()
	{
		*this = Handle();
	}

	template <typename DataType>
	DataType* Handle<DataType>::Get() const
	{
		return sPool ? sPool->Get(*this) : nullptr;
	}


	template <typename DataType>
	DataType* Handle<DataType>::operator->() const
	{
		return sPool ? sPool->Get(*this) : nullptr;
	}

}
}