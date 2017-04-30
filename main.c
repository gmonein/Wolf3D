#include <stdio.h>

int		blend(unsigned char fg[4], unsigned char bg[4])
{
	unsigned int		alpha;
	unsigned int		inv_alpha;
	unsigned char		res[4];

	alpha = fg[3] + 1;
	inv_alpha = 256 - fg[3];
	res[0] = (unsigned char)((alpha * fg[0] + inv_alpha * bg[0]) >> 8);
	res[1] = (unsigned char)((alpha * fg[1] + inv_alpha * bg[1]) >> 8);
	res[2] = (unsigned char)((alpha * fg[2] + inv_alpha * bg[2]) >> 8);
	res[3] = 0xFF;
//	printf("- %08X\n", *(int *)fg);
//	printf("-> %02X %02X %02X %02X\n", fg[0], fg[1], fg[2], fg[3]);
	return (*(int *)res);
}

int		main(void)
{
	int		fg;
	int		bg;

	fg = 0xA000FF00;
	bg = 0xFFFFFFFF;
	printf("blend : \n->%08X\n->%08X\n", fg, bg);
	printf("=%08X\n", blend((char *)&fg, (char *)&bg));
	return (1);
}
