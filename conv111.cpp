#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<vector>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;



int main(){
	

	
	int i,m_cols,m_rows,s,j,k,l;	
	double ***rr;
	
	double ***rr1;
	double ***rr2;
	double ***rr3;
	double ***rr4;
	

	double ip2[10][500];
	double conv2[50][20][5][5];
	double conv1[20][1][5][5];
	double ip1[500][800];
	char trash[100];
	char trash1;
	int  trash2;
	int f_size;
	double max1;
	double max2;
	int kkk;

	Mat image1=imread("9.jpg");  
	if(image1.empty())
	{
		cout<<"Could not open"<<endl;
		return -1;	
	}
	Mat image;
	cvtColor( image1, image, COLOR_BGR2GRAY);
 	int x = image1.cols;
	int y = image1.rows; 
	imshow("new_image",image);

	
	FILE *fp;
	fp=fopen("/home/socmgr/work/0715/opencv-3.4.2/build/caffe/python/ip2.txt","r");
	if(fp==NULL)
	{
		printf("fail to open \n");
		return -1;
	}
		

	//ip2
	for(i=0;i<10;i++)
	{	
		for(j=0;j<500;j++)
		{
			fscanf(fp,"%lf",&ip2[i][j]);
			//fscanf(fp,"%c",&trash1);
			//printf("%lf %d %d ",ip2[i][j],i,j);		
		}	
	}
	fclose(fp);
	
	
	//conv2

	FILE *fp1;
	fp1=fopen("/home/socmgr/work/0715/opencv-3.4.2/build/caffe/python/conv2.txt","r");
	if(fp1==NULL)
	{
		printf("fail to open \n");
		return -1;
	}
		
	for(i=0;i<50;i++)
	{
		for(j=0;j<20;j++)
		{			

			for(k=0;k<5;k++)
			{				
				for(l=0;l<5;l++)
				{
					fscanf(fp1,"%lf",&conv2[i][j][k][l]);
					//fscanf(fp1,"%c",&trash1);
					//printf("%lf %d %d %d %d ",conv2[i][j][k][l],i,j,k,l);
				}
			}		
		}	
	}
	
	fclose(fp1);


	//conv1
	FILE *fp2;
	fp2=fopen("/home/socmgr/work/0715/opencv-3.4.2/build/caffe/python/conv1.txt","r");
	if(fp2==NULL)
	{
		printf("fail to open \n");
		return -1;
	}
	for(i=0;i<20;i++)
	{
		for(j=0;j<1;j++)
		{
			for(k=0;k<5;k++)
			{
				for(l=0;l<5;l++)
				{
					fscanf(fp2,"%lf",&conv1[i][j][k][l]);
					//fscanf(fp2,"%c",&trash1);
					//printf("%lf %d %d %d %d ",conv1[i][j][k][l],i,j,k,l);
				}
			}
		}
	}fclose(fp2);
	//ip1
	FILE *fp3;
	fp3=fopen("/home/socmgr/work/0715/opencv-3.4.2/build/caffe/python/ip1.txt","r");
	if(fp3==NULL)
	{
		printf("fail to open \n");
		return -1;
	}

	for(i=0;i<500;i++)
	{	
		for(j=0;j<800;j++)
		{
			fscanf(fp3,"%lf",&ip1[i][j]);
			//fscanf(fp3,"%c",&trash1);
			//printf("%lf %d %d ",ip1[i][j],i,j);
		}
	}
	fclose(fp3);
	f_size=5;
	int f_num=20;
	int cha=1;
	s=1;
	

//rr=image
		rr = (double***)malloc(cha*sizeof(double**));
		for(int i=0;i<cha;i++){						
			*(rr+i) = (double**)malloc(y*sizeof(double*));									
			for(int j=0;j<y;j++){						
			*(*(rr+i)+j) = (double*)malloc(x*sizeof(double));
			}
		}
			

		for(i=0;i<cha;i++){				
			for(int j=0;j<y;j++){
				for(int l=0;l<x;l++){
							
				rr[i][j][l]=image.at<uchar>(j,l);
				if(rr[i][j][l]<10)
				rr[i][j][l]=0;
				else 
				rr[i][j][l]=1;				
				//printf("%2.0lf ",rr[i][j][l]);		
				}
	printf("\n");
			}
	}
	
		



	//cin >> kkk;
		int c_cols=((x-f_size)/s)+1;
		int c_rows=((y-f_size)/s)+1;
	//	printf("%d %d",c_rows,c_cols);
	

//f-o		
	
		rr1 = (double***)malloc(f_num*sizeof(double**));
		for(i=0;i<f_num;i++){						
			*(rr1+i) = (double**)malloc(c_rows*sizeof(double*));									
			for(int j=0;j<c_rows;j++){						
			*(*(rr1+i)+j) = (double*)malloc(c_cols*sizeof(double));
				
			}
		}
		
	

		for(int k=0;k<f_num;k++){
			for(int SC=0;SC<c_rows;SC++){		
				for(int SR=0;SR<c_cols;SR++){			
				rr1[k][SC][SR]=0;
				}
					
			}		
		}

	for(int q=0;q<f_num;q++){
		for(int k=0;k<cha;k++){
			for(int SC=0;SC<c_rows;SC++){		
				for(int SR=0;SR<c_cols;SR++){		
					for(int c=0;c<f_size;c++){
						for(int d=0;d<f_size;d++){	
						rr1[q][SC][SR]+=rr[k][c+SC*s][d+SR*s]*conv1[q][k][c][d];
						}
					}
					//printf("%.3lf ",rr1[q][SC][SR]);
				}//printf("\n");
			}
	        }
	}


	/*for(i=0;i<c_rows;i++)
		{
			for(j=0;j<c_cols;j++)
			{
				printf("%2.0lf",rr1[0][i][j]);
			}
			printf("\n");
		}*/
	//m_p1
	int pf_size=2;
	int ps=2;
	int pm_cols=((c_cols-pf_size)/ps)+1;
	int pm_rows=((c_rows-pf_size)/ps)+1;
	

	
		rr2 = (double***)malloc(f_num*sizeof(double**));
		for(i=0;i<f_num;i++){						
		*(rr2+i) = (double**)malloc(pm_rows*sizeof(double*));									
			for(int j=0;j<pm_rows;j++){						
				*(*(rr2+i)+j) = (double*)malloc(pm_cols*sizeof(double));
			}
		}
			


	
		for(i=0;i<f_num;i++){
			for(int SC=0;SC<pm_rows;SC++){		
				for(int SR=0;SR<pm_cols;SR++){	max1=INT_MIN;	
					for(int c=0;c<pf_size;c++){
						for(int d=0;d<pf_size;d++){	
							if((rr1[i][c+SC*ps][d+SR*ps])>max1)
	                                        	{
							max1=rr1[i][c+SC*ps][d+SR*ps];			
							rr2[i][SC][SR]=max1;							
							}
						}
	                		}//printf("%lf %d %d %d ",rr2[i][SC][SR],i,SC,SR);

				}//printf("\n");
			}
		}
/*	for(i=0;i<pm_rows;i++)
		{
			for(j=0;j<pm_cols;j++)
			{
				printf("%2.0lf",rr2[0][i][j]);
			}
			printf("\n");
		}

*/




	int cf_size=5;
	int cs=1;
	int cf_num=50;
	int cha2=20;
	
	int c_rows2=((pm_rows-cf_size)/cs)+1;
	int c_cols2=((pm_cols-cf_size)/cs)+1;

		rr3 = (double***)malloc(cf_num*sizeof(double**));
		for(i=0;i<cf_num;i++){						
			*(rr3+i) = (double**)malloc(c_rows2*sizeof(double*));									
			for(int j=0;j<c_rows2;j++){						
				*(*(rr3+i)+j) = (double*)malloc(c_cols2*sizeof(double));
			}
		}
	
	
	//conv2	
	for(int q=0;q<cf_num;q++){
			
				for(int SC=0;SC<c_rows2;SC++){		
					for(int SR=0;SR<c_cols2;SR++){		
						for(int c=0;c<cf_size;c++){
							for(int d=0;d<cf_size;d++){	
							rr3[q][SC][SR]=0;
							}
						}
					
					}
				}
	       
	}

	for(int q=0;q<cf_num;q++){
			for(int k=0;k<cha2;k++){
				for(int SC=0;SC<c_rows2;SC++){		
					for(int SR=0;SR<c_cols2;SR++){		
						for(int c=0;c<cf_size;c++){
							for(int d=0;d<cf_size;d++){	
							rr3[q][SC][SR]+=rr2[k][c+SC*cs][d+SR*cs]*conv2[q][k][c][d];
							}
						}//printf("%lf %d %d %d ",rr3[q][SC][SR],q,SC,SR);
				}//printf("\n");
				}
	        }
	}

	/*for(i=0;i<c_rows2;i++)
		{
			for(j=0;j<c_cols2;j++)
			{
				printf("%2.0lf",rr3[0][i][j]);
			}
			printf("\n");
		}
*/


		//max_p2
		int p2f_size=2;
		int p2s=2;
		int p2m_cols=((c_cols2-p2f_size)/p2s)+1;
		int p2m_rows=((c_rows2-p2f_size)/p2s)+1;			//여기부터
	
				
	
		rr4 = (double***)malloc(cf_num*sizeof(double**));
		for(i=0;i<cf_num;i++){						
			*(rr4+i) = (double**)malloc(p2m_rows*sizeof(double*));									
			for(int j=0;j<y;j++){						
				*(*(rr4+i)+j) = (double*)malloc(p2m_cols*sizeof(double));
			}
		}
			
	
	for(int q=0;q<cf_num;q++){
		
			for(int SC=0;SC<p2m_rows;SC++){		
				for(int SR=0;SR<p2m_cols;SR++){	max2 = INT_MIN;	
					for(int c=0;c<p2f_size;c++){
						for(int d=0;d<p2f_size;d++){	
							if((rr3[q][c+SC*p2s][d+SR*p2s])>max2)
	                                        	{
							max2=rr3[q][c+SC*p2s][d+SR*p2s];
							rr4[q][SC][SR]=max2;	
							}
						}
	                		}
				//printf("%lf %d %d %d ",rr4[q][SC][SR],q,SC,SR);
				}
			}//printf("\n");
		
	}for(i=0;i<p2m_rows;i++)
		{
			for(j=0;j<p2m_cols;j++)
			{
				printf("%2.0lf",rr4[0][i][j]);
			}
			printf("\n");
		}
			//cnct
		double connect1[500];
		double connect2[800]={};
		int cnt=0;
		double connect3[10];
			
		
	for(int q=0;q<cf_num;q++){
	
			for(int SC=0;SC<p2m_rows;SC++){		
				for(int SR=0;SR<p2m_cols;SR++){
				connect2[cnt]=rr4[q][SC][SR];
				
				//printf("%lf ",connect2[cnt]);			
				}
			}
		
	}
	
	
	for(l=0;l<500;l++){
		for(i=0;i<800;i++){
		connect1[l]+=ip1[l][i]*connect2[i];
		
		}//printf("%lf %d ",connect1[l],l);
	}
	
	
	for(i=0;i<500;i++){
		if(connect1[i]<0)
		connect1[i]=0;
	//printf("%lf %d ",connect1[i],i);
	}
	
	
	for(int m=0;m<10;m++){
		for(i=0;i<500;i++){
		connect3[m]+=connect2[i]*ip2[m][i];
		
		}//printf("%lf %d ",connect3[m],m);
	}
	
	for(int z=0;z<10;z++){
	printf("%d :%lf\n",z,connect3[z]);
	}
	
	
	

	
	


	

	
	
		
	for(i=0;i<cha;i++){
		for(int jj=0;jj<y;jj++){
		free(*(*(rr+i)+jj));
		}
		free(*(rr+i));
	}free(rr);


	for(int q=0;q<f_num;q++){	
		for(int jj=0;jj<c_rows;jj++){
		free(*(*(rr1+q)+jj));
		}
		free(*(rr1+j));
	}free(rr1);

	for(int q=0;q<f_num;q++){	
		for(int j1=0;j1<pm_rows;j1++){
		free(*(*(rr2+q)+j1));
		}
		free(*(rr2+q));
	}free(rr2);

	
	for(int q=0;q<cf_num;q++){	
		for(int j2=0;j2<c_rows2;j2++){
		free(*(*(rr3+q)+j2));
		}
		free(*(rr3+q));
	}free(rr3);

	for(int q=0;q<cf_num;q++){	
		for(int j3=0;j3<p2m_rows;j3++){
		free(*(*(rr4+q)+j3));
		}
		free(*(rr4+q));
	}free(rr4);
	return 0;	

}


