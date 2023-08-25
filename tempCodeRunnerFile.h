float nx, ny;
		nx = ny = 0;
		if (posy < 50)
			ny += dir_y;
		if (posy == 50 && posy < 75 && posx < 470)
			nx += dir_x;
		if (posy <= 75 && posy >= 50)
		{
			ny += dir_y;
			nx -= dir_x;
		}
		if (posy >= 75 && posx > -10)
			nx -= dir_x;
		if (posy > 50 && posx  -10)
		{
			nx -= dir_x;
			ny += dir_x;
		}