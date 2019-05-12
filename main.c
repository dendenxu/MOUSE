#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define PENSIZE 10.0

void MouseEventProcess(int x, int y, int button, int event); /*鼠标消息回调函数*/

void MyMain() /*仅初始化执行一次*/
{
	InitGraphics();

	registerMouseEvent(MouseEventProcess); /*注册鼠标消息回调函数*/

	SetPenColor("GRAY");
	SetPenSize(PENSIZE);

}

void MouseEventProcess(int x, int y, int button, int event)
{
	static bool isDraw = FALSE;
	static double omx = 0.0, omy = 0.0;
	double mx, my;
	double dx, dy;
	double mySin, myCos;
	double L;

	mx = ScaleXInches(x); /*pixels --> inches*/
	my = ScaleYInches(y); /*pixels --> inches*/

	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)
		{
			isDraw = TRUE;
			omx = mx;
			omy = my;
		}

		break;

	case MOUSEMOVE:
		dx = mx - omx;
		dy = my - omy;
		//L = sqrt(pow(dx, 2) + pow(dy, 2));
		//myCos = dx / L;
		//mySin = dy / L;

		if (isDraw)
		{
			//if (L>=0.08)
			//{
			//	MovePen(omx-(0.05)*myCos,omy-(0.05)*mySin);
			//	DrawLine(dx+2*(0.05)*myCos,dy+2*(0.05)*mySin);
			//	omx = mx;
			//	omy = my;
			//}
			MovePen(omx, omy);
			DrawLine(dx, dy);
			omx = mx;
			omy = my;
		}

		break;

	case BUTTON_UP:
		if (button == LEFT_BUTTON)
			isDraw = FALSE;
		break;
	}
}