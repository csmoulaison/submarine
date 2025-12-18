#ifndef glmath_h_INCLUDED
#define glmath_h_INCLUDED

void gmath_mat4_identity(f32* res);
void gmath_mat4_perspective(f32 fovy, f32 aspect, f32 zfar, f32 znear, f32* res);
void gmath_mat4_lookat(f32* origin, f32* target, f32* up, f32* res);
void gmath_mat4_mul(f32* a, f32* b, f32* res);
void gmath_mat4_translation(f32* v, f32* res);
f32 gmath_radians(f32 degrees);

#ifdef CSM_BASE_IMPLEMENTATION

void gmath_mat4_identity(f32* res) {
	for(i8 i = 0; i < 16; i++) {
		res[i] = 0.0f;
	}
	res[0] = 1.0f;
	res[5] = 1.0f;
	res[10] = 1.0f;
	res[15] = 1.0f;
}

void gmath_mat4_perspective(f32 fovy, f32 aspect, f32 zfar, f32 znear, f32* res) {
	assert(zfar != znear);

	f32 rad = fovy;
	f32 tan_half_fovy = tan(rad / 2.0f);

	for(i8 i = 0; i < 16; i++) {
		res[i] = 0.0f;
	}
	res[0] = 1.0f / (aspect * tan_half_fovy);
	res[5] = 1.0f / (tan_half_fovy);
	res[10] = - (zfar + znear) / (zfar - znear);
	res[11] = - 1.0f;
	res[14] = - (2.0f * zfar * znear) / (zfar - znear);
}

void gmath_mat4_lookat(f32* origin, f32* target, f32* up, f32* res) {
	float dir[3] = { 
		target[0] - origin[0],
		target[1] - origin[1],
		target[2] - origin[2]
	};
	float f[3];
	float u[3]; 
	float s[3]; 
	v3_normalize(dir, f);
	v3_normalize(up, u);

	float cross_fu[3];
	v3_cross(f, u, cross_fu);

	v3_normalize(cross_fu, s);
	v3_cross(s, f, u);

	res[0] = s[0];
	res[4] = s[1];
	res[8] = s[2];
	res[1] = u[0];
	res[5] = u[1];
	res[9] = u[2];
	res[2] = -f[0];
	res[6] = -f[1];
	res[10] = -f[2];
	res[12] = -v3_dot(s, origin);
	res[13] = -v3_dot(u, origin);
	res[14] =  v3_dot(f, origin);
}

f32 gmath_radians(f32 degrees) {
	return degrees * 0.0174533;
}

void gmath_mat4_mul(f32* a, f32* b, f32* res) {
	f32 a00 = a[0];
	f32 a01 = a[1];
	f32 a02 = a[2]; 
	f32 a03 = a[3];
	f32 a10 = a[4];
	f32 a11 = a[5];
	f32 a12 = a[6];
	f32 a13 = a[7];
	f32 a20 = a[8];
	f32 a21 = a[9];
	f32 a22 = a[10];
	f32 a23 = a[11];
	f32 a30 = a[12];
	f32 a31 = a[13];
	f32 a32 = a[14];
	f32 a33 = a[15];

	f32 b00 = b[0];
	f32 b01 = b[1];
	f32 b02 = b[2]; 
	f32 b03 = b[3];
	f32 b10 = b[4];
	f32 b11 = b[5];
	f32 b12 = b[6];
	f32 b13 = b[7];
	f32 b20 = b[8];
	f32 b21 = b[9];
	f32 b22 = b[10];
	f32 b23 = b[11];
	f32 b30 = b[12];
	f32 b31 = b[13];
	f32 b32 = b[14];
	f32 b33 = b[15];

	res[0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
	res[1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
	res[2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
	res[3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
	res[4] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
	res[5] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
	res[6] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
	res[7] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
	res[8] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
	res[9] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
	res[10] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
	res[11] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
	res[12] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
	res[13] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
	res[14] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
	res[15] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
}

void gmath_mat4_translation(f32* v, f32* res) {
	for(i8 i = 0; i < 16; i++) {
		res[i] = 0.0f;
	}
	res[0] = 1.0f;
	res[5] = 1.0f;
	res[10] = 1.0f;
	res[15] = 1.0f;

	res[12] = v[0];
	res[13] = v[1];
	res[14] = v[2];
}

#endif // CSM_BASE_IMPLEMENTATION
#endif // glmath_h_INCLUDED
