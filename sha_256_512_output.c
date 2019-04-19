#include "sha256.h"
#include "sha512.h"

/*
**	Functions for producing output for SHA-256 and SHA-512 respectively.
*/

char	*sha256_output(uint32_t *hash)
{
	int		i;
	int		j;
	char	*temp;
	int		temp_len;
	char	*result;

	i = 8;
	j = 64;
	if (!(result = ft_memalloc(sizeof(char) * 65)))
		return (NULL);
	ft_memset(result, '0', 64);
	while (i)
	{
		temp = uint32_into_hex(hash[--i]);
		temp_len = ft_strlen(temp);
		while (temp_len)
			result[--j] = ft_tolower(temp[--temp_len]);
		while (j && j % 8)
			j--;
		if (temp)
			ft_memdel((void **)&temp);
	}
	return (result);
}

char	*uint32_into_hex(uint32_t num)
{
	int		len;
	int		temp;
	char	*result;

	len = 8;
	if (!(result = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memset(result, '0', len);
	while (len)
	{
		temp = (uint8_t)num % 16;
		result[--len] = temp < 10 ? temp + '0' : temp + 87;
		temp = (uint8_t)num / 16;
		result[--len] = temp < 10 ? temp + '0' : temp + 87;
		num = num >> 8;
	}
	return (result);
}

char	*sha512_output(uint64_t *hash)
{
	int		i;
	int		j;
	char	*temp;
	int		temp_len;
	char	*result;

	i = 8;
	j = 128;
	if (!(result = ft_memalloc(sizeof(char) * 129)))
		return (NULL);
	ft_memset(result, '0', 128);
	while (i)
	{
		temp = uint64_into_hex(hash[--i]);
		temp_len = ft_strlen(temp);
		while (temp_len)
			result[--j] = ft_tolower(temp[--temp_len]);
		while (j && j % 8)
			j--;
		if (temp)
			ft_memdel((void **)&temp);
	}
	return (result);
}

char	*uint64_into_hex(uint64_t num)
{
	int		len;
	int		temp;
	char	*result;

	len = 16;
	if (!(result = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memset(result, '0', len);
	while (len)
	{
		temp = (uint8_t)num % 16;
		result[--len] = temp < 10 ? temp + '0' : temp + 87;
		temp = (uint8_t)num / 16;
		result[--len] = temp < 10 ? temp + '0' : temp + 87;
		num = num >> 8;
	}
	return (result);
}
