#pragma once

// Process 명령 대상

class Process : public CObject
{
public:
	Process();
	virtual ~Process();
	static void GetCircleCenter(const CImage* const image, const unsigned char mapColor, const unsigned char circleColor, int* const outCenterX, int* const outCenterY);
	static void GetCirclePointSum(const CImage* const image, const int startX, const int startY, const int findWidth, const int findHeight, const unsigned char mapColor, const unsigned char circleColor, long long* const outXSum, long long* const outYSum, long long* const outPointCount);

private:
	enum {
		THREAD_ROW_COUNT = 2,
		THREAD_COL_COUNT = 2,
	};
};


