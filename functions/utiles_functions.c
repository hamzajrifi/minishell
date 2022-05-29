
#include "../header/utiles_functions.h"

unsigned int  ft_strlen(char *src)
{
    unsigned int    i;

    i = 0;
    while(src && src[i])
        i++;
    return(i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lendst;
	size_t	len_s;

	j = 0;
	len_s = 0;
	lendst = ft_strlen(dst);
	i = ft_strlen(dst); 
	while (src[len_s] != '\0')
		len_s++;
	if (dstsize == 0 || dstsize <= lendst)
		return (dstsize + len_s);
	while (src[j] && ((dstsize - lendst > 1)))
	{
		dst[i] = src[j];
		i++;
		j++;
		dstsize--;
	}
	dst[i] = '\0';
	return (lendst + len_s);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ptr;
	int		len;
	int		len1;

	if (s2 == NULL)
		return (NULL);
	len = ft_strlen((char *)s1);
	len1 = ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (len + len1 + 1));
	if (!ptr)
		return (NULL);
	*ptr = '\0';
    if (s1)
	    ft_strlcat(ptr, (char *)s1, len + 1);
	ft_strlcat(ptr, (char *)s2, len + len1 + 1);
	return (ptr);
}