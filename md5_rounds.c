#include "md5.h"

void	md5_round1(uint32_t *abcd, uint32_t *x)
{
	uint32_t	a[4];

	md5_add_and_equate_words(a, abcd, 0);
	a[0] = a[1] + ROTR((a[0] + F(a[1], a[2], a[3]) + x[0] + g_k[0]), 7);
	a[3] = a[0] + ROTR((a[3] + F(a[0], a[1], a[2]) + x[1] + g_k[1]), 12);
	a[2] = a[3] + ROTR((a[2] + F(a[3], a[0], a[1]) + x[2] + g_k[2]), 17);
	a[1] = a[2] + ROTR((a[1] + F(a[2], a[3], a[0]) + x[3] + g_k[3]), 22);
	a[0] = a[1] + ROTR((a[0] + F(a[1], a[2], a[3]) + x[4] + g_k[4]), 7);
	a[3] = a[0] + ROTR((a[3] + F(a[0], a[1], a[2]) + x[5] + g_k[5]), 12);
	a[2] = a[3] + ROTR((a[2] + F(a[3], a[0], a[1]) + x[6] + g_k[6]), 17);
	a[1] = a[2] + ROTR((a[1] + F(a[2], a[3], a[0]) + x[7] + g_k[7]), 22);
	a[0] = a[1] + ROTR((a[0] + F(a[1], a[2], a[3]) + x[8] + g_k[8]), 7);
	a[3] = a[0] + ROTR((a[3] + F(a[0], a[1], a[2]) + x[9] + g_k[9]), 12);
	a[2] = a[3] + ROTR((a[2] + F(a[3], a[0], a[1]) + x[10] + g_k[10]), 17);
	a[1] = a[2] + ROTR((a[1] + F(a[2], a[3], a[0]) + x[11] + g_k[11]), 22);
	a[0] = a[1] + ROTR((a[0] + F(a[1], a[2], a[3]) + x[12] + g_k[12]), 7);
	a[3] = a[0] + ROTR((a[3] + F(a[0], a[1], a[2]) + x[13] + g_k[13]), 12);
	a[2] = a[3] + ROTR((a[2] + F(a[3], a[0], a[1]) + x[14] + g_k[14]), 17);
	a[1] = a[2] + ROTR((a[1] + F(a[2], a[3], a[0]) + x[15] + g_k[15]), 22);
	md5_add_and_equate_words(abcd, a, 0);
}

void	md5_round2(uint32_t *abcd, uint32_t *x)
{
	uint32_t	a[4];

	md5_add_and_equate_words(a, abcd, 0);
	a[0] = a[1] + ROTR((a[0] + G(a[1], a[2], a[3]) + x[1] + g_k[16]), 5);
	a[3] = a[0] + ROTR((a[3] + G(a[0], a[1], a[2]) + x[6] + g_k[17]), 9);
	a[2] = a[3] + ROTR((a[2] + G(a[3], a[0], a[1]) + x[11] + g_k[18]), 14);
	a[1] = a[2] + ROTR((a[1] + G(a[2], a[3], a[0]) + x[0] + g_k[19]), 20);
	a[0] = a[1] + ROTR((a[0] + G(a[1], a[2], a[3]) + x[5] + g_k[20]), 5);
	a[3] = a[0] + ROTR((a[3] + G(a[0], a[1], a[2]) + x[10] + g_k[21]), 9);
	a[2] = a[3] + ROTR((a[2] + G(a[3], a[0], a[1]) + x[15] + g_k[22]), 14);
	a[1] = a[2] + ROTR((a[1] + G(a[2], a[3], a[0]) + x[4] + g_k[23]), 20);
	a[0] = a[1] + ROTR((a[0] + G(a[1], a[2], a[3]) + x[9] + g_k[24]), 5);
	a[3] = a[0] + ROTR((a[3] + G(a[0], a[1], a[2]) + x[14] + g_k[25]), 9);
	a[2] = a[3] + ROTR((a[2] + G(a[3], a[0], a[1]) + x[3] + g_k[26]), 14);
	a[1] = a[2] + ROTR((a[1] + G(a[2], a[3], a[0]) + x[8] + g_k[27]), 20);
	a[0] = a[1] + ROTR((a[0] + G(a[1], a[2], a[3]) + x[13] + g_k[28]), 5);
	a[3] = a[0] + ROTR((a[3] + G(a[0], a[1], a[2]) + x[2] + g_k[29]), 9);
	a[2] = a[3] + ROTR((a[2] + G(a[3], a[0], a[1]) + x[7] + g_k[30]), 14);
	a[1] = a[2] + ROTR((a[1] + G(a[2], a[3], a[0]) + x[12] + g_k[31]), 20);
	md5_add_and_equate_words(abcd, a, 0);
}

