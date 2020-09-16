#define _CRT_SECURE_NO_DEPRECATE
#include "Application.h"
#include <FL/fl_file_chooser.H>
#include "Gui.h"
#include <algorithm>
#include "VolumeRendering.cpp"
	
extern Gui* gui;
Image curImage; // make inImage a global, need it in other classes
Volume vol;

// these are declared in transFunc.cpp
extern TransferFunction transFunc[4];
extern int maxTransFunc;
extern int activeTransFunc;
extern float transFuncColor[4][3];
extern int hist[256];
//Image tt;
unsigned char* dupImage;
unsigned char* oldImage;


//project 2
Image showXRayImage;
Image showMipImage;

//Volume vol;
Image curXRayImage;
Image curMipImage;

float rotationX = 0;
float rotationY = 0;
float rotationZ = 0;
float scale = 1.0f;
Volume volume2;



// the constructor method for the Application class

Application::Application()
{
	// initialize the image data structure
	curImage.nx = curImage.ny = curImage.n = curImage.ncolorChannels = 0;

	// add more initialization here:

}

// the method that gets executed when the readFile callback is called

void Application::ReadFile()
{
	FILE* fp;
	char imageType[3], str[100];
	int dummy;
	int i, j;

	char* file = fl_file_chooser("Pick a file to READ from", "*.{pgm,ppm,vol}", "");
	if (file == NULL)
		return;

	// Read PGM image file with filename "file"

	// The PGM file format for a GREYLEVEL image is:
	// P5 (2 ASCII characters) <CR>
	// two ASCII numbers for nx ny (number of rows and columns <CR>
	// 255 (ASCII number) <CR>
	// binary pixel data with one byte per pixel

	// The PGM file format for a COLOR image is:
	// P6 (2 ASCII characters) <CR>
	// two ASCII numbers for nx ny (number of rows and columns <CR>
	// 255 (ASCII number) <CR>
	// binary pixel data with three bytes per pixel (one byte for eacg RGB)

	fp = fopen(file, "rb");

	// free memory from old image, if any
	if (curImage.n > 0)
	{
		delete[] curImage.data;
	}

	// read the first ASCII line to find out if we read a color image or
	// a greylevel image

	fgets(str, 100, fp);
	sscanf(str, "%s", imageType);

	if (!strncmp(imageType, "P5", 2)) // greylevel image 
	{
		curImage.ncolorChannels = 1;
		maxTransFunc = 1;  // have read a greylevel image: need only one transfer function
		activeTransFunc = 0;    // transFunc 0 is active (all the time)
		transFuncColor[0][0] = 1.0; transFuncColor[0][1] = 0.0; transFuncColor[0][2] = 0.0;  // draw transfer function curve in red 
	}
	else if (!strncmp(imageType, "P6", 2)) // color image 
	{
		curImage.ncolorChannels = 3;
		maxTransFunc = 1;  // have read a color image: if you want 3 transfer functions (HSV) change this value to 3
		activeTransFunc = 0;    // transFunc 0 is active (for now)
		transFuncColor[0][0] = 1.0; transFuncColor[0][1] = 0.0; transFuncColor[0][2] = 0.0;  // draw transfer function curve in red 
		transFuncColor[1][0] = 0.0; transFuncColor[1][1] = 1.0; transFuncColor[1][2] = 0.0;  // draw transfer function curve in red 
		transFuncColor[2][0] = 0.0; transFuncColor[2][1] = 0.0; transFuncColor[2][2] = 1.0;  // draw transfer function curve in red 
	}

	// skip comments embedded in header
	fgets(str, 100, fp);
	while (str[0] == '#')
		fgets(str, 100, fp);

	// read image dimensions 
	sscanf(str, "%d %d", &curImage.nx, &curImage.ny);

	// read the next line into dummy variable
	fgets(str, 100, fp);

	// allocate the memory
	curImage.n = curImage.nx * curImage.ny;

	// read the image data 
	curImage.data = new unsigned char[curImage.n * curImage.ncolorChannels];
	fread(curImage.data, sizeof(unsigned char), curImage.n * curImage.ncolorChannels, fp);

	// unfortunately OpenGL displays the image upside-down
	// we have to flip it at read time.
	FlipImage(&curImage);

	fclose(fp);
	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		hist[i] = 0;
	}

	for (int j = 0; j < curImage.n * curImage.ncolorChannels; j = j+curImage.ncolorChannels)
	{
		hist[curImage.data[j]] += 1;
	}

	dupImage = new unsigned char[curImage.n * curImage.ncolorChannels];
	memcpy(dupImage, curImage.data, curImage.n * curImage.ncolorChannels);
	 //tt = curImage;
	// call the window drawing routines to display the image curImage
	// and to draw image-related transFuncs
	gui->DisplayWindow->redraw();
	gui->EditorWindow->redraw();
	//undoImage = curImage;
}


