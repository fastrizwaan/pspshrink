#ifndef __CISO_H__
#define __CISO_H__

#include <string>
#include <stdint.h>

typedef struct ciso_header
{
	unsigned char magic[4];			/* +00 : 'C','I','S','O'                 */
	uint32_t header_size;		/* +04 : header size (==0x18)            */
	unsigned long long total_bytes;	/* +08 : number of original data size    */
	uint32_t block_size;		/* +10 : number of compressed block size */
	unsigned char ver;				/* +14 : version 01                      */
	unsigned char align;			/* +15 : align of index value            */
	unsigned char rsv_06[2];		/* +16 : reserved                        */
}CISO_H;

class CIsoException
{
    public:
        CIsoException(const std::string message)
        : m_Message(message)
        {
        }
        
        const std::string what()
        {
            return m_Message;
        }    

    private:
        std::string m_Message;
};


class CIso
{
    public:
        CIso();
        ~CIso();
		
        void compress(const std::string& filenameIn, const std::string& filenameOut, int level);
        void decompress(const std::string& filenameIn, const std::string& filenameOut);
		int getProgress() const { return m_Progress; }
		int getCompressionRate() const { return m_CompressionRate; }
       
	protected:
		void run();
	
    private:
        int32_t check_file_size(FILE *fp, CISO_H* ciso);
        
        unsigned int* index_buf;
        unsigned int* crc_buf;
        unsigned char* block_buf1;
        unsigned char* block_buf2;
        
        int ciso_total_block;
		int m_Progress;
		int m_CompressionRate;
};

#endif
