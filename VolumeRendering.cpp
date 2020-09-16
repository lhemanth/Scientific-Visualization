
// Read in a volume
// fn: filename;	nx,ny,nz: volume dimensions;	involume: retur the 3d voxel array
/*#include <cstdio>
#include <string.h>
#include <malloc.h>*/
/*
#include<iostream>
#include<math.h>

bool useboundingbox = false;
void ReadVolume_vol(char *fn, int &nx, int &ny, int &nz, unsigned char *&involume)
{
	int n;
	FILE *fp;
	char imageType[20],str[100];

	fp = fopen(fn,"rb");
	fgets(str,100,fp);
	sscanf(str,"%s",imageType);
	if(!strncmp(imageType,"P7",2)){ // volume data
		// skip comments embedded in header
		fgets(str,100,fp);  
		while(str[0]=='#')
			fgets(str,100,fp);

		// read volume dimensions 
		sscanf(str,"%d %d %d",&nx,&ny,&nz);
		n = nx*ny*nz;

		fgets(str,100,fp);  

		involume=(unsigned char*)malloc(n*sizeof(unsigned char));
		fread(involume,sizeof(unsigned char),n,fp);
	}
	fclose(fp);
}



// p is the starting position, ray is the ray direction vector
// return t_front and t_back
void vIntersectRaywithVolumeBoundingBox(double p[3], double ray[3], double &t_front, double &t_back)
{
	double bbx0, bbx1, bby0, bby1, bbz0, bbz1;	// bounding box
	double dev;
	double t1, t2, mint, maxt;

	t_front = -1e10;
	t_back = 1e10;
	dev = 0.0001;
	if (useboundingbox) {
		//		bbx0 = bbx[0] + dev;	bbx1 = bbx[1] - dev;
		//		bby0 = bby[0] + dev;	bby1 = bby[1] - dev;
		//		bbz0 = bbz[0] + dev;	bbz1 = bbz[1] - dev;
		
		//bbx0 = bbx[0] - dev;	bbx1 = bbx[1] + dev;
		//bby0 = bby[0] - dev;	bby1 = bby[1] + dev;
		//bbz0 = bbz[0] - dev;	bbz1 = bbz[1] + dev;
	} else {
		//bbx0 = 0 + dev;		bbx1 = vol.nx -1 - dev;
		//bby0 = 0 + dev;		bby1 = vol.ny -1 - dev;
		//bbz0 = 0 + dev;		bbz1 = vol.nz -1 - dev;
	}

	if (fabs(ray[0])<=1e-5) {
		if (p[0]<bbx0 || p[0]>bbx1)
			return;
	}
	if (fabs(ray[1])<=1e-5) {
		if (p[1]<bby0 || p[1]>bby1)
			return;
	}
	if (fabs(ray[2])<=1e-5) {
		if (p[2]<bbz0 || p[2]>bbz1)
			return;
	}
	if (fabs(ray[0])>1e-5) {	// intersect with bbx
		t1 = (bbx0 - p[0]) / ray[0];
		t2 = (bbx1 - p[0]) / ray[0];
		mint = fmin(t1, t2);
		maxt = fmax(t1, t2);
		t_front = fmax(mint, t_front);
		t_back = fmin(maxt, t_back);
	}
	if (fabs(ray[1])>1e-5) {	// intersect with bby
		t1 = (bby0 - p[1]) / ray[1];
		t2 = (bby1 - p[1]) / ray[1];
		mint = fmin(t1, t2);
		maxt = fmax(t1, t2);
		t_front = fmax(mint, t_front);
		t_back = fmin(maxt, t_back);
	}
	if (fabs(ray[2])>1e-5) {	// intersecgt with bbz
		t1 = (bbz0 - p[2]) / ray[2];
		t2 = (bbz1 - p[2]) / ray[2];
		mint = fmin(t1, t2);
		maxt = fmax(t1, t2);
		t_front = fmax(mint, t_front);
		t_back = fmin(maxt, t_back);
	}
	return;
}*/