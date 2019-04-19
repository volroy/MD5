#include "md5.h"

char			*md5_start(char *m, size_t len)
{
	size_t		i;
	uint32_t	*padded_m;

	i = 0;
	if ((len = md5_padding(m, len, &padded_m)))
	{
		md5_add_and_equate_words(g_a, g_abcd, 0);
		while (i < len)
		{
			md5_process(&(padded_m[i]));
			i += 16;
		}
		ft_memdel((void **)&padded_m);
	}
	else
		perror("Message Digest was created by default!\nSomething went wrong");
	ft_memdel((void **)&m);
	return (md5_output());
}

int				md5_padding(char *m, uint64_t slen, uint32_t **nm)
{
	int			bits;
	uint8_t		*temp;
	uint64_t	nm_len;

	bits = 8;
	nm_len = slen * bits + 1;
	while ((nm_len % 512) != 448)
		nm_len++;
	nm_len = (nm_len + 64) / bits;
	if (!(temp = ft_memalloc(sizeof(uint8_t) * nm_len)))
		return (0);
	ft_memcpy(temp, m, slen);
	temp[slen] = 128;
	slen *= bits;
	while (bits)
	{
		temp[nm_len - bits] = (uint8_t)slen;
		slen = slen >> 8;
		bits--;
	}
	nm_len /= 4;
	*nm = (uint32_t *)temp;
	return (nm_len);
}

void			md5_process(uint32_t *x)
{
	uint32_t	ah[8];

	md5_add_and_equate_words(ah, g_a, 0);
	md5_round1(ah, x);
	md5_round2(ah, x);
	md5_round3(ah, x);
	md5_round4(ah, x);
	md5_add_and_equate_words(g_a, ah, 1);
}

void			md5_add_and_equate_words(uint32_t *a, uint32_t *b, int op)
{
	if (!op)
	{
		a[0] = b[0];
		a[1] = b[1];
		a[2] = b[2];
		a[3] = b[3];
	}
	else
	{
		a[0] += b[0];
		a[1] += b[1];
		a[2] += b[2];
		a[3] += b[3];
	}
}

char			*md5_output(void)
{
	int			i;
	int			j;
	int			k;
	int			temp;
	char		*result;

	i = 0;
	j = 0;
	if (!(result = ft_memalloc(sizeof(char) * 33)))
		return (NULL);
	while (i < 4)
	{
		k = 0;
		while (k < 4 && ++k)
		{
			temp = (uint8_t)g_a[i] / 16;
			result[j++] = temp < 10 ? temp + '0' : temp + 87;
			temp = (uint8_t)g_a[i] % 16;
			result[j++] = temp < 10 ? temp + '0' : temp + 87;
			g_a[i] = g_a[i] >> 8;
		}
		i++;
	}
	return (result);
}
