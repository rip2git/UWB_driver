#include "UserPack.h"


uint8 UserPack::ToBytes(uint8 *buffer) const
{
	uint8 i = 0;
	buffer[i++] = static_cast <uint8> (this->Command);
	buffer[i++] = this->DestinationID;
	buffer[i++] = this->TotalSize;
	for (uint8 j = 0; j < this->TotalSize; ++j)
		buffer[i++] = this->Data[j];
	return i;
}



void UserPack::ToStruct(const uint8 *buffer)
{
	uint8 i = 0;
	this->Command = static_cast <UserPack::COMMAND> (buffer[i++]);
	this->DestinationID = buffer[i++];
	this->TotalSize = buffer[i++];
	for (uint8 j = 0; j < this->TotalSize; ++j)
		this->Data[j] = buffer[i++];
}



void UserPack::SetData(const uint8 *buffer)
{
	for (uint8 i = 0; i < this->TotalSize; ++i)
		this->Data[i] = buffer[i];

}



void UserPack::Reset()
{
	this->Command = UserPack::COMMAND::Status;
	this->DestinationID = static_cast <uint8> (UserPack::STATUS::Reserved);
	this->TotalSize = 0;
}



#ifdef UserPack_DEBUG_MODE
#include <iostream>
using std::cout;
using std::endl;
using std::hex;
using std::dec;
void UserPack::Print() const
{
	cout << "{" << static_cast <int> (this->Command) << "}-";
	cout << "{" << static_cast <int> (this->DestinationID) << "}-";
	cout << "{" << static_cast <int> (this->TotalSize) << "}-";
	cout << "{";
	if (this->TotalSize > 2) {
		for (uint8 i = 0; i < this->TotalSize - 2; ++i)
			cout << static_cast <char> (this->Data[i]);
		cout << "}";
	}
}
#endif
