#include "sha512.h"

char			*sha512_start(char *m, size_t len)
{
	size_t		i;
	uint64_t	*padded_m;

	i = 0;
	if ((len = sha512_padding(m, len, &padded_m)))
	{
		sha512_add_and_equate_words(g_t2, g_sha512_h, 0);
		while (i < len)
		{
			sha512_process(&(padded_m[i]));
			i += 16;
		}
		ft_memdel((void **)&padded_m);
	}
	else
		perror("Message Digest was created by default!\nSomething went wrong");
	ft_memdel((void **)&m);
	return (sha512_output(g_t2));
}

int				sha512_padding(char *m, uint64_t slen, uint64_t **nm)
{
	int			i;
	uint8_t		*temp;
	uint64_t	nm_len;

	nm_len = slen * 8 + 1;
	while ((nm_len % 1024) != 896)
		nm_len++;
	nm_len = (nm_len + 128) / 8;
	if (!(temp = ft_memalloc(sizeof(uint8_t) * nm_len)))
		return (0);
	ft_memcpy(temp, m, slen);
	temp[slen] = 128;
	slen *= 8;
	i = 1;
	while (i <= 16)
	{
		if (i > 8 && i++)
			continue ;
		temp[nm_len - i] = (uint8_t)slen;
		slen = slen >> 8;
		i++;
	}
	nm_len /= 8;
	*nm = (uint64_t *)temp;
	return (nm_len);
}

void			sha512_process(uint64_t *x)
{
	int			i;
	uint64_t	ah[8];
	uint64_t	temp1;
	uint64_t	temp2;
	uint64_t	w[80];

	i = 0;
	sha512_expand_words_amount(x, w);
	sha512_add_and_equate_words(ah, g_t2, 0);
	while (i < 80)
	{
		temp1 = ah[7] + g_sha512_k[i] + w[i]
			+ S1_512(ah[4]) + CH_512(ah[4], ah[5], ah[6]);
		temp2 = S0_512(ah[0]) + MAJ_512(ah[0], ah[1], ah[2]);
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
	sha512_add_and_equate_words(g_t2, ah, 1);
}

void			sha512_expand_words_amount(uint64_t *x, uint64_t *w)
{
	int			i;

	i = 0;
	while (i < 80)
	{
		while (i < 16)
		{
			w[i] = ft_swap_bits64(x[i]);
			i++;
		}
		w[i] = D1_512(w[i - 2]) + w[i - 7] + D0_512(w[i - 15]) + w[i - 16];
		i++;
	}
}

void			sha512_add_and_equate_words(uint64_t *a, uint64_t *b, int op)
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
