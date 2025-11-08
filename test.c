#include <iostream>

using namespace std;
int main()
{
	    string map[8] = {
        "1111111111111\n",
        "1P0000C000E01\n",
        "1011110111101\n",
        "1001000000001\n",
        "1111011111001\n",
        "1C00010000001\n",
        "101111101C001\n",
        "1111111111111\0",
    };
	int x = 1;
	int y = 1;
	int c =9;
	while (c--)
	{
	  cout<<"enter:\n";
		char m;cin>>m;
		if (m == 'w')
		{
		    if (!(map[x--][y] == '1'))
		    {
		        map[x][y] = '0';
			    x--;
			    map[x][y] = 'P';

		    }
		}
		if (m == 's')
		{
		    if (!map[x++][y] == '1')
		    {
		        map[x][y] = '0';
		        x++;
		        map[x][y] = 'P';
		    }
		}
    	if (m == 'a')
		{
		    if (!(map[x][y--] == '1'))
		    {
		    map[x][y] = '0';
		    y--;
		    map[x][y] = 'P';
		    }
		}
		if (m == 'd')
		{
		    if (!(map[x][y++] == '1'))
		    {
		        map[x][y] = '0';
		        y++;
			    map[x][y] = 'P';

		    }
		}
		if (m == 'q')
			break;
		for(int i=0;i < 8;i++)
			cout<<map[i];
		cout<<"\n";
	}

}
