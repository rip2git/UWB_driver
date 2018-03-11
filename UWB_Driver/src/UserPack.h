#ifndef USERPACK_H_
#define USERPACK_H_


#define UserPack_DEBUG_MODE
typedef unsigned char uint8;
typedef unsigned short uint16;


struct UserPack {

	enum class COMMAND : uint8 {
		Status = 0,
		SetID,
		Distance,
		Data
	};
	enum class STATUS : uint8 {
		Reserved = 0,
		SetID,
		Distance,
		Data
	};
	static const uint8 BROADCAST_ID = 0xFF;
	static const uint8 DATA_OFFSET = 3;
	static const uint8 MAX_DATA_SIZE = 127; // according with IEEE Std 802.15.4-2011
	static const uint8 MAX_PACK_BYTE = MAX_DATA_SIZE + DATA_OFFSET + 2;

	COMMAND Command;
	uint8 DestinationID;
	uint8 TotalSize;
	uint8 Data[MAX_DATA_SIZE];

	uint8 ToBytes(uint8 *buffer) const;
	void ToStruct(const uint8 *buffer);
	void SetData(const uint8 *buffer);
	void Reset();
#ifdef UserPack_DEBUG_MODE
	void Print() const;
#endif
};



#endif /* USERPACK_H_ */
