//
//  EyeP.cpp
//
//  Created by SIFEN ZHONG on 6/10/14.
//  Copyright (c) 2014 ___ZHONGSIFEN___. All rights reserved.
//

#include "_EyeP.hpp"

void EyeP_kw(
	float t_x, float t_y,
	int& k_x, int& k_y,
	int16_t& w_0, int16_t& w_1, int16_t& w_2, int16_t& w_3)
{
	k_x = (int)floorf(t_x);
	k_y = (int)floorf(t_y);
	float p1 = t_x - k_x;
	float p2 = t_y - k_y;
	float q1 = 1.0F - p1;
	float q2 = 1.0F - p2;
	w_0 = _s(q1*q2);
	w_1 = _s(p1*q2);
	w_2 = _s(q1*p2);
	w_3 = _s(p1*p2);
}

void EyeP_kwmap_zr(
	FunG fung, void* param,
	int l_x, int l_y, float z_x, float z_y, float r_x, float r_y,
	int m_x, int m_y, float w_x, float w_y, float s_x, float s_y,
	int32_t map_k[], int16_t map_w[][4])
{
	float m0_x = -(s_x*m_x / 2);
	float m0_y = -(s_x*m_y / 2);
	float f_x, f_y, g_x, g_y;
	for (int i = 0, i2 = 0; i2<m_y; i2++) {
		g_y = m0_y + s_y*(i2 + 0.5F);
		for (int i1 = 0; i1<m_x; i1++, i++) {
			g_x = m0_x + s_x*(i1 + 0.5F);
			fung(g_x, g_y, f_x, f_y, param);
			float t_x = (f_x/r_x) + z_x;
			float t_y = (f_y/r_y) + z_y;

			//assert(t_x >= 0);
			//assert(t_y >= 0);
			//assert(t_x < l_x-1);
			//assert(t_y < l_y-1);

			if (t_x < 0) t_x = 0;
			if (t_x > l_x - 2) t_x = (float)l_x - 2;
			if (t_y < 0) t_y = 0;
			if (t_y > l_y - 2) t_y = (float)l_y - 2;

			int k_x, k_y;
			int16_t w_0, w_1, w_2, w_3;
			EyeP_kw(t_x, t_y, k_x, k_y, w_0, w_1, w_2, w_3);
			map_k[i] = k_x + k_y*l_x;
			map_w[i][0] = w_0;
			map_w[i][1] = w_1;
			map_w[i][2] = w_2;
			map_w[i][3] = w_3;
		}
	}
}

void EyeP_kwmap(
	FunG fung, void* param,
	int l_x, int l_y, float l_x_n, float l_x_p, float l_y_n, float l_y_p,
	int m_x, int m_y, float m_x_n, float m_x_p, float m_y_n, float m_y_p,
	int32_t map_k[], int16_t map_w[][4])
{
	float z_x = ((float)l_x) / 2;
	float z_y = ((float)l_y) / 2;
	float r_x = (l_x_p - l_x_n) / ((float)l_x);
	float r_y = (l_y_p - l_y_n) / ((float)l_y);
	float w_x = ((float)m_x) / 2;
	float w_y = ((float)m_y) / 2;
	float s_x = (m_x_p - m_x_n) / ((float)m_x);
	float s_y = (m_y_p - m_y_n) / ((float)m_y);

	EyeP_kwmap_zr(fung, param, l_x, l_y, z_x, z_y, r_x, r_y, m_x, m_y, w_x, w_y, s_x, s_y, map_k, map_w);
}

void EyeP_kwmap_(
	FunG fung, void* param,
	int l_x, int l_y, float l_x_n, float l_x_p, float l_y_n, float l_y_p,
	int m_x, int m_y, float m_x_n, float m_x_p, float m_y_n, float m_y_p,
	int32_t map_k[], int16_t map_w[][4])
{
	float r_x = (float)(l_x_p - l_x_n) / l_x;
	float r_y = (float)(l_y_p - l_y_n) / l_y;
	float s_x = (float)(m_x_p - m_x_n) / m_x;
	float s_y = (float)(m_y_p - m_y_n) / m_y;
	float f_x, f_y, g_x, g_y;
	for (int i = 0, i2 = 0; i2<m_y; i2++) {
		g_y = m_y_n + s_y*(i2 + 0.5F);
		for (int i1 = 0; i1<m_x; i1++, i++) {
			g_x = m_x_n + s_x*(i1 + 0.5F);
			fung(g_x, g_y, f_x, f_y, param);
			float t_x = (f_x - l_x_n) / r_x;
			float t_y = (f_y - l_y_n) / r_y;

			//assert(t_x >= 0);
			//assert(t_y >= 0);
			//assert(t_x < l_x-1);
			//assert(t_y < l_y-1);

			if (t_x < 0) t_x = 0;
			if (t_x > l_x - 2) t_x = (float)l_x - 2;
			if (t_y < 0) t_y = 0;
			if (t_y > l_y - 2) t_y = (float)l_y - 2;

			int k_x, k_y;
			int16_t w_0, w_1, w_2, w_3;
			EyeP_kw(t_x, t_y, k_x, k_y, w_0, w_1, w_2, w_3);
			map_k[i] = k_x + k_y*l_x;
			map_w[i][0] = w_0;
			map_w[i][1] = w_1;
			map_w[i][2] = w_2;
			map_w[i][3] = w_3;
		}
	}
}

