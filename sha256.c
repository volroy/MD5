#include "sha256.h"

char			*sha256_start(char *m, size_t len)
{
	size_t		i;
	uint32_t	*padded_m;

	i = 0;
	if ((len = sha256_padding(m, len, &padded_m)))
	{
		sha256_add_and_equate_words(g_t1, g_sha256_h, 0);
		while (i < len)
		{
			sha256_process(&(padded_m[i]));
			i += 16;
		}
		ft_memdel((void **)&padded_m);
	}
	else
		perror("Message Digest was created by default!\nSomething went wrong");
	ft_memdel((void **)&m);
	return (sha256_output(g_t1));
}

int				sha256_padding(char *m, uint64_t slen, uint32_t **nm)
{
	int			i;
	uint8_t		*temp;
	uint64_t	nm_len;

	nm_len = slen * 8 + 1;
	while ((nm_len % 512) != 448)
		nm_len++;
	nm_len = (nm_len + 64) / 8;
	if (!(temp = ft_memalloc(sizeof(uint8_t) * nm_len)))
		return (0);
	ft_memcpy(temp, m, slen);
	temp[slen] = 128;
	slen *= 8;
	i = 1;
	while (i <= 8)
	{
		temp[nm_len - i] = (uint8_t)slen;
		slen = slen >> 8;
		i++;
	}
	nm_len /= 4;
	*nm = (uint32_t *)temp;
	return (nm_len);
}

void			sha256_process(uint32_t *x)
{
	int			i;
	uint32_t	ah[8];
	uint32_t	temp1;
	uint32_t	temp2;
	uint32_t	w[64];

	i = 0;
	sha256_expand_words_amount(x, w);
	sha256_add_and_equate_words(ah, g_t1, 0);
	while (i < 64)
	{
		temp1 = ah[7] + g_sha256_k[i] + w[i]
			+ S1_256(ah[4]) + CH_256(ah[4], ah[5], ah[6]);
		temp2 = S0_256(ah[0]) + MAJ_256(ah[0], ah[1], ah[2]);
		ah[7] = ah[6];
		ah[6] = ah[5];
		ah[5] = ah[4];
		ah[4] = ah[3] + temp1;
		ah[3] = ah[2];
		ah[2] = ah[1];
		ah[1] = ah[0];
		ah[0] = temp1 + temp2;
		i++;
	}
	sha256_add_and_equate_words(g_t1, ah, 1);
}

void			sha256_expand_words_amount(uint32_t *x, uint32_t *w)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		while (i < 16)
		{
			w[i] = ft_swap_bits32(x[i]);
			i++;
		}
		w[i] = D1_256(w[i - 2]) + w[i - 7] + D0_256(w[i - 15]) + w[i - 16];
		i++;
	}
}

void			sha256_add_and_equate_words(uint32_t *a, uint32_t *b, int op)
{
	if (!op)
	{
		a[0] = b[0];
		a[1] = b[1];
		a[2] = b[2];
		a[3] = b[3];
		a[4] = b[4];
		a[5] = b[5];
		a[6] = b[6];
		a[7] = b[7];
	}
	else
	{
		a[0] += b[0];
		a[1] += b[1];
		a[2] += b[2];
		a[3] += b[3];
		a[4] += b[4];
		a[5] += b[5];
		a[6] += b[6];
		a[7] += b[7];
	}
}