void Application::WriteFile()
{
	FILE* fp;
	char imageType[3], str[100];
	int dummy, i;
	char* file = fl_file_chooser("Specify a filename to WRITE to", "*.{vol,ppm,pgm}", "");
	if (file == NULL)
		return;

	// Write PGM image file with filename "file"

	// The PGM file format for a GREYLEVEL image is:
	// P5 (2 ASCII characters) <CR>
	// two ASCII numbers for nx ny (number of rows and columns <CR>
	// 255 (ASCII number) <CR>
	// binary pixel data with one byte per pixel

	// The PGM file format for a COLOR image is:
	// P6 (2 ASCII characters) <CR>
	// two ASCII numbers for nx ny (number of rows and columns <CR>
	// 255 (ASCII number) <CR>
	// binary pixel data with three bytes per pixel (one byte for each R,G,B)

	fp = fopen(file, "wb");

	// write the first ASCII line with the file type
	if (curImage.ncolorChannels == 1)
		fprintf(fp, "P5\n"); //greylevel image
	else if (curImage.ncolorChannels == 3)
		fprintf(fp, "P6\n");  // color image

	  // write image dimensions 
	fprintf(fp, "%d %d\n", curImage.nx, curImage.ny);

	// write '255' to the next line 
	fprintf(fp, "255\n");

	// since we flipped the image upside-down when we read it
	// we have to write it upside-down so it's stored the right way
	for (i = curImage.ny - 1; i >= 0; i--)
		fwrite(&curImage.data[i * curImage.nx * curImage.ncolorChannels], sizeof(unsigned char), curImage.nx * curImage.ncolorChannels, fp);

	fclose(fp);
}

// flips an image upside down
// you will not have to change anything here

void Application::FlipImage(Image* img)
{
	int i, j, k, rowOffsetSrc, rowOffsetDest, columnOffset;
	unsigned char ctmp;

	for (i = 0; i < img->ny / 2; i++)
	{
		rowOffsetSrc = i * img->nx * img->ncolorChannels;
		rowOffsetDest = (img->ny - 1 - i) * img->nx * img->ncolorChannels;
		for (j = 0; j < img->nx; j++)
		{
			columnOffset = j * img->ncolorChannels;
			for (k = 0; k < img->ncolorChannels; k++)
			{
				ctmp = img->data[rowOffsetSrc + columnOffset + k];
				img->data[rowOffsetSrc + columnOffset + k] = img->data[rowOffsetDest + columnOffset + k];
				img->data[rowOffsetDest + columnOffset + k] = ctmp;
			}
		}
	}
}

void Application::updateImage()
{
	//unsigned char newPixelValue;

	//copy original data from duplicate storage
	oldImage = new unsigned char[curImage.n * curImage.ncolorChannels];
	memcpy(oldImage, curImage.data, curImage.n * curImage.ncolorChannels);
	memcpy( curImage.data, dupImage,curImage.n * curImage.ncolorChannels);
	
	
	
	//curImage = tt ;
	//undoImage = curImage;
	for (int j = 0; j < 256 ; j++)

	{


		for (int i = 0; i < curImage.n * curImage.ncolorChannels; i = i + curImage.ncolorChannels)
		{
			if (curImage.data[i] == j)
			{
				curImage.data[i] = transFunc[0][j];
				curImage.data[i + 1] = transFunc[0][j];
				curImage.data[i + 2] = transFunc[0][j];
				//curImage.data[i] = newPixelValue;
			}
		}
	}
	//curImage.data = tempImage.data;
	/*for (int j = 0; j < 256; j = j + 1)
	{
		curImage.data[j] = tempImage.data[j];
		//curImage.data[i] = newPixelValue;

	}*/
	//curImage = tempImage;

	//draw updated greyscale image
	
	for (int i = 0; i < 256; i++)
	{
		hist[i] = 0;
	}

	for (int j = 0; j < curImage.n * curImage.ncolorChannels; j = j + curImage.ncolorChannels)
	{
		hist[curImage.data[j]] += 1;
	}
	gui->DisplayWindow->redraw();
	gui->EditorWindow->redraw();
}


