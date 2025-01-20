// Process.cpp: 구현 파일
//

#include "pch.h"
#include "MfcCircleMove.h"
#include "Process.h"
#include "ASSERT.h"
#include <thread>
// Process

Process::Process()
{
}

Process::~Process()
{
}

void Process::GetCircleCenter(const CImage* const image, const unsigned char mapColor, const unsigned char circleColor, int* const outCenterX, int* const outCenterY)
{
	MY_ASSERT(outCenterX != nullptr);
	MY_ASSERT(outCenterY != nullptr);
	MY_ASSERT(mapColor != circleColor);
	const unsigned char* const fm = static_cast<const unsigned char*>(image->GetBits());
	const int nPitch = image->GetPitch();
	const int nWidth = image->GetWidth();
	const int nHeight = image->GetHeight();
	long long circlePixelCount[THREAD_ROW_COUNT][THREAD_COL_COUNT] = { 0 };
	long long circleXSum[THREAD_ROW_COUNT][THREAD_COL_COUNT] = { 0 };
	long long circleYSum[THREAD_ROW_COUNT][THREAD_COL_COUNT] = { 0 };
	static_assert(sizeof(circleXSum[0][0]) == 8, "");
	static_assert(sizeof(circleYSum[0][0]) == 8, "");
	static_assert(sizeof(circlePixelCount[0][0]) == 8, "");

	MY_ASSERT(nWidth - nWidth / 2)

	std::thread thread0(GetCirclePointSum, image, 0, 0, nWidth / 2, nHeight / 2, mapColor, circleColor, &circleXSum[0][0], &circleYSum[0][0], &circlePixelCount[0][0]);
	std::thread thread1(GetCirclePointSum, image, nWidth / 2, 0, nWidth - nWidth / 2, nHeight / 2, mapColor, circleColor, &circleXSum[0][1], &circleYSum[0][1], &circlePixelCount[0][1]);
	std::thread thread2(GetCirclePointSum, image, 0, nHeight / 2, nWidth / 2, nHeight - nHeight / 2, mapColor, circleColor, &circleXSum[1][0], &circleYSum[1][0], &circlePixelCount[1][0]);
	std::thread thread3(GetCirclePointSum, image, nWidth / 2, nHeight / 2, nWidth - nWidth / 2, nHeight - nHeight / 2, mapColor, circleColor, &circleXSum[1][1], &circleYSum[1][1], &circlePixelCount[1][1]);

	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();


	long long allCircleXSum = circleXSum[0][0] + circleXSum[0][1] + circleXSum[1][0] + circleXSum[1][1];
	long long allCircleYSum = circleYSum[0][0] + circleYSum[0][1] + circleYSum[1][0] + circleYSum[1][1];

	long long allCirclePixelCount = circlePixelCount[0][0] + circlePixelCount[0][1] + circlePixelCount[1][0] + circlePixelCount[1][1];

	*outCenterX = static_cast<int>(static_cast<double>(allCircleXSum) / allCirclePixelCount + 0.5);
	*outCenterY = static_cast<int>(static_cast<double>(allCircleYSum) / allCirclePixelCount + 0.5);
}


void Process::GetCirclePointSum(const CImage* const image, const int startX, const int startY, const int findWidth, const int findHeight, const unsigned char mapColor, const unsigned char circleColor, long long* const outXSum, long long* const outYSum, long long* const outPointCount)
{
	MY_ASSERT(outXSum != nullptr);
	MY_ASSERT(outYSum != nullptr);
	MY_ASSERT(outPointCount != nullptr);
	static_assert(sizeof(outXSum) == 8, "");
	static_assert(sizeof(outYSum) == 8, "");
	static_assert(sizeof(outPointCount) == 8, "");

	*outXSum = 0;
	*outYSum = 0;
	*outPointCount = 0;
	const unsigned char* const fm = static_cast<const unsigned char*>(image->GetBits());
	const int nPitch = image->GetPitch();
	const int nWidth = image->GetWidth();
	const int nHeight = image->GetHeight();
	MY_ASSERT(startY + findHeight <= nHeight);
	MY_ASSERT(startX + findWidth <= nWidth);
	for (int y = startY; y < startY + findHeight; ++y) {
			
			for (int x = startX; x < startX + findWidth; ++x) {
				if (fm[y * nPitch + x] == mapColor) {
					continue;
				}
				const unsigned char pixel = fm[nPitch * y + x];
				if (pixel == mapColor) {
					continue;
				}
				MY_ASSERT(pixel == circleColor);
				*outXSum += static_cast<long long>(x);
				*outYSum += static_cast<long long>(y);
				++(*outPointCount);
			}
		}

}