void EyeP_kwmap(
	FunG fung, void* param,
	int l_x, int l_y, float l_x_n, float l_x_p, float l_y_n, float l_y_p,
	int m_x, int m_y, float m_x_n, float m_x_p, float m_y_n, float m_y_p,
	int32_t map_k[], int16_t map_w[][4],
	int32_t map_n[], int16_t map_z[][4])
{
	EyeP_kwmap(fung, param, l_x,   l_y,   l_x_n, l_x_p, l_y_n, l_y_p, m_x,   m_y,   m_x_n, m_x_p, m_y_n, m_y_p, map_k, map_w);
	EyeP_kwmap(fung, param, l_x/2, l_y/2, l_x_n, l_x_p, l_y_n, l_y_p, m_x/2, m_y/2, m_x_n, m_x_p, m_y_n, m_y_p, map_n, map_z);
}

void EyeP_remap_w(
	uint8_t f[], int l_x, int l_y,
	uint8_t g[], int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
{
	for (int i=0,i_y=0; i_y<m_y; i_y++) {
		for (int i_x=0; i_x<m_x; i_x++,i++) {
			int k = map_k[i];

			int w_0 = map_w[i][0];
			int w_1 = map_w[i][1];
			int w_2 = map_w[i][2];
			int w_3 = map_w[i][3];
			
			int f_0 = f[k      ];
			int f_1 = f[k+1    ];
			int f_2 = f[k+  l_x];
			int f_3 = f[k+1+l_x];
			
			g[i] = _r(f_0*w_0 + f_1*w_1 + f_2*w_2 + f_3*w_3);
		}
	}
}

typedef uint8_t c3_t[3];
void EyeP_remap_w3(
	uint8_t f[], int l_x, int l_y,
	uint8_t g[], int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
{
	c3_t* f_c3 = (c3_t*)f;
	c3_t* g_c3 = (c3_t*)g;
	for (int i = 0, i_y = 0; i_y<m_y; i_y++) {
		for (int i_x = 0; i_x<m_x; i_x++, i++) {
			int k = map_k[i];

			int w_0 = map_w[i][0];
			int w_1 = map_w[i][1];
			int w_2 = map_w[i][2];
			int w_3 = map_w[i][3];
			
			for (int c=0; c<3; c++) {
				int f_0 = f_c3[k     ][c];
				int f_1 = f_c3[k+1   ][c];
				int f_2 = f_c3[k+  l_x][c];
				int f_3 = f_c3[k+1+l_x][c];
				
				g_c3[i][c] = _r(f_0*w_0 + f_1*w_1 + f_2*w_2 + f_3*w_3);
			}
		}
	}
}

void EyeP_remap_k(
	uint8_t f[], int l_x, int l_y,
	uint8_t g[], int m_x, int m_y,
	int32_t map_k[])
{
	for (int i = 0, i_y = 0; i_y<m_y; i_y++) {
		for (int i_x = 0; i_x<m_x; i_x++, i++) {
			int k = map_k[i];
			
			int f_0 = f[k     ];
			int f_1 = f[k+1   ];
			int f_2 = f[k+  l_x];
			int f_3 = f[k+1+l_x];
			
			g[i] = (uint8_t)((f_0 + f_1 + f_2 + f_3) >> 2);
		}
	}
}

void EyeP_remap_yuv(
	uint8_t f_y[], uint8_t f_u[], uint8_t f_v[], int l_x, int l_y,
	uint8_t g_y[], uint8_t g_u[], uint8_t g_v[], int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4],
	int32_t map_n[], int16_t map_z[][4])
{
	EyeP_remap_w(f_y, l_x,   l_y,   g_y, m_x,   m_y,   map_k, map_w);
	EyeP_remap_w(f_u, l_x/2, l_y/2, g_u, m_x/2, m_y/2, map_n, map_z);
	EyeP_remap_w(f_v, l_x/2, l_y/2, g_v, m_x/2, m_y/2, map_n, map_z);
}