void Application::averageSmoothing()
{
	oldImage = new unsigned char[curImage.n * curImage.ncolorChannels];
	memcpy(oldImage, curImage.data, curImage.n * curImage.ncolorChannels);
	memcpy(curImage.data, dupImage, curImage.n * curImage.ncolorChannels);
	int n = curImage.n * curImage.ncolorChannels;

		for (int i = 0; i < n-3; i = i + curImage.ncolorChannels)
	{
		int totalValue = 0;
		int loop = i;
		int average = 0;
		
		for (int j = i; loop < i + 3; j = j + (curImage.nx + 1) * curImage.ncolorChannels) 
		{
			
			for (int k = j; k < j + 3; k++)
			{
				totalValue = totalValue + (int)dupImage[k];
			}
			loop++;
		}
		//average caluclation
		average = (totalValue / 9);
		//assign the caluclated average value to curl image  
		curImage.data[i + 2 + curImage.nx * curImage.ncolorChannels] = (unsigned char)average;
	}

	gui->DisplayWindow->redraw();
}

void Application::medianSmoothing()
{
	oldImage = new unsigned char[curImage.n * curImage.ncolorChannels];
	memcpy(oldImage, curImage.data, curImage.n * curImage.ncolorChannels);
	memcpy(curImage.data, dupImage, curImage.n * curImage.ncolorChannels);
	int n = curImage.n * curImage.ncolorChannels;
	for (int i = 0; i <  n; i = i + curImage.ncolorChannels)
	{
		//to store values to sort
		int temp[9] = {};
		int median = 0;
		int loop = i;
		
		
		for (int j = i; loop < i + 3; j = j + (curImage.nx + 1) * curImage.ncolorChannels)
		{
			int l = 0;
			for (int k = j; k < j + 3; k++)
			{
				temp[l] =  dupImage[k];
				l++;
			}
			loop++;
		}
		//std::sort(); --> sorting the elements
		std::sort(temp,temp+9);
		median = temp[4];
		curImage.data[i + 2 + curImage.nx * curImage.ncolorChannels] = median;

	}
	
	gui->DisplayWindow->redraw();
}
void Application::gaussianSmooth() {
	
	oldImage = new unsigned char[curImage.n * curImage.ncolorChannels];
	memcpy(oldImage, curImage.data, curImage.n * curImage.ncolorChannels);
	memcpy(curImage.data, dupImage, curImage.n * curImage.ncolorChannels);
	//gaussian mask values
	int gaussianMatrix[5][5] = { {1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1} };
	
	int n = curImage.n * curImage.ncolorChannels;

	for (int i = 0; i < n ; i = i + curImage.ncolorChannels)
	{
		int totalValue = 0;
		int loop = i;
		int k = 0;
		int average = 0;
		for (int j = i; loop < i + 5; j = j + (curImage.nx+1) * curImage.ncolorChannels)
		{
			for (int l = j; l < j + 5; l++)
			{
				
				totalValue += dupImage[l] * gaussianMatrix[k][l-j];
			}
			loop++;
			k++;
		}
		average = totalValue / 273;
		curImage.data[i + curImage.nx * curImage.ncolorChannels + 4] = average;
	}
	gui->DisplayWindow->redraw();
}
void Application::edgeDetection()
{
	oldImage = new unsigned char[curImage.n * curImage.ncolorChannels];
	memcpy(oldImage, curImage.data, curImage.n * curImage.ncolorChannels);
	memcpy(curImage.data, dupImage, curImage.n * curImage.ncolorChannels);
	int n = curImage.n * curImage.ncolorChannels;

	for (int i = 0; i < n-3 ; i = i + curImage.ncolorChannels)
	{
		int dataX[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
		int dataY[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };
	
		int loop = i;
		int x = 0, y = 0, edgeValue = 0;
		for (int j = i; loop < i + 3; j = j + (curImage.nx + 1) * curImage.ncolorChannels)
		{
			for (int l = j; l < j + 3; l++)
			{
				for (int k = 0; k < 3; k++) {
					x = x + dupImage[l] * dataX[k][l - j];
					y = y + dupImage[l] * dataY[k][l - j];
				}
			}
			
			loop++;
		}
		edgeValue = sqrt((x * x) + (y * y));
		if (edgeValue >= 120)
		{
			curImage.data[i + curImage.nx * curImage.ncolorChannels ] = 255;
		}
		else
		{
			curImage.data[i + curImage.nx * curImage.ncolorChannels ] = 0;
		}
	}
}


void Application::undo() {
	//curImage = undoImage;
	// roll back the data and display original image
	//memcpy(curImage.data, dupImage,curImage.n * curImage.ncolorChannels);
	memcpy(curImage.data, oldImage, curImage.n * curImage.ncolorChannels);
	for (int i = 0; i < 256; i++)
	{
		hist[i] = 0;
	}
	for (int j = 0; j < curImage.n * curImage.ncolorChannels; j = j + curImage.ncolorChannels)
	{
		hist[curImage.data[j]] += 1;
	}
	gui->DisplayWindow->redraw();
	gui->EditorWindow->redraw();


}

// Project 2 code 
void Application::readVolumeFile()
{
	int n;
	FILE* fp;
	char imageType[20], str[100];

	char* file = fl_file_chooser("Pick a file to READ from", "*.{pgm,ppm,vol}", "");
	if (file == NULL)
		return;

	fp = fopen(file, "rb");
	fgets(str, 100, fp);
	sscanf(str, "%s", imageType);
	if (!strncmp(imageType, "P7", 2)) { // volume data
		// skip comments embedded in header
		fgets(str, 100, fp);
		while (str[0] == '#')
			fgets(str, 100, fp);

		// read volume dimensions 
		sscanf(str, "%d %d %d", &volume2.nx, &volume2.ny, &volume2.nz);
		n = volume2.nx * volume2.ny * volume2.nz;

		fgets(str, 100, fp);

		volume2.data = (unsigned char*)malloc(n * sizeof(unsigned char));
		fread(volume2.data, sizeof(unsigned char), n, fp);
	}

	fclose(fp);
	curImage.nx = volume2.nx;
	curImage.ny = volume2.ny;
	curImage.n = volume2.nx * volume2.ny;
	curImage.ncolorChannels = 1;
	curImage.data = new unsigned char[curImage.n * curImage.ncolorChannels];

}

void Application::xRay()
{
	int maxValue = 0;
	int size = curImage.n * curImage.ncolorChannels;
	double* totalVal = new double[size];
	
	
	for (int i = 0; i < volume2.nx; i = i + curImage.ncolorChannels)
	{
		for (int j = 0; j < volume2.ny; j = j + curImage.ncolorChannels)

		{
			
			int totalValue = 0;
			int z = 0;
			int ta = volume2.nx * i + j;
			while (z < volume2.nz)
			{

				totalValue +=  volume2.data[volume2.nx * volume2.ny * z + ta];
				z++;
			}

			totalVal[i * volume2.nx + j] = totalValue;

			if (maxValue < totalValue)
			{
				maxValue = totalValue;
			}
		}

		for (int m = 0; m < size; m++)
		{
			curImage.data[m] = (totalVal[m] / maxValue) * 255;
		}
	}
	
	// display X-Ray
	gui->DisplayWindow->redraw();

}

void Application::mip()
{
	
	int volume2D = volume2.nx * volume2.ny;
	int volume3D = volume2.nx*volume2.ny*volume2.nz;


	for (int i = 0; i < volume2.nx; i = i + curImage.ncolorChannels)

	{
		for (int j = 0; j < volume2.ny; j = j + curImage.ncolorChannels)

		{
			int t = volume2.nx * i + j;
			curImage.data [t]=0;
			int z = 0;

			while(z < volume2.nz)
			{

				if (curImage.data[t] < volume2.data[volume2D * z + t])
				{
					curImage.data[t] = volume2.data[volume2D * z + t];
				}
				z++;
			}
		}
	}
	//display MIP image
	gui->DisplayWindow->redraw();

}

// put your application routines here:


