#!/bin/tcc -run
#include "zenomorph.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#ifdef __cplusplus
using namespace archivist;
#endif

#ifdef __TINYC__

zeno_cipher* fromJSONarray(const char* textarray)
{
	zeno_cipher* zc = (zeno_cipher*)malloc(sizeof(zeno_cipher));
	zc->content=(double*)malloc(1);
	size_t cr=0;
	size_t cnt=0;
	while(isspace(textarray[cr]))cr++;
	if(textarray[cr]!='['){printf("Bad Array at %d\n",cr);exit(3);}
	cr++;
	short cycle=1;
	while(cycle!=0)
	{
		while(isspace(textarray[cr]))cr++;
		if(textarray[cr]==']'||textarray[cr]=='\0'){cycle=0;	zc->size=cnt;zc->length=cnt;return zc;}
		else
		{
			if(!(textarray[cr]=='-'||isdigit(textarray[cr]))){printf("Bad Value at %d : '%c'\n",cr,textarray[cr]);exit(4);}
			char* entry=textarray+cr;
			while(isdigit(textarray[cr])||'-'==textarray[cr]||'.'==textarray[cr])cr++;
			char* outry=textarray+cr;
			double tmp = strtold(entry,&outry);
			cnt++;
			zc->content=(double*)realloc(zc->content,sizeof(double)*cnt);
			zc->content[cnt-1]=tmp;
			while(isspace(textarray[cr]))cr++;
			if(textarray[cr]==']'||textarray[cr]==',')cr++;else{printf("Unexpected '%c' at %d, expected ',' or ']'\n",textarray[cr],cr);exit(4);}
		}
	}
	zc->size=cnt;
	zc->length=cnt;
	return zc;
}

void printAsJSONarray(double* data,size_t sz)
{
	if(sz<1)printf("[]");
	else{
		printf("[%f",data[0]);
		size_t cur=1;
		while(cur<sz)
		{
			printf(",%f",data[cur]);
			cur++;
		}
		printf("]");
	}
}

void blur(double* data,size_t sz)
{
	
	for(size_t idx=0;idx<sz;idx++)
	{
		double b = 0.3-rand()/RAND_MAX*0.6;
		data[idx]+=b;
	}
}

