#include "ImageData.h"

// 'LOGO_ISU_Darkblue_red', 188x105px
const unsigned char LOGO_ISU []= {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x20, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe7, 0xdc, 0x01, 0xc0, 0x3c, 0x07, 0xcf, 0xbf, 0x8f, 0x00, 
	0x73, 0xe0, 0x7e, 0x7d, 0xfc, 0xfe, 0x7c, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe3, 0xdf, 
	0x8f, 0xcf, 0xfc, 0xe3, 0xc7, 0xbf, 0x8f, 0xe3, 0xf3, 0xc7, 0x3e, 0x3d, 0xfc, 0x7e, 0x7c, 0x10, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe3, 0xdf, 0xcf, 0xcf, 0xfc, 0xf3, 0xc7, 0xbf, 0x0f, 0xe7, 
	0xf3, 0xcf, 0x9e, 0x3d, 0xf8, 0x7e, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe1, 0xdf, 
	0xcf, 0xcf, 0xfc, 0xf3, 0xc3, 0xbf, 0x27, 0xe7, 0xf3, 0x9f, 0x9e, 0x9d, 0xf8, 0x7e, 0x7f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe4, 0xdf, 0xcf, 0xc0, 0x7c, 0xe3, 0xc9, 0xbf, 0x67, 0xe7, 
	0xf3, 0x9f, 0xde, 0xcd, 0xf3, 0x3e, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe4, 0xdf, 
	0xcf, 0xc0, 0x3c, 0x07, 0xc9, 0xbe, 0x67, 0xe7, 0xf3, 0x9f, 0xce, 0xcd, 0xf3, 0x3e, 0x7f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe6, 0x5f, 0xcf, 0xcf, 0xfc, 0xf3, 0xcc, 0xbe, 0x03, 0xe7, 
	0xf3, 0x9f, 0xde, 0xe5, 0xf0, 0x3e, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe7, 0x1f, 
	0xcf, 0xcf, 0xfc, 0xf3, 0xce, 0x3e, 0x03, 0xe7, 0xf3, 0x9f, 0x9e, 0xf1, 0xe0, 0x1e, 0x7f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe7, 0x1f, 0xcf, 0xcf, 0xfc, 0xf3, 0xce, 0x3c, 0xfb, 0xe7, 
	0xf3, 0xcf, 0x1e, 0xf1, 0xe7, 0x9e, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe7, 0x9f, 
	0xcf, 0xc0, 0x3c, 0xf3, 0xcf, 0x3c, 0xf9, 0xe7, 0xf3, 0xe0, 0x3e, 0xf9, 0xef, 0xce, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xef, 0xdf, 0xdf, 0xc0, 0x3d, 0xfb, 0xdf, 0xbd, 0xf9, 0xf7, 
	0xf3, 0xf0, 0xfe, 0xfd, 0xef, 0xde, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0xff, 
	0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0c, 0x03, 0x8f, 0xc0, 0xe0, 0x1f, 0x3e, 0x67, 0xd9, 0x9f, 
	0x20, 0x18, 0x0e, 0x03, 0x20, 0x09, 0xe7, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xcc, 0xf3, 
	0x8f, 0x9e, 0x67, 0xff, 0x3e, 0x63, 0xd9, 0x9e, 0x6f, 0xfb, 0xe6, 0x73, 0x3e, 0x79, 0xe7, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xe4, 0xf9, 0xa7, 0x3f, 0x67, 0xff, 0x3e, 0x61, 0xd9, 0x9e, 
	0x6f, 0xfb, 0xe6, 0xfb, 0x3e, 0x7c, 0xcf, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xfc, 0xf9, 
	0x27, 0x3f, 0xe7, 0xff, 0x3e, 0x61, 0xd9, 0xce, 0x6f, 0xfb, 0xe6, 0x7f, 0x3e, 0x7e, 0x4f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1c, 0x03, 0x33, 0x3f, 0xe0, 0x3f, 0x3e, 0x64, 0xd9, 0xcc, 
	0xe0, 0x38, 0x0e, 0x07, 0x3e, 0x7e, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0c, 0x07, 
	0x33, 0x3f, 0xe0, 0x3f, 0x3e, 0x64, 0xd9, 0xcc, 0xe0, 0x38, 0x07, 0xc3, 0x3e, 0x7f, 0x3f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe4, 0xfe, 0x03, 0x3f, 0x67, 0xff, 0x3e, 0x66, 0x59, 0xe5, 
	0xef, 0xfb, 0xe7, 0xf9, 0x3e, 0x7f, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xe4, 0xfe, 
	0x79, 0x3e, 0x67, 0xff, 0x3e, 0x67, 0x19, 0xe1, 0xef, 0xfb, 0xe4, 0xf9, 0x3e, 0x7f, 0x3f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0xe4, 0xfc, 0xf9, 0x9e, 0x67, 0xff, 0x9c, 0x67, 0x19, 0xf1, 
	0xef, 0xfb, 0xe6, 0x79, 0x3e, 0x7f, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0c, 0xfc, 
	0xf9, 0xc0, 0xe0, 0x1f, 0xc0, 0xe7, 0x99, 0xf3, 0xe0, 0x1b, 0xe6, 0x03, 0x3e, 0x7f, 0x3f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xfe, 0x00, 
	0x0f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 
	0x01, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf0, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 
	0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3f, 
	0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x3f, 
	0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x1f, 
	0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x0f, 
	0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x03, 
	0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xc0, 
	0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf8, 
	0x00, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0
};

const IMAGE ISU_logo =
{
    LOGO_ISU,
	188,
    105
};
