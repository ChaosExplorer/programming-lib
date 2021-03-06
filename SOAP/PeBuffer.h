/*
 * PeBuffer.h
 *
 *  Created on: 2012-6-14
 *      Author: Haosen Chen
 * 		Mail  : chenhaosen@genomics.cn
 */

#ifndef PREPROCESSTOOL_3_LOCAL_PEBUFFER_H_
#define PREPROCESSTOOL_3_LOCAL_PEBUFFER_H_

#include "Common.h"

namespace PreProcessTool {

class PeBuffer
{
public:
	enum MODE
	{
		RB, WB,
	};

public:
	PeBuffer(const char *fq1Filename, const char *fq2Filename, int capacity, MODE mode, bool filterTile, const set<string> &tiles);
	PeBuffer(const char *fq1Filename, const char *fq2Filename, int capacity, MODE mode, bool filterTile, const set<string> &tiles, int seqType);
	~PeBuffer();

	/**
	 * return:
	 * 	读取的read个数,
	 * 		0:  end of file,
	 * 		-1: error,
	 * 		-2: fq1和fq2的read条数不一样
	 */
	int getReads();
	int getReadSize();

	int getInitReadSize();

	char *getBuf1();
	char *getBuf2();
	int getlastIndex1();
	int getlastIndex2();

	Read* getReadsOne();
	Read* getReadsTwo();

	bool isFilterTile(char *name, int seqType);
    bool isFilterFov(char *name, int seqType);
	void setSeqType(int type);
    void setTileIsFov(bool b);

private:
	/**
	 * input:
	 * 	file: read which file
	 * 		1:fq1
	 * 		2:fq2
	 * output:
	 *  result:
	 *  	0 for end of file
	 *  	-1 for error
	 */
	void readTask(int file, int &result);

private:
	bool filterTile_;
    bool tileIsFov_;
	gzFile file1_;
	gzFile file2_;
	char *buf1_;
	char *buf2_;
	char tile[9];
	int capacity_;

	int *read_pos1;
	int *read_pos2;

	int size1_;
	int size2_;
	Read *reads1_;
	Read *reads2_;
	char **nameIndex1_;
	char **nameIndex2_;
	int readSize_;
	int realReadSize_;

	int initReadSize_;

	int lastIndex1_;
	int lastIndex2_;

	long lineNum1_; //fq1 current line number
	long lineNum2_; //fq2 current line number

	set<string> tiles_;
	int seqType_;

};

}  // namespace PreProcessTool


#endif /* PREPROCESSTOOL_3_LOCAL_PEBUFFER_H_ */
