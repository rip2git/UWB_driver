#ifndef CRC_H
#define CRC_H


typedef unsigned char uint8;
typedef unsigned short uint16;



/* -----------------------------------------------------------------------------------------
 * Provides to take check sum of some data (CRC and CRC16)
 * -----------------------------------------------------------------------------------------
 * */
class CheckSum {
public:
	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	CheckSum()
	{
		CRC16_MakeTable();
		CRC8_MakeTable();
	}

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	uint16 GetCRC16(const uint8 *buf, uint16 len) const
	{
		uint16 crc;
		crc = 0xFFFF;
		while (len--) {
			crc = this->crc16table[ ((crc >> 8) ^ *buf++) & 0xFF ] ^ (crc << 8);
		}
		crc ^= 0xFFFF;
		return crc;
	}

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	uint8 GetCRC8(const uint8 *buf, uint8 len) const
	{
		uint8 crc;
		crc = 0xFF;
		while (len--) {
			crc = this->crc8table[ (crc ^ *buf++) & 0xFF ];
		}
		crc ^= 0xFF;
		return crc;
	}

private:
	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	uint8 crc8table[256];

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	uint16 crc16table[256];

	/* -------------------------------------------------------------------------------------
	 * Makes codes. Standart polynome: 0x8005
	 * -------------------------------------------------------------------------------------
	 * */
	inline void CRC16_MakeTable()
	{
		uint16 i;
		uint16 r;
		uint8 j;

		for (i = 0; i < 256; i++) {
			r = i << 8;
			for (j = 0; j < 8; j++) {
				if (r & (1 << 15))
					r = (r << 1) ^ 0x8005;
				else
					r = r << 1;
			}
			this->crc16table[i] = r;
		}
	}

	/* -------------------------------------------------------------------------------------
	 * Makes codes. Standart polynome: 0x31
	 * -------------------------------------------------------------------------------------
	 * */
	inline void CRC8_MakeTable()
	{
		uint16 i;
		uint8 r;
		uint8 j;

		for (i = 0; i < 256; i++) {
			r = static_cast<uint8>(i);
			for (j = 0; j < 8; j++) {
				if ((r & 0x80))
					r = (r << 1) ^ 0x31;
				else
					r = r << 1;
			}
			this->crc8table[i] = r;
		}
	}
};

/* -----------------------------------------------------------------------------------------
 * Object for using
 * -----------------------------------------------------------------------------------------
 * */
const CheckSum CHECK_SUM_CRC;

#endif
