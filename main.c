#include <stdio.h>

int		main(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 257)
	{
		j = 0;
		while (j < 256)
		{
			if (j == 255)
				printf("0 -1");
			else
				if (i == 255)
					printf("0 ");
				else if (i == 256)
					printf("-1 ");
				else
					printf("0 ");
			j++;
		}
		printf("\n");
		i++;
	}
}
