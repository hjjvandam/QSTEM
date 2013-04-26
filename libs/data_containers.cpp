#include "stdio.h"
#include <string.h>
#include "data_containers.h"

WAVEFUNC::WAVEFUNC(int x, int y)
{
	char waveFile[256];
	const char *waveFileBase = "mulswav";
	detPosX=0;
	detPosY=0;
	iPosX=0;
	iPosY=0;
	nx = x;
	ny = y;
	diffpat = float2D(nx,ny,"diffpat");
	avgArray = float2D(nx,ny,"avgArray");

#if FLOAT_PRECISION == 1
	wave = complex2Df(nx, ny, "wave");
	fftPlanWaveForw = fftwf_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_FORWARD, FFTW_ESTIMATE);
	fftPlanWaveInv = fftwf_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_BACKWARD, FFTW_ESTIMATE);
#else
	wave = complex2D(nx, ny, "wave");
	fftPlanWaveForw = fftw_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_FORWARD,
		fftMeasureFlag);
	fftPlanWaveInv = fftw_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_BACKWARD,
		fftMeasureFlag);
#endif

	sprintf(waveFile,"%s.img",waveFileBase);
	strcpy(fileout,waveFile);
	sprintf(fileStart,"mulswav.img");
}

WAVEFUNC::WAVEFUNC( WAVEFUNC& other )
{
	iPosX = other.iPosX;
	iPosY = other.iPosY;
	detPosX = other.detPosX;
	detPosY = other.detPosY;

	strcpy(fileStart, other.fileStart);
	strcpy(fileout, other.fileout);
	strcpy(avgName, other.avgName);

	nx = other.nx;
	ny = other.ny;

	diffpat = float2D(nx,ny,"diffpat");
	avgArray = float2D(nx,ny,"avgArray");

#if FLOAT_PRECISION == 1
	wave = complex2Df(nx, ny, "wave");
	fftPlanWaveForw = fftwf_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_FORWARD, FFTW_ESTIMATE);
	fftPlanWaveInv = fftwf_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_BACKWARD, FFTW_ESTIMATE);
#else
	wave = complex2D(nx, ny, "wave");
	fftPlanWaveForw = fftw_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_FORWARD,
		fftMeasureFlag);
	fftPlanWaveInv = fftw_plan_dft_2d(nx,ny,wave[0],wave[0],FFTW_BACKWARD,
		fftMeasureFlag);
#endif
}