void	md5_round3(uint32_t *abcd, uint32_t *x)
{
	uint32_t	a[4];

	md5_add_and_equate_words(a, abcd, 0);
	a[0] = a[1] + ROTR((a[0] + H(a[1], a[2], a[3]) + x[5] + g_k[32]), 4);
	a[3] = a[0] + ROTR((a[3] + H(a[0], a[1], a[2]) + x[8] + g_k[33]), 11);
	a[2] = a[3] + ROTR((a[2] + H(a[3], a[0], a[1]) + x[11] + g_k[34]), 16);
	a[1] = a[2] + ROTR((a[1] + H(a[2], a[3], a[0]) + x[14] + g_k[35]), 23);
	a[0] = a[1] + ROTR((a[0] + H(a[1], a[2], a[3]) + x[1] + g_k[36]), 4);
	a[3] = a[0] + ROTR((a[3] + H(a[0], a[1], a[2]) + x[4] + g_k[37]), 11);
	a[2] = a[3] + ROTR((a[2] + H(a[3], a[0], a[1]) + x[7] + g_k[38]), 16);
	a[1] = a[2] + ROTR((a[1] + H(a[2], a[3], a[0]) + x[10] + g_k[39]), 23);
	a[0] = a[1] + ROTR((a[0] + H(a[1], a[2], a[3]) + x[13] + g_k[40]), 4);
	a[3] = a[0] + ROTR((a[3] + H(a[0], a[1], a[2]) + x[0] + g_k[41]), 11);
	a[2] = a[3] + ROTR((a[2] + H(a[3], a[0], a[1]) + x[3] + g_k[42]), 16);
	a[1] = a[2] + ROTR((a[1] + H(a[2], a[3], a[0]) + x[6] + g_k[43]), 23);
	a[0] = a[1] + ROTR((a[0] + H(a[1], a[2], a[3]) + x[9] + g_k[44]), 4);
	a[3] = a[0] + ROTR((a[3] + H(a[0], a[1], a[2]) + x[12] + g_k[45]), 11);
	a[2] = a[3] + ROTR((a[2] + H(a[3], a[0], a[1]) + x[15] + g_k[46]), 16);
	a[1] = a[2] + ROTR((a[1] + H(a[2], a[3], a[0]) + x[2] + g_k[47]), 23);
	md5_add_and_equate_words(abcd, a, 0);
}

void	md5_round4(uint32_t *abcd, uint32_t *x)
{
	uint32_t	a[4];

	md5_add_and_equate_words(a, abcd, 0);
	a[0] = a[1] + ROTR((a[0] + I(a[1], a[2], a[3]) + x[0] + g_k[48]), 6);
	a[3] = a[0] + ROTR((a[3] + I(a[0], a[1], a[2]) + x[7] + g_k[49]), 10);
	a[2] = a[3] + ROTR((a[2] + I(a[3], a[0], a[1]) + x[14] + g_k[50]), 15);
	a[1] = a[2] + ROTR((a[1] + I(a[2], a[3], a[0]) + x[5] + g_k[51]), 21);
	a[0] = a[1] + ROTR((a[0] + I(a[1], a[2], a[3]) + x[12] + g_k[52]), 6);
	a[3] = a[0] + ROTR((a[3] + I(a[0], a[1], a[2]) + x[3] + g_k[53]), 10);
	a[2] = a[3] + ROTR((a[2] + I(a[3], a[0], a[1]) + x[10] + g_k[54]), 15);
	a[1] = a[2] + ROTR((a[1] + I(a[2], a[3], a[0]) + x[1] + g_k[55]), 21);
	a[0] = a[1] + ROTR((a[0] + I(a[1], a[2], a[3]) + x[8] + g_k[56]), 6);
	a[3] = a[0] + ROTR((a[3] + I(a[0], a[1], a[2]) + x[15] + g_k[57]), 10);
	a[2] = a[3] + ROTR((a[2] + I(a[3], a[0], a[1]) + x[6] + g_k[58]), 15);
	a[1] = a[2] + ROTR((a[1] + I(a[2], a[3], a[0]) + x[13] + g_k[59]), 21);
	a[0] = a[1] + ROTR((a[0] + I(a[1], a[2], a[3]) + x[4] + g_k[60]), 6);
	a[3] = a[0] + ROTR((a[3] + I(a[0], a[1], a[2]) + x[11] + g_k[61]), 10);
	a[2] = a[3] + ROTR((a[2] + I(a[3], a[0], a[1]) + x[2] + g_k[62]), 15);
	a[1] = a[2] + ROTR((a[1] + I(a[2], a[3], a[0]) + x[9] + g_k[63]), 21);
	md5_add_and_equate_words(abcd, a, 0);
}