int main(int argc,const char** argv)
{
	setlocale(LC_ALL|~LC_NUMERIC, "");
	if(argc!=5)
	{
		printf("Zenomorph16 v0.1 (AGPL 3.0)\nUsage: zenomorph_exe crypt|decrypt key salt data\n");
		return 1;
	}
	if(strcmp("crypt",argv[1])==0)
	{
		float* key;
		size_t key_sz;
		if(argv[2][0]=='[')
		{
			zeno_cipher* tmp_key=fromJSONarray(argv[2]);
			key=(float*)malloc(sizeof(float)*tmp_key->size);
			for(size_t idx=0;idx<tmp_key->size;idx++)key[idx]=tmp_key->content[idx];
			key_sz=tmp_key->size;
			free(tmp_key);
		}
		else
		{
			key=(float*)malloc(1);
			size_t cur=0;
			char n=argv[2][cur];
			do{
				cur++;
				key=realloc(key,cur*sizeof(double));
				key[cur-1]=(unsigned int)n;
				n=argv[2][cur];
			}while(n!='\0');
			key_sz=cur;
		}
		float* salt;
		size_t salt_sz;
		if(argv[3][0]=='[')
		{
			zeno_cipher* tmp_salt=fromJSONarray(argv[3]);
			salt=(float*)malloc(sizeof(float)*tmp_salt->size);
			for(size_t idx=0;idx<tmp_salt->size;idx++)salt[idx]=tmp_salt->content[idx];
			salt_sz=tmp_salt->size;
			free(tmp_salt);
		}
		else
		{
			salt=(float*)malloc(1);
			size_t cur=0;
			char n=argv[3][cur];
			do{
				cur++;
				salt=realloc(salt,cur*sizeof(double));
				salt[cur-1]=(unsigned int)n;
				n=argv[3][cur];
			}while(n!='\0');
			salt_sz=cur;
		}
		double* data;
		size_t data_sz;
		if(argv[4][0]=='[')
		{
			zeno_cipher* tmp_data=fromJSONarray(argv[4]);
			data=tmp_data->content;
			data_sz=tmp_data->size;
			free(tmp_data);
		}
		else
		{
			data=(double*)malloc(1);
			size_t cur=0;
			char n=argv[4][cur];
			do{
				cur++;
				data=realloc(data,cur*sizeof(double));
				data[cur-1]=(unsigned int)n;
				n=argv[4][cur];
			}while(n!='\0');
			data_sz=cur;
		}
		if(salt_sz!=key_sz){printf("Salt and key have different sizes\n");exit(6);}
		blur(data,data_sz);
		zeno_cipher* cipher=crypt16(data,data_sz,key,salt,key_sz);
		printAsJSONarray(cipher->content,cipher->size);
	}else if(strcmp("decrypt",argv[1])==0||strcmp("decrypt_s",argv[1])==0)
	{
		float* key;
		size_t key_sz;
		if(argv[2][0]=='[')
		{
			zeno_cipher* tmp_key=fromJSONarray(argv[2]);
			key=(float*)malloc(sizeof(float)*tmp_key->size);
			for(size_t idx=0;idx<tmp_key->size;idx++)key[idx]=tmp_key->content[idx];
			key_sz=tmp_key->size;
			free(tmp_key);
		}
		else
		{
			key=(float*)malloc(1);
			size_t cur=0;
			char n=argv[2][cur];
			do{
				cur++;
				key=realloc(key,cur*sizeof(double));
				key[cur-1]=(unsigned int)n;
				n=argv[2][cur];
			}while(n!='\0');
			key_sz=cur;
		}
		float* salt;
		size_t salt_sz;
		if(argv[3][0]=='[')
		{
			zeno_cipher* tmp_salt=fromJSONarray(argv[3]);
			salt=(float*)malloc(sizeof(float)*tmp_salt->size);
			for(size_t idx=0;idx<tmp_salt->size;idx++)salt[idx]=tmp_salt->content[idx];
			salt_sz=tmp_salt->size;
			free(tmp_salt);
		}
		else
		{
			salt=(float*)malloc(1);
			size_t cur=0;
			char n=argv[3][cur];
			do{
				cur++;
				salt=realloc(salt,cur*sizeof(double));
				salt[cur-1]=(unsigned int)n;
				n=argv[3][cur];
			}while(n!='\0');
			salt_sz=cur;
		}
		zeno_cipher* data;
		if(argv[4][0]=='[')
		{
			data=fromJSONarray(argv[4]);
		}
		else
		{
			printf("Non data content on decrypt.");exit(8);
		}
		if(salt_sz!=key_sz){printf("Salt and key have different sizes\n");exit(6);}
		double* farray=decrypt16(data,key,salt,key_sz);
		if(strcmp("decrypt_s",argv[1])==0)
		{
			for(size_t idx=0;idx<data->size;idx++)
				printf("%c",(char)(data->content[idx]));
			printf("\n");
		}
		else
		{
			printAsJSONarray(farray,data->size);
		}
	}else {
		printf("Bad option, use without options to display help\n");
		return 2;
	}
	return 0;
}
#endif // __TINYC__

zeno_cipher* 
#ifdef __cplusplus
archivist::
#endif
crypt16(
	double* data,
	size_t data_sz,
	float* key,
	float* salt,
	size_t key_sz
)
{
	size_t nb_d=key_sz;
	
	double* vectorized=(double*)malloc(sizeof(double)*(data_sz+data_sz%key_sz));
	size_t vec_sz=data_sz+data_sz%key_sz;
	for(size_t i=0;i<vec_sz;i++)
	{
		vectorized[i]=(
			i<data_sz?
			data[i]:0
		);
		vectorized[i]=(vectorized[i]/10000.0*(1+key[i%nb_d]))+salt[i%nb_d];
	}
	
	zeno_cipher* ret = (zeno_cipher*)malloc(sizeof(zeno_cipher));
	ret->content = vectorized;
	ret->length=data_sz;
	ret->size=vec_sz;
	return ret;
}

double* 
#ifdef __cplusplus
archivist::
#endif
decrypt16(
	zeno_cipher* data,
	float* key,
	float* salt,
	size_t key_sz
)
{
	size_t nb_d=key_sz;

	for(size_t i=0;i<data->size;i++)
	{
		data->content[i]=round((data->content[i]-salt[i%nb_d])/(1+key[i%nb_d])*10000);
	}
	return data->content;
}

zeno_cipher* 
#ifdef __cplusplus
archivist::
#endif
add16(
	zeno_cipher* data,
	size_t position,
	double value,
	float* key,
	float* salt,
	size_t key_sz
)
{
	size_t nb_d=key_sz;
	data->content[position]+=(value/10000.0*(1+key[position%nb_d]))+salt[position%nb_d];
	return data;
}

zeno_cipher* 
#ifdef __cplusplus
archivist::
#endif
multiply16(
	zeno_cipher* data,
	size_t position,
	double value,
	float* key,
	float* salt,
	size_t key_sz
)
{

}
